#include "Game.hpp"
#include "Constants.hpp"

Game::Game() : m_window(&m_tetroMgr)
{
    Setup();
    RestartClock();
}

Game::~Game() {}

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
    if (m_elapsed >= game_constants::k_tickTime)
    {
        Tick();
        m_elapsed -= game_constants::k_tickTime;
    }
}

void Game::Tick()
{
    m_tetroMgr.UpdateTetrominos();
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

Window* Game::GetWindow() { return &m_window; }