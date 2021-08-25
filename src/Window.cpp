#include "Window.hpp"
#include "Constants.hpp"

Window::Window()
{
    sf::Vector2u l_winSize = sf::Vector2u
    (
        game_constants::k_gridSize.x * game_constants::k_squareSize,
        game_constants::k_gridSize.y * game_constants::k_squareSize
    );
    Create(l_winSize);
    Setup(); 
}

Window::~Window() {}

void Window::Create(sf::Vector2u l_winSize)
{
    m_window.create({l_winSize.x, l_winSize.y}, "Tetris");
}

void Window::Setup()
{
    m_done = false;
}

void Window::HandleEvents()
{
    // Implement event polling
    sf::Event ev;
    while (m_window.pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)
        {
            m_done = true;
        }
    }
}

void Window::BeginDraw()
{
    m_window.clear(sf::Color::Black);
}

void Window::EndDraw()
{
    m_window.display();
}

bool Window::IsDone() { return m_done; }
sf::RenderWindow* Window::GetRenderWindow() { return &m_window; }