/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GestorInputs.hpp
 * Author: antonio
 *
 * Created on 11 de febrero de 2018, 13:38
 */

#pragma once

#include <SFML/Graphics.hpp>

namespace Anto
{
	class GestorInputs
	{
	public:
		GestorInputs() {}
		~GestorInputs() {}

                
                int TeclaPulsada(sf::Keyboard::Key key);

	};
}
