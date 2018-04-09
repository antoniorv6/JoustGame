/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MaquinaEstados.hpp
 * Author: antonio
 *
 * Created on 11 de febrero de 2018, 13:25
 */

#pragma once

#include <memory>
#include <stack>

#include "State.hpp"

namespace Anto
{
	typedef std::unique_ptr<State> StateRef;

	class MaquinaEstados
	{
	public: 
		MaquinaEstados() {}
		~MaquinaEstados() {}

		void NuevoEstado(StateRef newState, bool isReplacing = true);
		void QuitaEstado();

		void GestionaCambios();

		StateRef &GetEstadoActual();

	private:
		std::stack<StateRef> _states;
		StateRef _newState;
		bool _isRemoving;
		bool _isAdding;
		bool _isReplacing;
	};
}


