#include "Game.h"

void Game::SetObjects() {
    float time;
    float time_coeff = 3.4;
    ManyFold::setWindowAxis(XWindow, YWindow);

    // add platform
    object* platform = new Platform(path_platform, XWindow / 2, YWindow - 100);
    objects.push_back(platform);

    // add ball
    object* ball = new Ball(path_ball, XWindow / 2, YWindow - 140);
    objects.push_back(ball);
    ball->setScale({ 0.5,0.5 });

    // add interaction
    manyfolds.push_back(new ManyFold(ball, platform));



    //add blocks and bonuses
    Bonus* bonus;
    object* bl;
    int rand_bonus;


    for (int i = 0; i < xNumBlocks; i++) {
        for (int j = 0; j < yNumBlocks; j++) {
            rand_bonus = ((double)rand() / RAND_MAX) * 10;

            // add bonus
            switch (rand_bonus)
            {
            case SIZE:

                bonus = new Bonus(path_bonus1, SIZE, i * path_block.weight_, j * path_block.hight_);
                // add bonus block
                bl = new BlockBonus(path_block, i * path_block.weight_, j * path_block.hight_);
                break;
            case SPEED:

                bonus = new Bonus(path_bonus2, SPEED, i * path_block.weight_, j * path_block.hight_);
                // add bonus block
                bl = new BlockBonus(path_block, i * path_block.weight_, j * path_block.hight_);
                break;

            case STICKING:

                bonus = new Bonus(path_bonus3, STICKING, i * path_block.weight_, j * path_block.hight_);
                bonus->getSprite().setColor(sf::Color(25, 20, 25));
                // add bonus block
                bl = new BlockBonus(path_block, i * path_block.weight_, j * path_block.hight_);
                break;

            case HEALTH:
                bonus = new Bonus(path_bonus3, HEALTH, i * path_block.weight_, j * path_block.hight_);
                bonus->getSprite().setColor(sf::Color(255, 255, 255));
                // add bonus block
                bl = new BlockBonus(path_block, i * path_block.weight_, j * path_block.hight_);
                break;

            case TRAJECTORY:

                bonus = new Bonus(path_bonus4, TRAJECTORY, i * path_block.weight_, j * path_block.hight_);
                // add bonus block
                bl = new BlockBonus(path_block, i * path_block.weight_, j * path_block.hight_);
                break;
            case INVULNERABLE:

                bonus = NULL;
                // add bonus block
                bl = new invulnerableBlock(path_block, i * path_block.weight_, j * path_block.hight_);
                bl->getSprite().setColor(sf::Color(25, 25, 255));
                break;

            case SPEEDBLOCK:
                bonus = NULL;
                // add bonus block
                bl = new SpeedBlock(path_block, i * path_block.weight_, j * path_block.hight_);
                ((SpeedBlock*)bl)->setBall((Ball*&)ball);
                bl->getSprite().setColor(sf::Color(255, 100, 255));
                break;
            default:
                bonus = NULL;
                // add bonus block
                bl = new Block(path_block, i * path_block.weight_, j * path_block.hight_);
                break;
            }

            if (bonus != NULL) {
                bonus->setScale({ 0.5,0.5 });
                bonus->setBall((Ball*&)ball);
                bonus->setPlatform((Platform*&)platform);
                ((BlockBonus*)bl)->setBonus(bonus);
                objects.push_back(bonus);
                manyfolds.push_back(new ManyFold(platform, (object*&)bonus));
            }


            // add to arrays for processing
            objects.push_back(bl);
            manyfolds.push_back(new ManyFold(ball, bl));

        }
    }

}
void Game::RUN() {

    Platform* platform = (Platform*)objects[0];
    Ball* ball = (Ball*)objects[1];

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



        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            Ball* circle = (Ball*)ball;
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
                if (circle->getSpeed().x == 0 && circle->getSpeed().y == 0) {
                    ball->getSprite().setPosition(vec2 + vec_ball);
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (circle->getSpeed() == sf::Vector2f({ 0,0 })) {
                    circle->setSpeed({ 1,1 });
                }
                break;

            default:
                break;
            }

        }

        // clear the window with black color
        window.clear(sf::Color::Blue);

        for (object* ob : objects) {
            if (ob->isShow()) {
                ob->run(time);
                window.draw(ob->getSprite());
            }

        }
        for (ManyFold* fold : manyfolds) {
            fold->setTime(time);
            fold->apply();
        }
        points.setString(to_string(ManyFold::getPlayerPoints()));
        window.draw(points);
        // end the current frame
        window.display();
    }


    // delete objects
    for (size_t i = 0; i < objects.size(); i++) {
        delete objects[i];
    }
    for (size_t i = 0; i < manyfolds.size(); i++) {
        delete manyfolds[i];
    }
}