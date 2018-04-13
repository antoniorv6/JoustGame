/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enemy.cpp
 * Author: antonio
 * 
 * Created on 17 de febrero de 2018, 12:33
 */

#include "Enemy.hpp"
#include "DEFINICIONES.hpp"
#include "Plataforma.hpp"
#include <iostream>

namespace Anto
{
    Enemy::Enemy(EstructuraJuegoData datos, int tipo, int plataforma): _datos(datos)
    {
         _spriteprinc.setTexture(_datos->g_assets.GetTextura("Personajes"));
        switch (tipo)
        {
            case ENEMY_BASE:
                _spriteprinc.setTextureRect(sf::IntRect(29, 140, 16, 0));
                _spriteprinc.setOrigin(_spriteprinc.getGlobalBounds().width/2,_spriteprinc.getGlobalBounds().height/2);
                _framesAnimacion.push_back(sf::IntRect(303, 38, 16, 20));
                _framesAnimacion.push_back(sf::IntRect(324, 38, 16, 20));
                _framesAnimacion.push_back(sf::IntRect(345, 38, 16, 20));
                _framesAnimacion.push_back(sf::IntRect(368, 38, 16, 20));
                _framesMuerte.push_back(sf::IntRect(217, 11, 16, 20));
                _framesMuerte.push_back(sf::IntRect(239, 16, 16, 8));
                punctuation = 100;
                
            break;
            case ENEMY_PALLADIN:
                 _spriteprinc.setTextureRect(sf::IntRect(29, 140, 16, 0));
                 _spriteprinc.setOrigin(_spriteprinc.getGlobalBounds().width/2,_spriteprinc.getGlobalBounds().height/2);
                 _framesAnimacion.push_back(sf::IntRect(303, 72, 16, 20));
                 _framesAnimacion.push_back(sf::IntRect(324, 72, 16, 20));
                 _framesAnimacion.push_back(sf::IntRect(345, 72, 16, 20));
                 _framesAnimacion.push_back(sf::IntRect(368, 72, 16, 20));
                 _framesMuerte.push_back(sf::IntRect(217, 11, 16, 20));
                 _framesMuerte.push_back(sf::IntRect(239, 16, 16, 8));
                 punctuation = 200;
            break;
                
        }
        
        flap_buffer.loadFromFile(FLAP_SOUND_FILE);
        flap_sound.setBuffer(flap_buffer);
        
        switch(plataforma)
        {
            case 1:
                _spriteprinc.setPosition(600, 620);
            break;
            case 2:
                _spriteprinc.setPosition(510, 150);
            break;
            case 3:
                _spriteprinc.setPosition(1050, 300);
            break;
            case 4:
                _spriteprinc.setPosition(75, 350);
           
        }
        
        _framesAparicion.push_back(sf::IntRect(29, 140, 16, 5));
        _framesAparicion.push_back(sf::IntRect(29, 140, 16, 10));
        _framesAparicion.push_back(sf::IntRect(29, 140, 16, 15));
        _framesAparicion.push_back(sf::IntRect(29, 140, 16, 20));
        
        _spriteprinc.scale(3,3);
        _direccion = 1;
        _direccion_correr = 0;
        _iteradorAnimacion = 0;
        _enemyState = ENEMY_STATE_APPEARING;
        this->tipo = tipo;
    }
    
    void Enemy::Draw()
    {
        _datos->ventana.draw(_spriteprinc);
    }
    
