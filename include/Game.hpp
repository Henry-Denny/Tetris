#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "Window.hpp"
#include "TetrominoManager.hpp"
#include "InfoBox.hpp"

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
    void ProcessChanges(int l_linesRemoved);

    Window m_window;
    TetrominoManager m_tetroMgr;
    InfoBox m_infoBox;
    sf::Clock m_clock;
    float m_elapsed;
    float m_tickTime;
    sf::Music m_tetrisTheme;

    int m_score;
    int m_level;
    int m_linesRemovedInLvl;
    bool m_lost;
};

#endif