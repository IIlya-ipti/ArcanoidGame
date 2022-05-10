#include "Game.h"


using namespace std;


void Game::SetObjects() {
    float time;
    float time_coeff = 3.4;
    ManyFold::setWindowAxis(XWindow, YWindow);

    // add platform
    std::shared_ptr <Platform> platform(new Platform(path_platform, XWindow / 2, YWindow - 100));
    objects.push_back(platform);

    // add ball
    std::shared_ptr <Ball> ball(new Ball(path_ball, XWindow / 2, YWindow - 140));
    objects.push_back(ball);
    ball->setScale({ 0.5,0.5 });

    // add intersection
    manyfolds.push_back(std::unique_ptr<ManyFold>(new ManyFold(std::dynamic_pointer_cast<object>(ball), 
        std::dynamic_pointer_cast<object>(platform))));



    //add blocks and bonuses
    std::shared_ptr <Bonus> bonus = NULL;
    std::shared_ptr <object> bl = NULL;
    int rand_bonus;


    for (int i = 0; i < xNumBlocks; i++) {
        for (int j = 0; j < yNumBlocks; j++) {
            rand_bonus = ((double)rand() / RAND_MAX) * 10;

            // add bonus
            switch (rand_bonus)
            {
            case SIZE:
                
                bonus.reset(new BonusSize(path_bonus1, i * path_block.weight_, j * path_block.hight_));
            
                bl.reset(new BlockBonus(path_block, i * path_block.weight_, j * path_block.hight_,bonus));
                break;
            case SPEED:

                bonus.reset(new BonusSpeed(path_bonus2, i * path_block.weight_, j * path_block.hight_));
        
                bl.reset(new BlockBonus(path_block, i * path_block.weight_, j * path_block.hight_,bonus));
                break;

            case STICKING:

                bonus.reset(new BonusSticking(path_bonus3, i * path_block.weight_, j * path_block.hight_));
                bonus->getSprite().setColor(sf::Color(25, 20, 25));
        
                bl.reset(new BlockBonus(path_block, i * path_block.weight_, j * path_block.hight_,bonus));
                break;

            case HEALTH:
                bonus.reset(new BonusHealth(path_bonus3, i * path_block.weight_, j * path_block.hight_));
                bonus->getSprite().setColor(sf::Color(255, 255, 255));
                bl.reset(new BlockBonus(path_block, i * path_block.weight_, j * path_block.hight_,bonus));
                break;

            case TRAJECTORY:

                bonus.reset(new BonusTrajectory(path_bonus4, i * path_block.weight_, j * path_block.hight_));
                bl.reset(new BlockBonus(path_block, i * path_block.weight_, j * path_block.hight_,bonus));



                break;
            case INVULNERABLE:

                bonus = NULL;
                bl.reset(new invulnerableBlock(path_block, i * path_block.weight_, j * path_block.hight_));
                bl->getSprite().setColor(sf::Color(25, 25, 255));
                break;

            case SPEEDBLOCK:
                bonus = NULL;
                bl.reset(new SpeedBlock(path_block, i * path_block.weight_, j * path_block.hight_,ball));
                bl->getSprite().setColor(sf::Color(255, 100, 255));

                break;
            default:
                bonus = NULL;
                bl.reset(new Block(path_block, i * path_block.weight_, j * path_block.hight_));
                break;
            }

            if (bonus != NULL) {
                bonus->setScale({ 0.5,0.5 });
                bonus->setBall(ball);
                bonus->setPlatform(platform);
                objects.push_back(bonus);
                manyfolds.push_back(std::unique_ptr <ManyFold>(new ManyFold(platform, bonus)));
            }

            // add to arrays for processing
            objects.push_back(bl);
            manyfolds.push_back(std::unique_ptr <ManyFold>(new ManyFold(ball,bl)));

        }
    }

}
void Game::RUN() {

    std::shared_ptr <object> platform = objects[0];
    std::shared_ptr <object> ball = objects[1];

    // output player score
    sf::Text points;
    sf::Font font;
    font.loadFromFile("res/arial.ttf");
    points.setString("-");
    points.setCharacterSize(30);
    points.setFont(font);
    points.setFillColor(sf::Color::Black);
    points.setPosition(sf::Vector2f(100, YWindow - 100));


    // create the window
    sf::RenderWindow window(sf::VideoMode(XWindow, YWindow), "My window");

    // get time
    sf::Clock clock;
    sf::Time lastTime = clock.getElapsedTime();


    // run the program as long as the window is open
    float time;
    while (window.isOpen())
    {

        // correct time
        sf::Time currentTime = clock.getElapsedTime();
        time = time_coeff * (currentTime.asMicroseconds() - lastTime.asMicroseconds()) / 10000;
        lastTime = currentTime;




        sf::Event event;
        while (window.pollEvent(event))
        {
            sf::Vector2f vec2 = platform->getSprite().getPosition();
            sf::Vector2f vec_ball = ball->getSprite().getPosition() - vec2;
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
                vec2.x = event.mouseMove.x;
                platform->getSprite().setPosition(vec2);
                if (ball->getSpeed().x == 0 && ball->getSpeed().y == 0) {
                    ball->getSprite().setPosition(vec2 + vec_ball);
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (ball->getSpeed() == sf::Vector2f({ 0,0 })) {
                    ball->setSpeed({ 1,1 });
                }
                break;

            default:
                break;
            }

        }

        // clear the window with blue color
        window.clear(sf::Color::Blue);

        for (int i = 0; i < objects.size();i++) {
            if (objects[i]->isShow()) {
                objects[i]->run(time);
                window.draw(objects[i]->getSprite());
            }

        }
        for (int i = 0; i < manyfolds.size();i++) {
            manyfolds[i]->setTime(time);
            manyfolds[i]->apply();
        }


        points.setString(to_string(ManyFold::getPlayerPoints()));
        window.draw(points);
        window.display();
    }



}