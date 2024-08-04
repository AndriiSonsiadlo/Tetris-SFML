#include <SFML/Graphics.hpp>
#include <iostream>

#define ASSETS_DIR "../assets/"


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

        sf::CircleShape circle(60.f, 30);
        circle.setFillColor(sf::Color(230, 0, 50));
        circle.setOutlineThickness(5.f);
        circle.setOutlineColor(sf::Color(80, 220, 50));
        circle.setPosition({15, 15});
        window.draw(circle);

        sf::CircleShape triangle(60.f, 3);
        triangle.setPosition(circle.getPosition() + sf::Vector2f{150, 0});
        triangle.setFillColor(sf::Color::Yellow);
        window.draw(triangle);

        sf::CircleShape square(60.f, 4);
        square.setPosition(triangle.getPosition() + sf::Vector2f{150, 0});
        square.setFillColor(sf::Color::Red);
        window.draw(square);

        sf::CircleShape octagon(60.f, 8);
        octagon.setPosition(square.getPosition() + sf::Vector2f{150, 0});
        octagon.setFillColor(sf::Color::Cyan);
        window.draw(octagon);

        sf::ConvexShape convex;
        convex.setPointCount(5);

        convex.setPoint(0, sf::Vector2f(0.f, 0.f));
        convex.setPoint(1, sf::Vector2f(150.f, 10.f));
        convex.setPoint(2, sf::Vector2f(120.f, 90.f));
        convex.setPoint(3, sf::Vector2f(30.f, 100.f));
        convex.setPoint(4, sf::Vector2f(5.f, 50.f));

        convex.setFillColor(sf::Color::Black);
        convex.move({1, 150});
        window.draw(convex);

        sf::RectangleShape rectangle(sf::Vector2f(70.f, 100.f));
        rectangle.move({165, 150});
        rectangle.setFillColor(sf::Color(175, 180, 240));
        window.draw(rectangle);

        sf::RectangleShape line_with_thickness(sf::Vector2f(130.f, 5.f));
        line_with_thickness.rotate(sf::degrees(45.f));
        line_with_thickness.setFillColor(sf::Color(15, 180, 140));
        line_with_thickness.move({250, 150});
        window.draw(line_with_thickness);

        sf::Vertex line_without_thickness[] = {
            sf::Vertex(sf::Vector2f(390.f, 240.f)),
            sf::Vertex(sf::Vector2f(470.f, 150.f))
        };
        line_without_thickness->color = sf::Color::Black;
        window.draw(line_without_thickness, 2, sf::PrimitiveType::Lines);

        sf::Texture texture;
        if (const bool textureIsLoaded = texture.loadFromFile(
                ASSETS_DIR "texture.png", false,
                sf::IntRect(sf::Vector2{50, 50}, sf::Vector2{100, 100}));
            !textureIsLoaded)
        {
            std::cerr << "Failed to load texture!" << std::endl;
            return 1;
        }
        sf::Sprite sprite(texture);
        sprite.setPosition({10, 300});

        window.draw(sprite);

        window.display();
    }
    return 0;
}
