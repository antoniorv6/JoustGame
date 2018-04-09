/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Plataforma.cpp
 * Author: antonio
 * 
 * Created on 16 de febrero de 2018, 17:12
 */

#include "Plataforma.hpp"

namespace Anto
{
    Plataforma::Plataforma(EstructuraJuegoData datos): _datos(datos)
    {
            sf::Sprite _principal(_datos->g_assets.GetTextura("Plataformas"));
            sf::Sprite _plana(_datos->g_assets.GetTextura("Plataforma_lisa"));
            _principal.setTextureRect(sf::IntRect(38, 157, 149, 30));
            _principal.setPosition(_datos->ventana.getSize().x/2 - _principal.getGlobalBounds().width/10, _datos->ventana.getSize().y - _principal.getGlobalBounds().height );
            _principal.setOrigin(_principal.getGlobalBounds().width/2, _principal.getGlobalBounds().height/2);
            _principal.scale(3,3);
            _platformSprites.push_back(_principal);
            
            sf::Sprite _1 = _principal;
            _1.setTextureRect(sf::IntRect(64, 40, 70, 9));
            _1.setOrigin(_1.getGlobalBounds().width/2, _1.getGlobalBounds().height/2);
            _1.setPosition(800, 250);
            _1.scale(1.2,1.2);
            _platformSprites.push_back(_1);
            
             sf::Sprite _2 = _principal;
            _2.setTextureRect(sf::IntRect(80, 114, 51, 7));
            _2.setOrigin(_2.getGlobalBounds().width/2, _2.getGlobalBounds().height/2);
            _2.setPosition(890, 500);
            _2.scale(1.2,1.2);
            _platformSprites.push_back(_2);
            
             sf::Sprite _3 = _principal;
            _3.setTextureRect(sf::IntRect(0, 91, 48, 7));
            _3.setOrigin(_3.getGlobalBounds().width/2, _3.getGlobalBounds().height/2);
            _3.setPosition(_3.getGlobalBounds().width+115, 450);
            _3.scale(1.2,1.2);
            _platformSprites.push_back(_3);
            
            
             sf::Sprite _4 = _principal;
            _4.setTextureRect(sf::IntRect(197, 29, 37, 6));
            _4.setOrigin(_4.getGlobalBounds().width/2, _4.getGlobalBounds().height/2);
            _4.scale(1.2,1.2);
            _4.setPosition(1395, 150);
            _platformSprites.push_back(_4);
            
            sf::Sprite _5 = _principal;
            _5.setTextureRect(sf::IntRect(0, 29, 23, 6));
            _5.setOrigin(_5.getGlobalBounds().width/2, _5.getGlobalBounds().height/2);
            _5.scale(1.2,1.2);
            _5.setPosition(125, 160);
            _platformSprites.push_back(_5);
            
            sf::Sprite _6 = _principal;
            _6.setTextureRect(sf::IntRect(200, 91, 34, 6));
            _6.setOrigin(_6.getGlobalBounds().width/2, _5.getGlobalBounds().height/2);
            _6.scale(1.2,1.2);
            _6.setPosition(1350, 450);
            _platformSprites.push_back(_6);
            
            sf::Sprite _7 = _principal;
            _7.setTextureRect(sf::IntRect(157, 83, 50, 8));
            _7.setOrigin(_7.getGlobalBounds().width/2, _5.getGlobalBounds().height/2);
            _7.scale(1.2,1.2);
            _7.setPosition(1200, 400);
            _platformSprites.push_back(_7);
            
            _plana.setOrigin(_plana.getGlobalBounds().width/2, _plana.getGlobalBounds().height/2);
            _plana.setPosition(209, 649);
            _plana.scale(-2.5,2);
            _platformSprites.push_back(_plana);
            
            sf::Sprite _plana2 = _plana;
            _plana2.setPosition(1050, 649);
            _plana2.scale(-1,1);
            _platformSprites.push_back(_plana2);
    } 
    
    void Plataforma::Draw()
    {
        for(int i=0; i<_platformSprites.size(); i++)
        {
            _datos->ventana.draw(_platformSprites.at(i));
        }
    }
    
    const std::vector<sf::Sprite> &Plataforma::GetSprite() const
    {
        return _platformSprites;
    }
}