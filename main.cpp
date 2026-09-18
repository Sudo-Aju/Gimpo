#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <string>

const float WINDOW_WIDTH = 800.f;
const float WINDOW_HEIGHT = 600.f;

const float PADDLE_WIDTH = 20.f;
const float PADDLE_HEIGHT = 100.f;

const float BALL_RADIUS = 12.f;
const float BALL_SIZE = BALL_RADIUS * 2.f;

const float START_BALL_SPEED = 300.f;
const float MAX_BALL_SPEED = 700.f;

const float PADDLE_SPEED = 400.f;

const int WIN_SCORE = 10;

int main()
{   
    int scorel = 0;
    int scorer = 0;

    float paddleSpeed = PADDLE_SPEED;

    float ballSpeedx = START_BALL_SPEED;
    float ballSpeedy = 0.f;

    float ly = 250.f;
    float ry = 250.f;

    float bx = 388.f;
    float by = 288.f;
    
    bool gameStarted = false;
    bool gamePaused = false;
    bool gameOver = false;

    sf::RenderWindow window(
        sf::VideoMode({800,600}),
        "Gimpo Pong"
    );

    sf::RectangleShape leftPaddle(
        {PADDLE_WIDTH, PADDLE_HEIGHT}
    );

    sf::RectangleShape rightPaddle(
        {PADDLE_WIDTH, PADDLE_HEIGHT}
    );

    sf::CircleShape ball(BALL_RADIUS);

    sf::RectangleShape centerLine(
        {4.f, WINDOW_HEIGHT}
    );

    leftPaddle.setPosition({25.f, ly});
    rightPaddle.setPosition({755.f, ry});
    ball.setPosition({bx, by});

    centerLine.setPosition({398.f, 0.f});

    sf::Font font;

    if (!font.openFromFile("./Assets/font.otf")) 
    {
        std::cerr << "font not loaded" << std::endl;
        return -1;
    }

    sf::Text scoreText(font);
    scoreText.setCharacterSize(32);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString("SCORE 0 - 0");

    sf::Text titleText(font);
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::White);
    titleText.setString("GIMPO PONG");

    sf::Vector2f titleSize = 
        titleText.getLocalBounds().size;
    
    titleText.setPosition({
        400.f - titleSize.x / 2.f, 
        200.f
    });

    sf::Text startText(font);
    startText.setCharacterSize(24);
    startText.setFillColor(sf::Color::White);

    sf::Text pauseText(font);
    pauseText.setCharacterSize(40);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setString("PAUSED");

    sf::Text winText(font);
    winText.setCharacterSize(40);
    winText.setFillColor(sf::Color::White);

    sf::Text countdownText(font);
    countdownText.setCharacterSize(60);
    countdownText.setFillColor(sf::Color::White);

    sf::SoundBuffer hitBuffer;
    sf::SoundBuffer scoreBuffer;

    bool soundsLoaded = false;

    if (
        hitBuffer.loadFromFile("./Assets/hit.WAV") && 
        scoreBuffer.loadFromFile("./Assets/ding.WAV")
    )
    {
        soundsLoaded = true;
    }
    else
    {
        std::cerr << "sound files are not loaded" << std::endl;
    }

    sf::Sound hitSound(hitBuffer);
    sf::Sound scoreSound(scoreBuffer);

    sf::Clock clock;

    float countdown = 0.f;
    int countdownNumber = 3;

    while (window.isOpen())
    {
        float deltaTime = 
            clock.restart().asSeconds();

        if (deltaTime > 0.05f)
        {
            deltaTime = 0.05f;
        }
        
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) 
            {
                window.close();
            }

            if (event->is<sf::Event::KeyPressed>())
            {
                auto key = 
                    event->getIf<sf::Event::KeyPressed>()->code;

                if (key == sf::Keyboard::Key::Space)
                {
                    if (!gameStarted && !gameOver)
                    {
                        gameStarted = true;
                        gamePaused = false;

                        countdown = 3.f;
                        countdownNumber = 3;

                        bx = 388.f;
                        by = 288.f;

                        ballSpeedx = START_BALL_SPEED;
                        ballSpeedy = 0.f;
                    }
                }

            
                if (key == sf::Keyboard::Key::P)
                {
                    if (gameStarted && !gameOver)
                    {
                        gamePaused = !gamePaused;
                    }
                }

                if (key == sf::Keyboard::Key::R)
                {
                    scorel = 0;
                    scorer = 0;

                    ly = 250.f;
                    ry = 250.f;

                    bx = 388.f;
                    by = 288.f;

                    ballSpeedx = START_BALL_SPEED;
                    ballSpeedy = 0.f;

                    gameOver = false;
                    gameStarted = true;
                    gamePaused = false;

                    countdown = 3.f;
                    countdownNumber = 3;
                }

                if (key == sf::Keyboard::Key::Escape)
                {
                    window.close();
                }
            }
        }

        if (gameStarted && !gamePaused && !gameOver)
        {
            if(countdown > 0.f)
            {
                countdown -= deltaTime;

                if (countdown > 2.f)
                {
                    countdownNumber = 3;
                }
                else if (countdown > 1.f)
                {
                    countdownNumber = 2;
                }
                else if (countdown > 0.f)
                {
                    countdownNumber = 1;
                }

                if (countdown <= 0.f)
                {
                    countdown = 0.f;
                }
            }

            if (countdown <= 0.f)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
                {
                    ly -= paddleSpeed * deltaTime;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
                {
                    ly += paddleSpeed * deltaTime;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
                {
                    ry -= paddleSpeed * deltaTime;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
                {
                    ry += paddleSpeed * deltaTime;
                }

                if (ly < 0.f) 
                {
                    ly = 0.f;
                }

                if (ly > WINDOW_HEIGHT - PADDLE_HEIGHT) 
                {
                    ly = WINDOW_HEIGHT - PADDLE_HEIGHT;
                }

                if (ry < 0.f) 
                {
                    ry = 0.f;
                }

                if (ry > WINDOW_HEIGHT - PADDLE_HEIGHT) 
                {
                    ry = WINDOW_HEIGHT - PADDLE_HEIGHT;
                }
                
                bx += deltaTime * ballSpeedx;
                by += deltaTime * ballSpeedy;
        
                if (by <= 0.f)
                {
                    by = 0.f;
                    ballSpeedy = std::abs(ballSpeedy);

                    if(soundsLoaded)
                    {
                        hitSound.play();
                    }
                }

                if (by >= WINDOW_HEIGHT - BALL_SIZE)
                {
                    by = WINDOW_HEIGHT - BALL_SIZE;
                    ballSpeedy = -std::abs(ballSpeedy);

                    if (soundsLoaded)
                    {
                        hitSound.play();
                    }
                }
                
                leftPaddle.setPosition({
                    25.f,
                    ly
                });
                rightPaddle.setPosition({
                    755.f,
                    ry
                });
                ball.setPosition({
                    bx, 
                    by
                });

                if (
                    ball.getGlobalBounds().findIntersection(
                        leftPaddle.getGlobalBounds()
                    )
                    &&
                    ballSpeedx < 0
                )
                {
                    bx = 45.f;
                    ballSpeedx = std::abs(ballSpeedx);

                    float paddleCenter = 
                        ly + PADDLE_HEIGHT / 2.f;

                    float ballCenter = 
                        by + BALL_RADIUS;

                    float difference = 
                        ballCenter - paddleCenter;

                    float normalized = 
                        difference / 
                        (PADDLE_HEIGHT / 2.f);

                    ballSpeedy = 
                        normalized * 
                        std::abs(ballSpeedx);

                    float currentSpeed = 
                        std::sqrt(
                            ballSpeedx * ballSpeedx + 
                            ballSpeedy * ballSpeedy
                        );

                    currentSpeed += 20.f;

                    if (currentSpeed > MAX_BALL_SPEED)
                    {
                        currentSpeed = MAX_BALL_SPEED;
                    }
        
                    float angle = 
                        std::atan2(
                            ballSpeedy,
                            ballSpeedx
                            );

                    ballSpeedx = 
                    std::cos(angle) * 
                    currentSpeed;

                    ballSpeedy = 
                    std::sin(angle) * 
                    currentSpeed;
        
                    if (soundsLoaded)
                    {
                        hitSound.play();
                    } 
                }

                if (ball.getGlobalBounds().findIntersection(
                        rightPaddle.getGlobalBounds()
                    ) 
                    && 
                    ballSpeedx > 0
                )
                {
                    bx = 731.f;
                    ballSpeedx = -std::abs(ballSpeedx);

                    float paddleCenter = 
                        ry + PADDLE_HEIGHT / 2.f;

                    float ballCenter = 
                    by + BALL_RADIUS;

                    float difference = 
                    ballCenter - paddleCenter;
                    float normalized = 
                    difference / (PADDLE_HEIGHT / 2.f);

                    ballSpeedy = 
                        normalized * 
                        std::abs(ballSpeedx);
                    
                    float currentSpeed = 
                        std::sqrt(
                            ballSpeedx * ballSpeedx + 
                            ballSpeedy * ballSpeedy
                        );

                    currentSpeed += 20.f;

                    if (currentSpeed > MAX_BALL_SPEED)
                    {
                        currentSpeed = MAX_BALL_SPEED;
                    }

                    float angle = 
                    std::atan2(
                        ballSpeedy, 
                        ballSpeedx
                    );

                    ballSpeedx = 
                        std::cos(angle) * 
                        currentSpeed;

                    ballSpeedy = 
                        std::sin(angle) * 
                        currentSpeed;

                    if (soundsLoaded)
                    {
                        hitSound.play();
                    }
                }

                if (bx > WINDOW_WIDTH)
                {
                    scorer++;

                    bx = 388.f;
                    by = 288.f;

                    ballSpeedx = 
                        -START_BALL_SPEED;

                    ballSpeedy = 0.f;

                    if (soundsLoaded)
                    {
                        scoreSound.play();
                    }

                    if (
                        scorer >= WIN_SCORE ||
                        scorel >= WIN_SCORE
                    )
                    {
                        gameOver = true;
                    }
                    else
                    {
                        countdown = 2.f;
                        countdownNumber = 2;
                    }
                }

                if (bx < -BALL_SIZE)
                {
                    scorel++;

                    bx = 388.f;
                    by = 288.f;

                    ballSpeedx = 
                        START_BALL_SPEED;

                    ballSpeedy = 0.f;

                    if (soundsLoaded)
                    {
                        scoreSound.play();
                    }

                    if (
                        scorer >= WIN_SCORE || 
                        scorel >= WIN_SCORE
                    )
                    {
                        gameOver = true;
                    }
                    else
                    {
                        countdown = 2.f;
                        countdownNumber = 2;
                    }
                }
       
                scoreText.setString(
                    "SCORE " + 
                    std::to_string(scorer) + 
                    " - " + 
                    std::to_string(scorel)
                );

                sf::Vector2f textSize = 
                    scoreText.getLocalBounds().size;
        
                scoreText.setPosition({
                    400.f - (textSize.x/2.f), 
                    300.f - (textSize.y/2.f)
                });
        
                ball.setPosition({bx,
                    by
                });
            }
        }

        window.clear();

        window.draw(centerLine);
        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.draw(ball);
        window.draw(scoreText);


        if (!gameStarted)
        {
            startText.setString(
                "PRESS SPACE TO START"
            );

            sf::Vector2f size = 
                startText.getLocalBounds().size;

            startText.setPosition({
                400.f - size.x / 2.f, 
                350.f
            });

            window.draw(titleText);
            window.draw(startText);
        }

        if (
            gameStarted && 
            countdown > 0.f && 
            !gameOver
        )
        {
            countdownText.setString(
                std::to_string(countdownNumber)
            );

            sf::Vector2f size = 
                countdownText.getLocalBounds().size;

            countdownText.setPosition({
                400.f - size.x / 2.f,
                250.f
            });

            window.draw(countdownText);
        }

        if (gamePaused)
        {
            sf::Vector2f size = 
                pauseText.getLocalBounds().size;

            pauseText.setPosition({
                400.f - size.x / 2.f, 
                270.f
            });

            window.draw(pauseText);
        }

        if (gameOver)
        {
            if (scorer >= WIN_SCORE)
            {
                winText.setString(
                    "RIGHT PLAYER WON\n\n"
                    "PRESS R TO RESTART"
                );                
            }
            else
            {
                winText.setString(
                    "LEFT PLAYER WON\n\n"
                    "PRESS R TO RESTART"
                );
            }

            sf::Vector2f size = 
            winText.getLocalBounds().size;

            winText.setPosition({
                400.f - size.x / 2.f, 
                230.f
            });

            window.draw(winText);

        }

        window.display();

        }    

    return 0;
}