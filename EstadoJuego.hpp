/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EstadoJuego.hpp
 * Author: antonio
 *
 * Created on 11 de febrero de 2018, 13:53
 */

#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Juego.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Plataforma.hpp"
#include <vector>

namespace Anto {
	
	class EstadoJuego : public State
	{
	public:
		EstadoJuego(EstructuraJuegoData datos);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
                
                void SpawnEnemigo(int tipo, int plat);
                int Joust(sf::Sprite jugador, sf::Sprite enemigo);
                
                void NuevaRonda();

	private:
		EstructuraJuegoData _datos;
                
                Player * _jugador;
                Plataforma * _plataformas;
                std::vector<Enemy *> _enemigos;
                
                sf::Clock _decisiones;
                sf::Clock _flapea;
                sf::Clock _deadEn;
                sf::Clock _spawnTime;
                
                int iterador;
                int spawneador;
                int ronda;
                bool nuevaronda;
                
	};
}

