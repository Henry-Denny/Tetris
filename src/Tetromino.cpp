#include "Tetromino.hpp"
#include "TetrominoManager.hpp"
#include <iostream>

Tetromino::Tetromino(TetrominoManager *l_tetrominoManager, const std::array<sf::Vector2i, 4> &l_squarePositions, std::unordered_map<Direction, std::array<sf::Vector2i, 4>> *l_wallKickData, sf::Vector2f l_centreOfRotation, sf::Color l_colour)
    : m_squarePositions(l_squarePositions), m_CoR(l_centreOfRotation), m_tetroMgr(l_tetrominoManager), m_facing(Direction::Up), m_wallKickData(l_wallKickData), m_colour(l_colour)
{
    m_position = sf::Vector2i((game_constants::k_gridSize.x / 2) - 2, -2);

    m_rect.setFillColor(l_colour);
    m_rect.setSize(sf::Vector2f(game_constants::k_squareSize - 3, game_constants::k_squareSize - 3));
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

bool Tetromino::Fall()
{
    int originalY = m_position.y;
    m_position.y += 1;
    if (IntersectsTetromino() || BelowFloor())
    {
        m_position.y = originalY;
        return false;
    }
    return true;
}

void Tetromino::MoveLeft()
{
    int l_originalX = m_position.x;
    m_position.x -= 1;
    if (PassesWall() || IntersectsTetromino()) { m_position.x = l_originalX; }
}
void Tetromino::MoveRight()
{
    int l_originalX = m_position.x;
    m_position.x += 1;
    if (PassesWall() || IntersectsTetromino()) { m_position.x = l_originalX; }
}

void Tetromino::RotateCW()
{
    const double pi = std::acos(-1);
    std::array<sf::Vector2i, 4> originalSquares = m_squarePositions;
    for (int i = 0; i < m_squarePositions.size(); ++i)
    {
        sf::Vector2f offset(m_squarePositions[i].x - m_CoR.x, m_squarePositions[i].y - m_CoR.y);
        int projectedX = std::round(m_CoR.x + (std::cos(-pi / 2) * offset.x - std::sin(-pi / 2) * -offset.y));
        int projectedY = std::round(m_CoR.y - (std::sin(-pi / 2) * offset.x + std::cos(-pi / 2) * -offset.y));
        m_squarePositions[i] = sf::Vector2i(projectedX, projectedY);
    }
    // Perform necessary checks
    const auto &l_wallKickRow = m_wallKickData->at(m_facing);
    int testNum = 0;
    sf::Vector2i originalPos = m_position;
    while (PassesWall() || IntersectsTetromino() || BelowFloor())
    {
        if (testNum >= l_wallKickRow.size())
        {
            // Rotation has failed ==> set position, relative square positions to their original values
            m_position = originalPos;
            m_squarePositions = originalSquares;
            return;
        }

        m_position = originalPos + sf::Vector2i(l_wallKickRow[testNum].x, -l_wallKickRow[testNum].y);

        ++testNum;
    }
    // Rotation has succeeded ==> increment direction
    m_facing = Direction((int(m_facing) + 1) % 4);
}

std::array<sf::Vector2i, 4> Tetromino::GetTilePositions()
{
    std::array<sf::Vector2i, 4> l_tilePositions;
    for (int i = 0; i < l_tilePositions.size(); ++i)
    {
        l_tilePositions[i] = m_position + m_squarePositions[i];
    }
    return l_tilePositions;
}

sf::Color Tetromino::GetColour() { return m_colour; }

bool Tetromino::PassesWall()
{
    for (auto &m_worldSqrPos : GetTilePositions())
    {
        if (m_worldSqrPos.x < 0 || m_worldSqrPos.x >= game_constants::k_gridSize.x) { return true; }
    }
    return false;
}

bool Tetromino::BelowFloor()
{
    for (auto &m_worldSqrPos : GetTilePositions())
    {
        if (m_worldSqrPos.y >= (int)game_constants::k_gridSize.y) { return true; }
    }
    return false;
}

bool Tetromino::IntersectsTetromino()
{
    const auto &frozenTetrominos = m_tetroMgr->GetFrozenTetrominos();
    for (auto &l_tilePos : GetTilePositions())
    {
        if (l_tilePos.y < 0 || l_tilePos.y >= game_constants::k_gridSize.y) { continue; }
        if (!frozenTetrominos[l_tilePos.x][l_tilePos.y]->empty) { return true; }
    }
    return false;
}

bool Tetromino::TouchesCeiling()
{
    for (auto &m_worldSqrPos : GetTilePositions())
    {
        if (m_worldSqrPos.y <= 0) { return true; }
    }
    return false;
}