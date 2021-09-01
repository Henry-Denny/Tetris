#include "TetrominoManager.hpp"
#include <iostream>

TetrominoManager::TetrominoManager()
    : m_currentTetromino(nullptr), m_numBlocksInLine(game_constants::k_gridSize.y), m_frozenTetrominos(game_constants::k_gridSize.x, std::vector<Tile*>(game_constants::k_gridSize.y))
{
    m_wallKickDataArr[0].emplace
    (
        Direction::Up,
        std::array<sf::Vector2i, 4>{ sf::Vector2i(-1, 0), sf::Vector2i(-1, 1), sf::Vector2i(0, -2), sf::Vector2i(-1, -2) }
    );
    
    m_wallKickDataArr[0].emplace
    (
        Direction::Right,
        std::array<sf::Vector2i, 4>{ sf::Vector2i(1, 0), sf::Vector2i(1, -1), sf::Vector2i(0, 2), sf::Vector2i(1, 2) }
    );
    m_wallKickDataArr[0].emplace
    (
        Direction::Down,
        std::array<sf::Vector2i, 4>{ sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(0, -2), sf::Vector2i(1, -2) }
    );
    m_wallKickDataArr[0].emplace
    (
        Direction::Left,
        std::array<sf::Vector2i, 4>{ sf::Vector2i(-1, 0), sf::Vector2i(-1, -1), sf::Vector2i(0, 2), sf::Vector2i(-1, 2) }
    );

    m_wallKickDataArr[1].emplace
    (
        Direction::Up,
        std::array<sf::Vector2i, 4>{ sf::Vector2i(-2, 0), sf::Vector2i(1, 0), sf::Vector2i(-2, -1), sf::Vector2i(1, 2) }
    );
    m_wallKickDataArr[1].emplace
    (
        Direction::Right,
        std::array<sf::Vector2i, 4>{ sf::Vector2i(-1, 0), sf::Vector2i(2, 0), sf::Vector2i(-1, 2), sf::Vector2i(2, -1) }
    );
    m_wallKickDataArr[1].emplace
    (
        Direction::Down,
        std::array<sf::Vector2i, 4>{ sf::Vector2i(2, 0), sf::Vector2i(-1, 0), sf::Vector2i(2, 1), sf::Vector2i(-1, -2) }
    );
    m_wallKickDataArr[1].emplace
    (
        Direction::Left,
        std::array<sf::Vector2i, 4>{ sf::Vector2i(1, 0), sf::Vector2i(-2, 0), sf::Vector2i(1, -2), sf::Vector2i(-2, 1) }
    );

    SetupTiles();
}

TetrominoManager::~TetrominoManager()
{
    DeleteTetrominos();
    DeleteTiles();
}

void TetrominoManager::SetupTiles()
{
    for (int i = 0; i < m_frozenTetrominos.size(); ++i)
    {
        for (int j = 0; j < m_frozenTetrominos[i].size(); ++j)
        {
            Tile *tile = new Tile();
            m_frozenTetrominos[i][j] = tile;
        }
    }
}

void TetrominoManager::DeleteTiles()
{
    for (int i = 0; i < m_frozenTetrominos.size(); ++i)
    {
        for (int j = 0; j < m_frozenTetrominos[i].size(); ++j)
        {
            delete m_frozenTetrominos[i][j];
        }
    }
}

void TetrominoManager::DeleteTetrominos()
{
    if (m_currentTetromino)
    {
        delete m_currentTetromino;
        m_currentTetromino = nullptr;
    }
}

void TetrominoManager::Reset()
{
    DeleteTetrominos();
    m_currentTetromino = GetNextTetromino();
    for (auto itr = m_numBlocksInLine.begin(); itr != m_numBlocksInLine.end(); ++itr)
    {
        *itr = 0;
    }
    m_linesRemoved = 0;
}

bool TetrominoManager::Continue()
{
    if (!m_currentTetromino->Fall())
    {
        if (m_currentTetromino->TouchesCeiling())
        {
            return false;
        }

        for (auto &squarePos : m_currentTetromino->GetTilePositions())
        {
            m_frozenTetrominos[squarePos.x][squarePos.y]->empty = false;
            m_frozenTetrominos[squarePos.x][squarePos.y]->colour = m_currentTetromino->GetColour();
        }
        UpdateLines();
        delete m_currentTetromino;
        m_currentTetromino = GetNextTetromino();
    }
    return true;
}

