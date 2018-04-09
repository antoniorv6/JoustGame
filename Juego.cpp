/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Juego.cpp
 * Author: antonio
 * 
 * Created on 11 de febrero de 2018, 13:46
 */

#include "Juego.hpp"
#include "EstadoJuego.hpp"
#include <stdlib.h>
#include <time.h>

namespace Anto 
{
	Juego::Juego(int width, int height, std::string title)
	{
		srand(time(NULL));
		_datos->ventana.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
		_datos->maquina.NuevoEstado(StateRef (new EstadoJuego (this->_datos)));

		this->Run();
	}

	void Juego::Run()
	{
		float newTime, frameTime, interpolation;

		float currentTime = this->_clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (this->_datos->ventana.isOpen())
		{
			this->_datos->maquina.GestionaCambios();

			newTime = this->_clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			if (frameTime > 0.25f)
			{
				frameTime = 0.25f;
			}

			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= dt)
			{
				this->_datos->maquina.GetEstadoActual()->HandleInput();
				this->_datos->maquina.GetEstadoActual()->Update(dt);
				accumulator -= dt;
			}

			interpolation = accumulator / dt;
			this->_datos->maquina.GetEstadoActual()->Draw(interpolation);
		}
	}
}
