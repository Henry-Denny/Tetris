#include "Game.hpp"

Game::Game() : m_window(k_gridSize)
{
    Setup();
    RestartClock();
}

void Game::Setup()
{
    m_tetroMgr.Reset();
    m_score = 0;
    m_lost = false;
}

void Game::HandleInput()
{
    m_window.HandleEvents();
}

void Game::Update()
{
    if (m_elapsed >= k_tickTime)
    {
        Tick();
    }
}

void Game::Tick()
{
    m_tetroMgr.GetCurrentTetromino()->Fall();
    if (m_tetroMgr.GetCurrentTetromino()->IsFrozen())
    {
        m_tetroMgr.CreateRandTetromino();
    }
}

void Game::DrawScene()
{
    m_window.BeginDraw();
    m_tetroMgr.DrawTetrominos(m_window.GetRenderWindow());
    m_window.EndDraw();
}

void Game::RestartClock()
{
    m_elapsed += m_clock.restart().asSeconds();
}