void TetrominoManager::UpdateLines()
{
    auto tilePositions = m_currentTetromino->GetTilePositions();
    int upper = 0;
    int lower = game_constants::k_gridSize.y - 1;
    for (sf::Vector2i tilePos : tilePositions)
    {
        ++m_numBlocksInLine[tilePos.y];
        if (tilePos.y > upper) { upper = tilePos.y; }
        if (tilePos.y < lower) { lower = tilePos.y; }
    }
    
    for (int i = lower; i < upper + 1; ++i)
    {
        if (m_numBlocksInLine[i] == game_constants::k_gridSize.x)
        {
            RemoveLine(i);
            ++m_linesRemoved;
        }
    }
}

void TetrominoManager::RemoveLine(int row)
{
    for (int y = row; y > 0; --y)
    {
        for (int x = 0; x < m_frozenTetrominos.size(); ++x)
        {
            m_frozenTetrominos[x][y]->empty = m_frozenTetrominos[x][y - 1]->empty;
            m_frozenTetrominos[x][y]->colour = m_frozenTetrominos[x][y - 1]->colour;
            m_numBlocksInLine[y] = m_numBlocksInLine[y - 1];
        }
    }
    m_numBlocksInLine[0] = 0;
}

void TetrominoManager::DrawTetrominos(sf::RenderWindow *l_wind)
{
    sf::RectangleShape rect;
    rect.setSize({game_constants::k_squareSize - 3, game_constants::k_squareSize - 3});
    for (int x = 0; x < m_frozenTetrominos.size(); ++x)
    {
        for (int y = 0; y < m_frozenTetrominos[x].size(); ++y)
        {
            sf::Vector2f l_pos(x * game_constants::k_squareSize, y * game_constants::k_squareSize);
            rect.setPosition(l_pos);
            sf::Color l_colour = m_frozenTetrominos[x][y]->empty ? ((x + y + 1) % 5 ? sf::Color(12, 12, 12) : sf::Color(24, 24, 24)) : m_frozenTetrominos[x][y]->colour;
            rect.setFillColor(l_colour);
            l_wind->draw(rect);
        }
    }
    m_currentTetromino->Draw(l_wind);
}

Tetromino* TetrominoManager::CreateTetromino(TetrominoType l_type)
{
    switch (l_type)
    {
    case (TetrominoType::I):
        return new Tetromino
        (
            this,
            { sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(2, 1), sf::Vector2i(3, 1) },
            &m_wallKickDataArr[1],
            sf::Vector2f(1.5f, 1.5f),
            sf::Color::Cyan
        );
        break;
    case (TetrominoType::J):
        return new Tetromino
        (
            this,
            { sf::Vector2i(0, 0), sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(2, 1) },
            &m_wallKickDataArr[0],
            sf::Vector2f(1, 1),
            sf::Color::Blue
        );
        break;
    case (TetrominoType::L):
        return new Tetromino
        (
            this,
            { sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(2, 1), sf::Vector2i(2, 0) },
            &m_wallKickDataArr[0],
            sf::Vector2f(1, 1),
            sf::Color(255, 127, 0)
        );
        break;
    case (TetrominoType::O):
        return new Tetromino
        (
            this,
            { sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(2, 0), sf::Vector2i(2, 1) },
            &m_wallKickDataArr[0],
            sf::Vector2f(1.5f, 0.5f),
            sf::Color::Yellow
        );
        break;
    case (TetrominoType::S):
        return new Tetromino
        (
            this,
            { sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(1, 0), sf::Vector2i(2, 0) },
            &m_wallKickDataArr[0],
            sf::Vector2f(1, 1),
            sf::Color::Green
        );
        break;
    case (TetrominoType::T):
        return new Tetromino
        (
            this,
            { sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(2, 1), sf::Vector2i(1, 0) },
            &m_wallKickDataArr[0],
            sf::Vector2f(1, 1),
            sf::Color::Magenta);
        break;
    case (TetrominoType::Z):
        return new Tetromino
        (
            this,
            { sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(2, 1) },
            &m_wallKickDataArr[0],
            sf::Vector2f(1, 1),
            sf::Color::Red
        );
        break;
    default:
        break;
    }
}

Tetromino* TetrominoManager::GetNextTetromino()
{
    TetrominoType randType = TetrominoType(rand() % int(TetrominoType::Count));
    return CreateTetromino(randType);
}

Tetromino* TetrominoManager::GetCurrentTetromino() { return m_currentTetromino; }
const std::vector<std::vector<Tile*>>& TetrominoManager::GetFrozenTetrominos() { return m_frozenTetrominos; }
int TetrominoManager::GetLinesRemoved()
{
    int temp = m_linesRemoved;
    m_linesRemoved = 0;
    return temp;
}