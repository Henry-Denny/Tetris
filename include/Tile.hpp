#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>

struct Tile
{
public:
    Tile() : empty(true) {}

    bool empty;
    sf::Color colour;
};

#endif