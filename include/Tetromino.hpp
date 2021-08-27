#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <array>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "Constants.hpp"

class Tetromino
{
public:
    Tetromino(std::array<sf::Vector2i, 4> l_squarePositions, sf::Vector2f l_centreOfRotation, sf::Color l_colour = sf::Color(255, 255, 255));
    ~Tetromino();

    void Fall();
    void RotateCW();
    void MoveRight();
    void MoveLeft();
    void Draw(sf::RenderWindow *l_win);

    bool IsFrozen();

private:
    sf::RectangleShape m_rect;
    sf::Vector2i m_position;
    std::array<sf::Vector2i, 4> m_squarePositions;
    sf::Vector2f m_CoR;
    bool m_frozen;
};

#endif