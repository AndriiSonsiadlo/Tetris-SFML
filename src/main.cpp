#include <SFML/Graphics.hpp>
#include <iostream>

#define ASSETS_DIR "../assets/"


int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({800, 600}), "Tetris");
    window.setFramerateLimit(165);

    const auto tiles = std::make_shared<sf::Texture>();
    if (!tiles->loadFromFile(ASSETS_DIR "tiles.png"))
    {
        std::cerr << "Error loading texture" << std::endl;
        return -1;
    }

    constexpr int tileCount = 8;
    std::vector<sf::Sprite> spritesArray;
    spritesArray.reserve(tileCount);
    for (int i = 0; i < tileCount; ++i)
    {
        constexpr int tileSize = 30;
        sf::IntRect rect({i * tileSize, 0}, {tileSize, tileSize});
        spritesArray.push_back(sf::Sprite(*tiles, rect));
        spritesArray.back().move({i * 30.f, 0});
    }


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        for (const auto& sprite : spritesArray)
            window.draw(sprite);

        window.display();
    }
    return 0;
}
