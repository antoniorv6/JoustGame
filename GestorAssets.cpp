/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GestorAssets.cpp
 * Author: antonio
 * 
 * Created on 11 de febrero de 2018, 13:33
 */

#include "GestorAssets.hpp"

namespace Anto 
{
	void GestorAssets::CargaTextura(std::string name, std::string fileName)
	{
		sf::Texture tex;

		if (tex.loadFromFile(fileName))
		{
			this->_texturas[name] = tex;
		}
	}

	sf::Texture &GestorAssets::GetTextura(std::string name)
	{
		return this->_texturas.at(name);
	}

	void GestorAssets::CargaFuente(std::string name, std::string fileName)
	{
		sf::Font font;

		if (font.loadFromFile(fileName))
		{
			this->_fuentes[name] = font;
		}
	}

	sf::Font &GestorAssets::GetFuente(std::string name)
	{
		return this->_fuentes.at(name);
	}

}

