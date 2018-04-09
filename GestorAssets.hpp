/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GestorAssets.hpp
 * Author: antonio
 *
 * Created on 11 de febrero de 2018, 13:33
 */
#pragma once

#include <map>

#include <SFML/Graphics.hpp>
using namespace std;
namespace Anto
{
	class GestorAssets
	{
	public:
		GestorAssets() {}
		~GestorAssets() {}

		void CargaTextura(string name, string fileName);
		sf::Texture &GetTextura(string name);

		void CargaFuente(string name, string fileName);
		sf::Font &GetFuente(string name);

	private:
		std::map<string, sf::Texture> _texturas;
		std::map<string, sf::Font> _fuentes;
	};
}
