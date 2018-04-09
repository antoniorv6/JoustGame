/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.cpp
 * Author: antonio
 * 
 * Created on 11 de febrero de 2018, 14:37
 */

#include "Player.hpp"
#include "DEFINICIONES.hpp"
#include "Plataforma.hpp"
#include <iostream>

namespace Anto
{
    Player::Player(EstructuraJuegoData datos): _datos(datos)
    {
        _spriteprinc.setTexture(_datos->g_assets.GetTextura("Personajes"));
        _spriteprinc.setTextureRect(sf::IntRect(8, 35, 16, 20));
        _spriteprinc.setPosition(_datos->ventana.getSize().x/2.2, _datos->ventana.getSize().y/1.16);
        _spriteprinc.setOrigin(_spriteprinc.getGlobalBounds().width/2,_spriteprinc.getGlobalBounds().height/2);
        _spriteprinc.scale(3,3);
        _iteradorAnimacion = 0;
        _iteradorMuerte = 0;
        
        _framesAnimacion.push_back(sf::IntRect(8, 35, 16, 20));
        _framesAnimacion.push_back(sf::IntRect(28, 35, 16, 20));
        _framesAnimacion.push_back(sf::IntRect(48, 35, 16, 20));
        _framesAnimacion.push_back(sf::IntRect(69, 35, 16, 20));
        
        _framesMuerte.push_back(sf::IntRect(122, 14, 15, 13));
        _framesMuerte.push_back(sf::IntRect(100, 14, 16, 13));
        
        _direccion = 1;
        _direccion_correr = 0;
        _playerState = PLAYER_STATE_STILL;
        _vida = 3;
    }
    
    void Player::Draw()
    {
        _datos->ventana.draw(_spriteprinc);
    }
    
    void Player::Update(float dt)
    {
        if(_playerState != PLAYER_STATE_DEAD)
        {
            if(_playerState == PLAYER_STATE_MOVING)
            {
                _spriteprinc.move((dt * SPEED_PLAYER *_direccion_correr),0);
                CheckSalida();
            }

            if(_playerState == PLAYER_STATE_FLAP)
            {
                _spriteprinc.move((dt * SPEED_PLAYER *_direccion_correr),-FLY_POWER);
                CheckSalida();
                if(_flap_timer.getElapsedTime().asSeconds() > FLY_TIME)
                {
                    _playerState = PLAYER_STATE_FALLING;
                    _spriteprinc.setTextureRect(sf::IntRect(30, 14, 16, 13));
                }
            }

            if(_playerState == PLAYER_STATE_FALLING)
            {
                _spriteprinc.move((dt * SPEED_PLAYER *_direccion_correr),GRAVITY);
                CheckSalida();
            }
        }
        else
        {
             _spriteprinc.move((dt * SPEED_PLAYER * 2 *_direccion_correr),0);
             if(_respawnclock.getElapsedTime().asSeconds() > RESPAWN)
             {
                 this->Respawn();
             }
        }
       
    }
    
    void Player::CambiaDireccion(int newdir)
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
        if(_playerState == PLAYER_STATE_STILL)
            _playerState = PLAYER_STATE_MOVING;
        
        
    }
    
    void Player::AnimarMovimiento(float dt)
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
    
    void Player::CheckSalida()
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
    
    int Player::GetActualState()
    {
        return _playerState;
    }
    
    void Player::Fly()
    {
        if(_flap_refresh.getElapsedTime().asSeconds() > FLY_REFRESH)
        {
            _flap_timer.restart();
            _spriteprinc.setTextureRect(sf::IntRect(8, 14, 16, 13));
            _playerState = PLAYER_STATE_FLAP;
            _flap_refresh.restart();
        }
    }
    
    void Player::Break()
    {
        if(_playerState == PLAYER_STATE_MOVING)
        {
            _spriteprinc.move(0,0);
            _playerState = PLAYER_STATE_STILL;
        }
        else if(_playerState == PLAYER_STATE_FLAP)
        {
            _spriteprinc.move(0,GRAVITY);
            _playerState = PLAYER_STATE_FALLING;
        }
    }
    
    void Player::ColisionPlataformas(std::vector<sf::Sprite> plataforma)
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
            if(_playerState == PLAYER_STATE_MOVING)
            {
                _playerState = PLAYER_STATE_FALLING;
                _spriteprinc.setTextureRect(sf::IntRect(30, 14, 16, 13));
            }
        }
    }
    
    void Player::TrataColision(sf::Sprite sprite_plat)
    { 
        if(sprite_plat.getPosition().y > _spriteprinc.getPosition().y)
        {
            if(_playerState == PLAYER_STATE_FALLING)
            {
                _playerState = PLAYER_STATE_MOVING;
                _spriteprinc.setTextureRect(sf::IntRect(8, 35, 16, 20));
                _spriteprinc.setPosition(_spriteprinc.getPosition().x, _spriteprinc.getPosition().y - 20);
            }
        }
        if(_spriteprinc.getPosition().x <= sprite_plat.getPosition().x)
        {
            if(_playerState == PLAYER_STATE_FALLING || _playerState == PLAYER_STATE_FLAP)
            {
                _direccion_correr *= -1;
            }
        }
        if(_spriteprinc.getPosition().x >= sprite_plat.getGlobalBounds().width + sprite_plat.getPosition().x)
        {
            if(_playerState == PLAYER_STATE_FALLING || _playerState == PLAYER_STATE_FLAP)
            {
                _direccion_correr *= -1;
            }
        }
    }
    
    const sf::Sprite &Player::GetSprite() const
    {
        return _spriteprinc;
    }
    
    void Player::AnimarMuerte(float dt)
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
    
    void Player::Morir()
    {
        _vida--;
        _playerState = PLAYER_STATE_DEAD;
        _spriteprinc.setTextureRect(_framesMuerte.at(1));
        _respawnclock.restart();
    }
    
    void Player::Respawn()
    {
        if(this->CheckVida())
        {
            _spriteprinc.setTextureRect(sf::IntRect(8, 35, 16, 20));
            _spriteprinc.setPosition(_datos->ventana.getSize().x/2.2, _datos->ventana.getSize().y/1.16);
            if(_direccion == 2)
            {
                _spriteprinc.scale(-1.0f,1.0f);
            }
            _direccion = 1;
            _direccion_correr = 1;
            _playerState = PLAYER_STATE_STILL;
        }
    }
    
    bool Player::CheckVida()
        {
            if(_vida > 0)
                return true;
            else
                return false;
        }
    
}

 
