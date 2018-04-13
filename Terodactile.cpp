#include "DEFINICIONES.hpp"
#include "Terodactile.hpp"
#include <math.h>
#include<iostream>


namespace Anto
{
    Terodactile::Terodactile(EstructuraJuegoData l_datos):m_datos(l_datos)
    {
       mainSprite.setTexture(m_datos->g_assets.GetTextura("Personajes"));
       mainSprite.setTextureRect(sf::IntRect(43,180,25,7));
       
       mainSprite.setPosition(0,320);
       
       animationSprites.push_back(sf::IntRect(43,180,25,7));
       animationSprites.push_back(sf::IntRect(74,175,24,10));
       
       mainSprite.scale(2.5,2.5);
       
       _iteradorAnimacion = 0;
       
       y = TERODACTILE_AMPLITUDE*std::sin((2*3.1416)/4);
       
       xPeriodTimes = 1;
       
       terodactileState = TERODACTILE_NOAPPEAR;
       
       terodactileBuffer.loadFromFile(TERODACTILE_SOUND_FILE);
       terodactileSound.setBuffer(terodactileBuffer);
    }
    
    void Terodactile::Animate()
    {
        if (aniClock.getElapsedTime().asSeconds() > SPEED_ANIMATION_TERODACTILE /  animationSprites.size())
		{
			if (_iteradorAnimacion < animationSprites.size() - 1)
			{
				_iteradorAnimacion++;
			}
			else
			{
				_iteradorAnimacion = 0;
			}

			mainSprite.setTextureRect(animationSprites.at(_iteradorAnimacion));

			aniClock.restart();
		}
    }
    
    void Terodactile::Update(float dt)
    {
        if(terodactileState == TERODACTILE_APPEAR)
        {
            CalculateY();
            mainSprite.move(2.0,y);
        }
    }
    
    bool Terodactile::ColisionPlayer(const sf::Sprite& player)
    {
        if(mainSprite.getGlobalBounds().intersects(player.getGlobalBounds()))
            return true;
        return false;
    }
    
    void Terodactile::CalculateY()
    {   
        if(moveTime.getElapsedTime().asSeconds()>xPeriodTimes*TERODACTILE_PERIOD)
        {
            if(terodactileState==TERODACTILE_APPEAR)
                terodactileSound.play();
            xPeriodTimes++;
            y*=-1;
        }
            
    }
    
    void Terodactile::Draw()
    {
        if(terodactileState == TERODACTILE_APPEAR)
        {
            this->Animate();
            m_datos->ventana.draw(mainSprite);
        }
    }
    
    void Terodactile::ChangeState(int value)
    {
        terodactileState = value;
    }
    
    void Terodactile::Reposition()
    {
        mainSprite.setPosition(0,320);
    }
}
