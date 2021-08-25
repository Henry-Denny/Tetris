#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <Graphics.hpp>

class Tetromino
{
public:
    Tetromino(sf::Vector2i l_squarePositions[4], sf::Color l_colour = sf::Color(255, 255, 255));
    ~Tetromino();

    void Fall();
    void Rotate(bool l_clockwise);

    bool IsFrozen();

private:
    sf::RectangleShape m_rect;
    sf::Vector2i m_position;
    bool m_frozen;
};

#endif