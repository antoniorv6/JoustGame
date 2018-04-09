/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enemy.hpp
 * Author: antonio
 *
 * Created on 17 de febrero de 2018, 12:33
 */

#pragma once
#include <SFML/Graphics.hpp>
#include "Juego.hpp"
#include "DEFINICIONES.hpp"
#include <vector>

namespace Anto
{
    class Enemy
    {
        public:
            Enemy(EstructuraJuegoData datos, int tipo, int plataforma);
            ~Enemy();
            void Draw();
            void Update(float dt);
            void CambiaDireccion(int newdir);
            void AnimarMovimiento(float dt);
            void AnimarMuerte(float dt);
            void CheckSalida();
            int GetActualState();
            void Fly();
            void Break();
            void ColisionPlataformas(std::vector<sf::Sprite> plataforma);
            void TrataColision(sf::Sprite sprite_plat);
            void SpawnEnemigo(int tipo);
            void Aparecer();
            const sf::Sprite &GetSprite() const;
            void Decidir();
            void Flapea(int rep);
            void Morir();
            void Respawn();
    
        private:
            EstructuraJuegoData _datos;
            sf::Sprite _spriteprinc;
            int tipo;
            int _direccion;
            float _direccion_correr;
            std::vector<sf::IntRect> _framesAnimacion;
            std::vector<sf::IntRect> _framesAparicion;
            std::vector<sf::IntRect> _framesMuerte;
	    unsigned int _iteradorAnimacion;
            unsigned int _iteradorAparicion;
            unsigned int _iteradorMuerte;
            int _enemyState;
            sf::Rect<float> _colisionador;	
            sf::Clock aniClock;
            sf::Texture _textura;
            sf::Clock _cambio_lado;
            sf::Clock _flap_timer;
            sf::Clock _appearanim;
            sf::Sprite _aparicion; 
            
    };
}
