#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <array>
#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Constants.hpp"

class TetrominoManager;

class Tetromino
{
public:
    Tetromino(TetrominoManager *l_tetrominoManager, const std::array<sf::Vector2i, 4> &l_squarePositions, sf::Vector2f l_centreOfRotation, sf::Color l_colour = sf::Color(255, 255, 255));
    ~Tetromino();

    bool Fall();
    void RotateCW();
    void MoveRight();
    void MoveLeft();
    void Draw(sf::RenderWindow *l_win);

    std::array<sf::Vector2i, 4> GetTilePositions();

private:
    TetrominoManager *m_tetroMgr;
    sf::RectangleShape m_rect;
    sf::Vector2i m_position;
    std::array<sf::Vector2i, 4> m_squarePositions;
    sf::Vector2f m_CoR;

    bool PassesWall();
    bool IntersectsTetromino();
};

bool intersects(const std::array<sf::Vector2i, 4> &first, const std::array<sf::Vector2i, 4> &second);

#endif