    void Enemy::Update(float dt)
    {
        if(_enemyState != PLAYER_STATE_DEAD)
        {
            if(_enemyState == ENEMY_STATE_FLIGHT)
            {
                _spriteprinc.move((dt * SPEED_PLAYER *_direccion_correr),-FLY_POWER);
                CheckSalida();
                if(_flap_timer.getElapsedTime().asSeconds() > FLY_TIME)
                {
                    if(tipo == ENEMY_PALLADIN)
                    {
                        _spriteprinc.setTextureRect(sf::IntRect(217, 72, 16, 13));
                    }
                    else
                    {
                        _spriteprinc.setTextureRect(sf::IntRect(217, 38, 16, 13));
                    }
                    _flap_timer.restart();
                }
            }
            
            
            if(_enemyState == ENEMY_STATE_APPEARING)
            {
                this->Aparecer();
            }

            if(_enemyState == ENEMY_STATE_STILL)
            {
                this->CambiaDireccion(1);
            }

            if(_enemyState == PLAYER_STATE_MOVING)
            {
                _spriteprinc.move((dt * SPEED_PLAYER *_direccion_correr),0);
                CheckSalida();
            }

            if(_enemyState == PLAYER_STATE_FLAP)
            {
                _spriteprinc.move((dt * SPEED_PLAYER *_direccion_correr),-FLY_POWER);
                CheckSalida();
                if(_flap_timer.getElapsedTime().asSeconds() > FLY_TIME)
                {
                    _enemyState = PLAYER_STATE_FALLING;
                    if(tipo == ENEMY_PALLADIN)
                    {
                        _spriteprinc.setTextureRect(sf::IntRect(217, 72, 16, 13));
                    }
                    else
                    {
                        _spriteprinc.setTextureRect(sf::IntRect(217, 38, 16, 13));
                    }
                }
            }

            if(_enemyState == PLAYER_STATE_FALLING)
            {
                _spriteprinc.move((dt * SPEED_PLAYER *_direccion_correr),GRAVITY);
                CheckSalida();
            }
        }
        else
        {
             _spriteprinc.move((dt * SPEED_PLAYER * 2 *_direccion_correr),0);  
        }
       
    }
    
    void Enemy::CambiaDireccion(int newdir)
    {
        switch(newdir)
        {
            case 2:
                if(_direccion == 2)
                {
                    _spriteprinc.scale(1.0f,1.0f);
                }
                else
                {
                    _spriteprinc.scale(-1.0f,1.0f);
                }
                _direccion_correr = -1.0;
                _direccion = newdir;
                break;
            case 1:
                if(_direccion == 2)
                {
                    _spriteprinc.scale(-1.0f,1.0f);
                }
                else
                {
                    _spriteprinc.scale(1.0f,1.0f);
                }
                _direccion_correr = 1.0;
                _direccion = newdir;
                break;
        }
        if(_enemyState == PLAYER_STATE_STILL)
            _enemyState = PLAYER_STATE_MOVING;
        
        
    }
    
    void Enemy::AnimarMovimiento(float dt)
    {
        if (aniClock.getElapsedTime().asSeconds() > SPEED_ANIMACION / _framesAnimacion.size())
		{
			if (_iteradorAnimacion < _framesAnimacion.size() - 1)
			{
				_iteradorAnimacion++;
			}
			else
			{
				_iteradorAnimacion = 0;
			}

			_spriteprinc.setTextureRect(_framesAnimacion.at(_iteradorAnimacion));

			aniClock.restart();
		}
    }
    
    void Enemy::CheckSalida()
    {
        if(_spriteprinc.getGlobalBounds().left >= _datos->ventana.getSize().x)
        {
            std::cout<<"Me he salido xd"<<endl;
            if(_cambio_lado.getElapsedTime().asSeconds()>CAMBIO_LADO)
            {
                std::cout<<"Cambio el lado"<<endl;
                _spriteprinc.setPosition(0,_spriteprinc.getPosition().y);
                _cambio_lado.restart();
            }
        }
        
        if(_spriteprinc.getGlobalBounds().left + _spriteprinc.getGlobalBounds().width <= 0)
        {
            std::cout<<"Me he salido xd"<<endl;
             
            if(_cambio_lado.getElapsedTime().asSeconds()>CAMBIO_LADO)
             {
                std::cout<<"Cambio el lado"<<endl;
                _spriteprinc.setPosition(_datos->ventana.getSize().x,_spriteprinc.getPosition().y);
                _cambio_lado.restart();
             }
        }
    }
    
    int Enemy::GetActualState()
    {
        return _enemyState;
    }
    
    void Enemy::Fly()
    {
            _flap_timer.restart();
            flap_sound.play();
            if(tipo == ENEMY_PALLADIN)
                    {
                        _spriteprinc.setTextureRect(sf::IntRect(241, 72, 16, 13));
                    }
                    else
                    {
                          _spriteprinc.setTextureRect(sf::IntRect(241, 38, 16, 13));
                    }
          
            _enemyState = PLAYER_STATE_FLAP;
    }
    
    void Enemy::Break()
    {
        if(_enemyState == PLAYER_STATE_MOVING)
        {
            _spriteprinc.move(0,0);
            _enemyState = PLAYER_STATE_STILL;
        }
        else if(_enemyState == PLAYER_STATE_FLAP)
        {
            _spriteprinc.move(0,GRAVITY);
            _enemyState = PLAYER_STATE_FALLING;
        }
    }
    
