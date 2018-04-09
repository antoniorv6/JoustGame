/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EstadoJuego.cpp
 * Author: antonio
 * 
 * Created on 11 de febrero de 2018, 13:53
 */

#include <sstream>
#include "EstadoJuego.hpp"
#include "DEFINICIONES.hpp"
#include <iostream>
namespace Anto
{
	EstadoJuego::EstadoJuego(EstructuraJuegoData datos) : _datos(datos)
	{

	}

	void EstadoJuego::Init()
	{
		_datos->g_assets.CargaTextura("Personajes", PATH_SPRITE);
                _datos->g_assets.CargaTextura("Plataformas", PATH_PLATFORMS);
                _datos->g_assets.CargaTextura("Plataforma_lisa", PATH_PLATFORMS_1);
                _jugador = new Player(_datos);
                _plataformas = new Plataforma(_datos);
                iterador = 0;
                ronda = 0;
                spawneador = 0;
                nuevaronda = true;
	}

	void EstadoJuego::HandleInput()
	{
		sf::Event event;
		while (_datos->ventana.pollEvent(event))
		{
                        int tecla = _datos->g_input.TeclaPulsada(event.key.code);
                        switch(tecla)
                        {
                            case -1:
                                _datos->ventana.close();
                            break;

                            case 1:
                                if(_jugador->GetActualState() != PLAYER_STATE_DEAD)
                                _jugador->CambiaDireccion(tecla);
                            break;

                            case 2:
                                if(_jugador->GetActualState() != PLAYER_STATE_DEAD)
                                _jugador->CambiaDireccion(tecla);
                            break;

                            case 3:
                                if(_jugador->GetActualState() != PLAYER_STATE_DEAD)
                                _jugador->Fly();
                            break;
                            
                            case 6:
                                if(_jugador->GetActualState() != PLAYER_STATE_DEAD)
                                _jugador->Break();
                            break;

                        }
		}
	}

	void EstadoJuego::Update(float dt)
	{
            if(nuevaronda)
            {
                this->NuevaRonda();
            }
                            
            if(_jugador->GetActualState() == PLAYER_STATE_MOVING)
            {
                _jugador->AnimarMovimiento(dt);
            }
            
            if(_jugador->GetActualState() == PLAYER_STATE_DEAD)
            {
                _jugador->AnimarMuerte(dt);
            }
		_jugador->Update(dt);
            
            for(int i = 0; i<_enemigos.size(); i++)
                {
                    if(_enemigos.at(i)->GetActualState() == PLAYER_STATE_MOVING)
                    {
                        _enemigos.at(i)->AnimarMovimiento(dt);
                    }
                    
                    if(_enemigos.at(i)->GetActualState() == PLAYER_STATE_DEAD)
                    {
                        _enemigos.at(i)->Update(dt);
                        _enemigos.at(i)->AnimarMuerte(dt);
                        if(_deadEn.getElapsedTime().asSeconds() > RESPAWN)
                        {
                            delete _enemigos.at(i);
                            _enemigos.erase(_enemigos.begin() + i);
                        }
                    }
                    else
                    {
                        _enemigos.at(i)->Update(dt);

                        if(_enemigos.at(i)->GetActualState() != PLAYER_STATE_DEAD)
                        {
                            if(_decisiones.getElapsedTime().asSeconds() > DECISION)
                            {
                                _enemigos.at(i)->Decidir();
                                _decisiones.restart();
                            }

                            if(_flapea.getElapsedTime().asSeconds()> FLAP)
                            {
                                _enemigos.at(i)->Fly();
                                _flapea.restart();
                            }

                            _enemigos.at(i)->ColisionPlataformas(_plataformas->GetSprite());
                            
                            if(_jugador->GetActualState() != PLAYER_STATE_DEAD && _enemigos.at(i)->GetActualState() != PLAYER_STATE_DEAD)
                            {
                                switch(this->Joust(_jugador->GetSprite(), _enemigos.at(i)->GetSprite()))
                                {
                                    case 1:
                                        _enemigos.at(i)->Morir();
                                        _deadEn.restart();
                                    break;
                                }
                            }
                        }
                    }
                    
                    
                }
                
                
                
                if(_enemigos.size()==0 && !nuevaronda)
                {
                    nuevaronda = true;
                    ronda ++;
                    iterador = 0;
                }
                
                if(_jugador->GetActualState() != PLAYER_STATE_DEAD)
                    _jugador->ColisionPlataformas(_plataformas->GetSprite());
                
                
        }

	void EstadoJuego::Draw(float dt)
	{
		_datos->ventana.clear();
                _jugador->Draw();
                for(int i = 0; i< _enemigos.size(); i++)
                {
                    _enemigos.at(i)->Draw();
                }
                _plataformas->Draw();
		_datos->ventana.display();
	}
        
        void EstadoJuego::SpawnEnemigo(int tipo, int plat)
        {
            Enemy * enemigo = new Enemy(_datos, tipo, plat);
            _enemigos.push_back(enemigo);
        }
        
        int EstadoJuego::Joust(sf::Sprite jugador, sf::Sprite enemigo)
        {
            sf::FloatRect rectjugador = jugador.getGlobalBounds();
            sf::FloatRect rectenemigo = enemigo.getGlobalBounds();
            if(rectjugador.intersects(rectenemigo))
            {
                if(jugador.getPosition().y < enemigo.getPosition().y + 5)
                {
                    return 1;
                }
                else if (jugador.getPosition().y > enemigo.getPosition().y + 5)
                {
                    _jugador->Morir();
                }
                else
                {
                    std::cout<<"Rebotan"<<std::endl;
                }
            }
            
            return 0;
        }
        
        void EstadoJuego::NuevaRonda()
        {
            if(iterador < ronda*2 +1)
            {
                if(_spawnTime.getElapsedTime().asSeconds() > SPAWN_ENEMY)
                {
                    this->SpawnEnemigo(rand()%2, spawneador + 1);
                    if(spawneador < 3)
                    {
                        spawneador ++;
                    }
                    else
                    {
                        spawneador = 0;
                    }
                    iterador++;
                    _spawnTime.restart();
                    std::cout<<"Tiro enemigo"<<std::endl;
                }
            }
            else
            {
                nuevaronda = false;
            }

        }
        
}

