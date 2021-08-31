#include "InfoBox.hpp"

InfoBox::InfoBox(int l_level, int l_score)
{
    m_font.loadFromFile("./res/otomanopee.ttf");

    m_levelBox.setFont(m_font);
    m_levelBox.setFillColor(sf::Color::White);
    m_levelBox.setCharacterSize(60);
    m_levelBox.setPosition(sf::Vector2f(15, 15));

    m_scoreBox.setFont(m_font);
    m_scoreBox.setFillColor(sf::Color::White);
    m_scoreBox.setCharacterSize(60);
    m_scoreBox.setPosition(sf::Vector2f(15, 80));

    UpdateValues(l_level, l_score);
}

void InfoBox::UpdateValues(int l_level, int l_score)
{
    m_levelBox.setString("Level: " + std::to_string(l_level));
    m_scoreBox.setString("Score: " + std::to_string(l_score));
}

void InfoBox::Draw(sf::RenderWindow *l_wind)
{
    l_wind->draw(m_levelBox);
    l_wind->draw(m_scoreBox);
}