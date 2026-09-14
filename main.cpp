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

    sf::RectangleShape leftPaddle({20.f,100.f});
    sf::RectangleShape rightPaddle({20.f,100.f});
    sf::CircleShape ball(12.f);
    ball.setPosition({388,288});
    
    rightPaddle.setPosition({755,250});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
        if (event->is<sf::Event::Closed>())
            window.close();
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            paddlePos1 -= 0.02;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            paddlePos1 += 0.02;
        }
        leftPaddle.setPosition({25,paddlePos1});
        
    window.clear();
    
    window.draw(leftPaddle);
    window.draw(rightPaddle);
    window.draw(ball);

    window.display();
    }

    
}