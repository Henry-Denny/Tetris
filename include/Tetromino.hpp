#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <array>

#include <SFML/Graphics.hpp>

class Tetromino
{
public:
    Tetromino(std::array<sf::Vector2i, 4> l_squarePositions, bool l_rotatable, sf::Color l_colour = sf::Color(255, 255, 255));
    ~Tetromino();

    void Fall();
    void RotateCW();
    void Draw(sf::RenderWindow *l_win);

    bool IsFrozen();

private:
    sf::RectangleShape m_rect;
    sf::Vector2i m_position;
    std::array<sf::Vector2i, 4> m_squarePositions;
    bool m_frozen;
    bool m_canRotate;
};

#endif