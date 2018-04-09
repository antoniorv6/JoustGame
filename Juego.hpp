/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Juego.hpp
 * Author: antonio
 *
 * Created on 11 de febrero de 2018, 13:46
 */

#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "MaquinaEstados.hpp"
#include "GestorAssets.hpp"
#include "GestorInputs.hpp"

namespace Anto
{
	struct Controllers
	{
		MaquinaEstados maquina;
		sf::RenderWindow ventana;
		GestorAssets g_assets;
		GestorInputs g_input;
	};

	typedef std::shared_ptr<Controllers> EstructuraJuegoData;

	class Juego
	{
	public: 
		Juego(int width, int height, std::string title);
		
	private:
		const float dt = 1.0f / 60.0f;
		sf::Clock _clock;

		EstructuraJuegoData _datos = std::make_shared<Controllers>();

		void Run();
	};

}

