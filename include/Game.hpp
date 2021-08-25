#ifndef GAME_HPP
#define GAME_HPP

#include <System.hpp>

#include "Window.hpp"
#include "TetrominoManager.hpp"

static const float k_tickTime = 0.5f;
static const int k_squareSize = 32;
static const sf::Vector2u k_gridSize(16, 64);

class Game
{
public:
    Game();
    ~Game();

    void Setup();

    void HandleInput();
    void Update();
    void DrawScene();
    void RestartClock();

    Window* GetWindow();

private:
    void Tick();

    Window m_window;
    TetrominoManager m_tetroMgr;
    sf::Clock m_clock;
    float m_elapsed;

    int m_score;
    bool m_lost;
};

#endif