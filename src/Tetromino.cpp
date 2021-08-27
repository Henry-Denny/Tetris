#include "Tetromino.hpp"
#include <iostream>

Tetromino::Tetromino(std::array<sf::Vector2i, 4> l_squarePositions, sf::Vector2f l_centreOfRotation, sf::Color l_colour)
    : m_squarePositions(l_squarePositions), m_CoR(l_centreOfRotation), m_frozen(false)
{
    m_position = sf::Vector2i((game_constants::k_gridSize.x / 2) - 1, 0);

    m_rect.setFillColor(l_colour);
    m_rect.setSize(sf::Vector2f(game_constants::k_squareSize, game_constants::k_squareSize));
    // Causes bugs
    // m_rect.setOutlineThickness(0.5f);
    // m_rect.setOutlineColor(sf::Color::Black);
}

Tetromino::~Tetromino() {}

void Tetromino::Draw(sf::RenderWindow *l_win)
{
    for(auto itr = m_squarePositions.begin(); itr != m_squarePositions.end(); ++itr)
    {
        m_rect.setPosition
        (
            (m_position.x + itr->x) * game_constants::k_squareSize,
            (m_position.y + itr->y) * game_constants::k_squareSize
        );
        l_win->draw(m_rect);
    }
}

void Tetromino::Fall()
{
    m_position.y += 1;
    for (auto relSquarePos : m_squarePositions)
    {
        sf::Vector2i squarePos = m_position + relSquarePos;
        if (squarePos.y >= game_constants::k_gridSize.y - 1) { m_frozen = true; }
    }
}

void Tetromino::MoveLeft() { m_position.x -= 1; }
void Tetromino::MoveRight() { m_position.x += 1; }

void Tetromino::RotateCW()
{
    const double pi = std::acos(-1);
    std::array<sf::Vector2i, 4> projectedSquares;
    for (int i = 0; i < m_squarePositions.size(); ++i)
    {
        sf::Vector2f offset(m_squarePositions[i].x - m_CoR.x, m_squarePositions[i].y - m_CoR.y);
        int projectedX = std::round(m_CoR.x + (std::cos(-pi / 2) * offset.x - std::sin(-pi / 2) * -offset.y));
        int projectedY = std::round(m_CoR.y - (std::sin(-pi / 2) * offset.x + std::cos(-pi / 2) * -offset.y));
        projectedSquares[i] = sf::Vector2i(projectedX, projectedY);
    }
    // Perform necessary checks
    m_squarePositions = projectedSquares;
}

bool Tetromino::IsFrozen() { return m_frozen; }