#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>

class Window
{
public:
    Window(sf::Vector2u l_winSize);
    ~Window();

    void Create(sf::Vector2u l_winSize);
    void Setup();
    void HandleEvents();

    void BeginDraw();
    void EndDraw();

    bool IsDone();
    sf::RenderWindow* GetRenderWindow();

private:
    bool m_done;
    sf::RenderWindow m_window;
};

#endif