#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    int playerScore = 0;
    int opponentScore = 0;
    float paddleSpeed = 300.0f;
    float ballSpeedx = 200.0f;
    float ballSpeedy = 200.0f;

    sf::RenderWindow window(
        sf::VideoMode({800,600}),
        "Gimpo"
    );

    float ly = 250.0f;
    float ry = 250.0f;
    float bx = 388.0f;
    float by = 288.0f;

    sf::RectangleShape leftPaddle({20.f,100.f});
    sf::RectangleShape rightPaddle({20.f,100.f});
    sf::CircleShape ball(12.f);

    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        while (const std::optional event = window.pollEvent())
        {
        if (event->is<sf::Event::Closed>())
            window.close();
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            ly -= deltaTime * paddleSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            ly += deltaTime * paddleSpeed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            ry -= deltaTime * paddleSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            ry += deltaTime * paddleSpeed;
        }

        bx += deltaTime * ballSpeedx;
        by += deltaTime * ballSpeedy;
        
        if (ly < 0) 
        {
            ly = 0;
        }
        else if (ly > 500) 
        {
            ly = 500;
        }

        if (ry < 0) 
        {
            ry = 0;
        }
        else if (ry > 500) 
        {
            ry = 500;
        }
        
        if (by < 0)
        {
            by = 0;
            ballSpeedy *= -1;
        }
        else if (by > 576){
            by = 576;
            ballSpeedy *= -1;
        }
        
        ball.setPosition({bx,by});

        if (ball.getGlobalBounds().findIntersection(
            leftPaddle.getGlobalBounds()) && bx > 44)
        {
            bx = 45;
            ballSpeedx *= -1;
        }

        if (ball.getGlobalBounds().findIntersection(
            rightPaddle.getGlobalBounds()) && bx < 755)
        {
            bx = 731;
            ballSpeedx *= -1;
        }

        if (ball.getGlobalBounds().findIntersection(
            rightPaddle.getGlobalBounds()) && bx > 755)
        {
            ballSpeedy *= -1;
        }

        if (ball.getGlobalBounds().findIntersection(
            leftPaddle.getGlobalBounds()) && bx < 44)
        {
            ballSpeedy *= -1;
        }


        
        leftPaddle.setPosition({25,ly});
        rightPaddle.setPosition({755,ry});

    window.clear();
    window.draw(leftPaddle);
    window.draw(rightPaddle);
    window.draw(ball);
    window.display();
}}