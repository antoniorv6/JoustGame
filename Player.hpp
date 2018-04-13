/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.hpp
 * Author: antonio
 *
 * Created on 11 de febrero de 2018, 14:37
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Juego.hpp"
#include "DEFINICIONES.hpp"
#include <vector>

namespace Anto
{
    class Player
    {
        public:
            Player(EstructuraJuegoData datos);
            void Draw();
            void Update(float dt);
            void CambiaDireccion(int newdir);
            void AnimarMovimiento(float dt);
            void AnimarMuerte(float dt);
            void CheckSalida();
            int GetActualState();
            const sf::Sprite &GetSprite() const;
            void Fly();
            void Break();
            void ColisionPlataformas(std::vector<sf::Sprite> plataforma);
            void TrataColision(sf::Sprite sprite_plat);
            void Morir();
            void Respawn();
            bool CheckVida();
            int GetLives();
    
        private:
            EstructuraJuegoData _datos;
            sf::Sprite _spriteprinc;
            
            int _direccion;
            int _vida;
            float _direccion_correr;
            std::vector<sf::IntRect> _framesAnimacion;
            std::vector<sf::IntRect> _framesMuerte;
            
	    unsigned int _iteradorAnimacion;
            unsigned int _iteradorMuerte;
            
            int _playerState;
            sf::Rect<float> _colisionador;
			
            sf::Clock aniClock;
            
            
            sf::Clock _cambio_lado;
            sf::Clock _flap_timer;
            sf::Clock _flap_refresh;
            
            sf::Clock _respawnclock;
            
            sf::SoundBuffer flapBuffer;
            sf::Sound flapSound;
    };
}

