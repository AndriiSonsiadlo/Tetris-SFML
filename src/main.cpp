#include <iostream>
#include <SFML/Graphics.hpp>


int main()
{
    std::cout << "SFML Version: " << SFML_VERSION_MAJOR << "."
        << SFML_VERSION_MINOR << "."
        << SFML_VERSION_PATCH << std::endl;

    auto window = sf::RenderWindow(sf::VideoMode({800, 400}), "CMake SFML Project");
    window.setFramerateLimit(165);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color::Blue);

        window.display();
    }
    return 0;
}
