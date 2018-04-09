/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Plataforma.hpp
 * Author: antonio
 *
 * Created on 16 de febrero de 2018, 17:12
 */

#pragma once
#include <SFML/Graphics.hpp>
#include "Juego.hpp"
#include "DEFINICIONES.hpp"
#include <vector>

namespace Anto
{
    class Plataforma
    {
        public:
            Plataforma(EstructuraJuegoData datos);
            void Draw();
            const std::vector<sf::Sprite> &GetSprite() const;
          
        
        private:
            EstructuraJuegoData _datos;
            std::vector<sf::Sprite> _platformSprites;
            
    };
}

