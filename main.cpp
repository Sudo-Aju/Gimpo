#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({800,600}),
        "Gimpo"
    );

    sf::CircleShape circle(50);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
        if (event->is<sf::Event::Closed>())
            window.close();
        }
        
    window.clear();

    window.draw(circle);

    window.display();
    }

    
}