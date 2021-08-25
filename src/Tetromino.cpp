#include "Tetromino.hpp"
#include "Constants.hpp"

Tetromino::Tetromino(std::array<sf::Vector2i, 4> l_squarePositions, bool l_rotatable, sf::Color l_colour)
    : m_squarePositions(l_squarePositions), m_canRotate(l_rotatable)
{
    m_position = sf::Vector2i(game_constants::k_gridSize.x / 2, 0);

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
}

void Tetromino::MoveLeft() { m_position.x -= 1; }
void Tetromino::MoveRight() { m_position.x += 1; }