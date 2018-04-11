
#include "Huevo.hpp"
#include "DEFINICIONES.hpp"

#include <iostream>


namespace Anto
{
    Huevo::Huevo(EstructuraJuegoData l_datos, sf::Vector2f l_firstPos):m_data(l_datos)
    {
        m_mainSprite.setTexture(m_data->g_assets.GetTextura("Personajes"));
        m_mainSprite.setTextureRect(sf::IntRect(191,181,6,7));
        m_mainSprite.setPosition(l_firstPos);
        m_mainSprite.scale(2.5,2.5);
        m_eggState = EGG_STATE_FALLING;
    }
    
    void Huevo::Update(float dt)
    {
        if(m_eggState == EGG_STATE_FALLING)
        {
            m_mainSprite.move(5, GRAVITY);
        }
        else
            m_mainSprite.move(0,0);
    }
    
    bool Huevo::Colision(std::vector<sf::Sprite> plataforma)
    {
        for(int i = 0; i< plataforma.size(); i++)
        {
            sf::Rect<float> rect1 = m_mainSprite.getGlobalBounds();
            sf::Rect<float> rect2 = plataforma.at(i).getGlobalBounds();
            if(rect2.intersects(rect1))
            {
                m_eggState = EGG_STATE_PUT;
                return true;
            }
        }
        return false;
    }
    
    bool Huevo::ColisionPlayer(const sf::Sprite& player)
    {
         sf::Rect<float> rect1 = m_mainSprite.getGlobalBounds();
            sf::Rect<float> rect2 = player.getGlobalBounds();
            if(rect2.intersects(rect1))
            {
                return true;
            }
            return false;
    }
    void Huevo::Draw()
    {
        m_data->ventana.draw(m_mainSprite);
    }
}