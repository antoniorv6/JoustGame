/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State.hpp
 * Author: antonio
 *
 * Created on 11 de febrero de 2018, 13:27
 */

#pragma once

namespace Anto
{
	class State
	{
	public :
		virtual void Init() = 0;

		virtual void HandleInput() = 0;

		virtual void Update(float dt) = 0;

		virtual void Draw( float dt ) = 0;

		virtual void Pause() {}

		virtual void Resume() { }
	};
}