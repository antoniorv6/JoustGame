/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GestorInputs.cpp
 * Author: antonio
 * 
 * Created on 11 de febrero de 2018, 13:38
 */

#include "GestorInputs.hpp"

namespace Anto
{
    int GestorInputs::TeclaPulsada(sf::Keyboard::Key key)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            return 3;
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            return 2;
        }
        
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            return 1;
        }
        
           if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            return -1;
        }
        
        return 6;
    }
}