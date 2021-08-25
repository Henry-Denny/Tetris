#include "Window.hpp"

Window::Window(sf::Vector2u l_winSize)
{ 
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