    void Enemy::ColisionPlataformas(std::vector<sf::Sprite> plataforma)
    {
       bool si = false;
        for(int i = 0; i< plataforma.size(); i++)
        {
            sf::Rect<float> rect1 = _spriteprinc.getGlobalBounds();
            sf::Rect<float> rect2 = plataforma.at(i).getGlobalBounds();
            if(rect2.intersects(rect1))
            {
                this->TrataColision(plataforma.at(i));
                si = true;
            }
        }    
        
        if(si == false)
        {
            if(_enemyState == PLAYER_STATE_MOVING)
            {
                _enemyState = PLAYER_STATE_FALLING;
                
                 if(tipo == ENEMY_PALLADIN)
                    {
                        _spriteprinc.setTextureRect(sf::IntRect(217, 72, 16, 13));
                    }
                    else
                    {
                        _spriteprinc.setTextureRect(sf::IntRect(217, 38, 16, 13));
                    }
            }
        }
    }
    
    void Enemy::TrataColision(sf::Sprite sprite_plat)
    { 
        if(_spriteprinc.getPosition().x <= sprite_plat.getPosition().x)
        {
            if(_enemyState == PLAYER_STATE_FALLING || _enemyState == PLAYER_STATE_FLAP)
            {
                _direccion_correr *= -1;
            }
        }
        if(_spriteprinc.getPosition().x >= sprite_plat.getGlobalBounds().width + sprite_plat.getPosition().x)
        {
            if(_enemyState == PLAYER_STATE_FALLING || _enemyState == PLAYER_STATE_FLAP)
            {
                _direccion_correr *= -1;
            }
        }
        if(sprite_plat.getPosition().y > _spriteprinc.getPosition().y)
        {
            if(_enemyState == PLAYER_STATE_FALLING)
            {
                _enemyState = PLAYER_STATE_STILL;
                _direccion_correr *= -1;
                 if(tipo == ENEMY_PALLADIN)
                    {
                         _spriteprinc.setTextureRect(sf::IntRect(303, 72, 16, 20));
                    }
                    else
                    {
                       _spriteprinc.setTextureRect(sf::IntRect(303, 38, 16, 20));
                    }
                _spriteprinc.setPosition(_spriteprinc.getPosition().x, _spriteprinc.getPosition().y - 20);
            }
        }
    }
    
    void Enemy::Aparecer()
    {
        if (aniClock.getElapsedTime().asSeconds() > SPEED_APARICION / _framesAparicion.size())
		{
			if (_iteradorAnimacion < _framesAparicion.size() - 1)
			{
                                _spriteprinc.setTextureRect(_framesAparicion.at(_iteradorAnimacion));
                                _iteradorAnimacion++;
			}
			else
			{
				 _spriteprinc.setTextureRect(sf::IntRect(303, 38, 16, 20));
                                 _enemyState = PLAYER_STATE_MOVING;
                                 this->CambiaDireccion(1);
                                 _iteradorAnimacion = 0;
                        }

			aniClock.restart();
		}
    }
    
    const sf::Sprite &Enemy::GetSprite() const
    {
        return _spriteprinc;
    }
    
    Enemy::~Enemy()
    {
        std::cout<<"He muerto jueee"<<std::endl;
        for(int i = 0; i<_framesAnimacion.size(); i++)
        {
            _framesAnimacion.erase(_framesAnimacion.begin() + i);
        }
    }
    
    void Enemy::Decidir()
    {
        int decision = rand()%7;
        switch(decision)
        {
            case 0:
                this->CambiaDireccion(1);
            break;
            case 1: 
                this->CambiaDireccion(2);
            break;
            case 2:
                _enemyState = ENEMY_STATE_FLIGHT;
            break;
                
        }
    }
    
    
    void Enemy::AnimarMuerte(float dt)
    {
        if (aniClock.getElapsedTime().asSeconds() > SPEED_ANIMACION / _framesMuerte.size())
		{
			if (_iteradorMuerte < _framesMuerte.size() - 1)
			{
				_iteradorMuerte++;
			}
			else
			{
				_iteradorMuerte = 0;
			}

			_spriteprinc.setTextureRect(_framesMuerte.at(_iteradorMuerte));

			aniClock.restart();
		}
    }
    
    void Enemy::Morir()
    {
        _enemyState = PLAYER_STATE_DEAD;
        _spriteprinc.setTextureRect(_framesMuerte.at(1));
    }
    
    int Enemy::GetPunctuation()
    {
        return punctuation;
    }
}

