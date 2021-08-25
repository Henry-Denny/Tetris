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
        std::cout << "1";
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
    m_currentTetromino = CreateRandTetromino();
}

void TetrominoManager::UpdateTetrominos()
{
    m_currentTetromino->Fall();
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
        return new Tetromino({sf::Vector2i(0, -1), sf::Vector2i(0, 0), sf::Vector2i(0, 1), sf::Vector2i(0, 2)}, true, sf::Color::Cyan);
        break;
    case (TetrominoType::J):
        return new Tetromino({sf::Vector2i(0, -1), sf::Vector2i(0, 0), sf::Vector2i(0, 1), sf::Vector2i(-1, 1)}, true, sf::Color::Blue);
        break;
    case (TetrominoType::L):
        return new Tetromino({sf::Vector2i(0, -1), sf::Vector2i(0, 0), sf::Vector2i(0, 1), sf::Vector2i(1, 1)}, true, sf::Color(255, 127, 0));
        break;
    case (TetrominoType::O):
        return new Tetromino({sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(0, 1), sf::Vector2i(1, 1)}, false, sf::Color::Yellow);
        break;
    case (TetrominoType::S):
        return new Tetromino({sf::Vector2i(-1, 0), sf::Vector2i(0, 0), sf::Vector2i(0, -1), sf::Vector2i(1, -1)}, true, sf::Color::Green);
        break;
    case (TetrominoType::T):
        return new Tetromino({sf::Vector2i(1, 0), sf::Vector2i(0, 0), sf::Vector2i(0, -1), sf::Vector2i(-1, -1)}, true, sf::Color::Magenta);
        break;
    default:
        break;
    }
}

Tetromino* TetrominoManager::CreateRandTetromino()
{
    TetrominoType randType = TetrominoType(rand() % int(TetrominoType::Count));
    return CreateTetromino(randType);
}

Tetromino* TetrominoManager::GetCurrentTetromino() { return m_currentTetromino; }