#ifndef INFO_BOX_HPP
#define INFO_BOX_HPP

#include <SFML/Graphics.hpp>

class InfoBox
{
public:
    InfoBox(int l_level, int l_score);
    void UpdateValues(int l_level, int l_score);
    void Draw(sf::RenderWindow *l_wind);

private:
    sf::Font m_font;
    sf::Text m_scoreBox;
    sf::Text m_levelBox;
};

#endif