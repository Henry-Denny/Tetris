#include "TetrominoManager.hpp"
#include <iostream>

TetrominoManager::TetrominoManager() : m_currentTetromino(nullptr) {}

TetrominoManager::~TetrominoManager()
{
    DeleteTetrominos();
}

void TetrominoManager::DeleteTetrominos()
{
    if (m_currentTetromino)
    {
        delete m_currentTetromino;
        m_currentTetromino = nullptr;
    }

    if (m_frozenTetrominos.empty()) { return; }
    while (m_frozenTetrominos.begin() != m_frozenTetrominos.end())
    {
        delete *(m_frozenTetrominos.begin());
        m_frozenTetrominos.erase(m_frozenTetrominos.begin());
    }
}

void TetrominoManager::Reset()
{
    DeleteTetrominos();
    m_currentTetromino = GetNextTetromino();
}

void TetrominoManager::UpdateTetrominos()
{
    if (!m_currentTetromino->Fall())
    {
        m_frozenTetrominos.push_back(m_currentTetromino);
        m_currentTetromino = GetNextTetromino();
    }
    // If stuck --> freeze tetromino, create new tetromino
}

void TetrominoManager::DrawTetrominos(sf::RenderWindow *l_wind)
{
    for (auto &itr : m_frozenTetrominos)
    {
        itr->Draw(l_wind);
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
            sf::Vector2f(1.5f, 1.5f),
            sf::Color::Cyan
        );
        break;
    case (TetrominoType::J):
        return new Tetromino
        (
            this,
            { sf::Vector2i(0, 0), sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(2, 1) },
            sf::Vector2f(1, 1),
            sf::Color::Blue
        );
        break;
    case (TetrominoType::L):
        return new Tetromino
        (
            this,
            { sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(2, 1), sf::Vector2i(2, 0) },
            sf::Vector2f(1, 1),
            sf::Color(255, 127, 0)
        );
        break;
    case (TetrominoType::O):
        return new Tetromino
        (
            this,
            { sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(2, 0), sf::Vector2i(2, 1) },
            sf::Vector2f(1.5f, 0.5f),
            sf::Color::Yellow
        );
        break;
    case (TetrominoType::S):
        return new Tetromino
        (
            this,
            { sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(1, 0), sf::Vector2i(2, 0) },
            sf::Vector2f(1, 1),
            sf::Color::Green
        );
        break;
    case (TetrominoType::T):
        return new Tetromino
        (
            this,
            { sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(2, 1), sf::Vector2i(1, 0) },
            sf::Vector2f(1, 1),
            sf::Color::Magenta);
        break;
    case (TetrominoType::Z):
        return new Tetromino
        (
            this,
            { sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(2, 1) },
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
    std::cout << "Getting next Tetromino" << std::endl;
    TetrominoType randType = TetrominoType(rand() % int(TetrominoType::Count));
    return CreateTetromino(randType);
}

Tetromino* TetrominoManager::GetCurrentTetromino() { return m_currentTetromino; }
const std::vector<Tetromino*>& TetrominoManager::GetFrozenTetrominos() { return m_frozenTetrominos; }