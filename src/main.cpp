#include <SFML/Graphics.hpp>
#include <iostream>

#include "const/TileConstants.h"
#include "include/TileManager.h"

#define ASSETS_DIR "../assets/"


int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({800, 600}), "Tetris");
    window.setFramerateLimit(165);

    const auto tilesTexture = std::make_shared<sf::Texture>();
    if (!tilesTexture->loadFromFile(ASSETS_DIR "tiles.png"))
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
        spritesArray.push_back(sf::Sprite(*tilesTexture, Tetris::TileConstants::TILE_BLUE));
    }


    auto tm = TileManager();
    tm.loadTileTexture(ASSETS_DIR "tiles.png");
    auto sprite = tm.createSprite(Tetris::TileConstants::TileColor::BLUE);
    sprite.setPosition({100, 100});

    auto sprite2 = tm.createSprite(Tetris::TileConstants::TileColor::RED);
    tm.moveRelativeTo(sprite2, sprite, Tetris::TileConstants::TileDirection::UP);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>() ||
                (event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code ==
                    sf::Keyboard::Key::Escape))
            {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        window.draw(sprite);
        window.draw(sprite2);
        window.display();
    }
    return 0;
}
