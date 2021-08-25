#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/System.hpp>

#include "Window.hpp"
#include "TetrominoManager.hpp"

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