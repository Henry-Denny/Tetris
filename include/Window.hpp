#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>

class TetrominoManager;

class Window
{
public:
    Window(TetrominoManager *l_tetrominoManager);
    ~Window();

    void Create(sf::Vector2u l_winSize);
    void Setup();
    void HandleEvents();

    void BeginDraw();
    void EndDraw();

    void SetDone(bool l_done);
    bool IsDone();
    sf::RenderWindow* GetRenderWindow();

private:
    bool m_done;
    sf::RenderWindow m_window;
    TetrominoManager *m_tetroMgr;
};

#endif