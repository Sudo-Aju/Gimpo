#include <iostream>
#include <SFML/Graphics.hpp>



int main()
{
    int playerScore = 0;
    int opponentScore = 0;
    float paddleSpeed = 300.0f;

    sf::RenderWindow window(
        sf::VideoMode({800,600}),
        "Gimpo"
    );

    float paddlePos1 = 250.0f;
    float paddlePos2 = 250.0f;

    sf::RectangleShape leftPaddle({20.f,100.f});
    sf::RectangleShape rightPaddle({20.f,100.f});
    sf::CircleShape ball(12.f);
    ball.setPosition({388,288});
    
    

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
            paddlePos1 -= deltaTime * paddleSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            paddlePos1 += deltaTime * paddleSpeed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            paddlePos2 -= deltaTime * paddleSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            paddlePos2 += deltaTime * paddleSpeed;
        }

        leftPaddle.setPosition({25,paddlePos1});
        rightPaddle.setPosition({755,paddlePos2});

        sf::Vector2f pos1 = leftPaddle.getPosition();
        sf::Vector2f pos2 = rightPaddle.getPosition();
        
        if (pos1.y < 0) {
            paddlePos1 = 0;
        }
        if (pos1.y > 500) {
            paddlePos1 = 500;
        }

        if (pos2.y < 0) {
            paddlePos2 = 0;
        }
        if (pos2.y > 500) {
            paddlePos2 = 500;
        }
        
    window.clear();
    
    window.draw(leftPaddle);
    window.draw(rightPaddle);
    window.draw(ball);

    window.display();
    }

    
}