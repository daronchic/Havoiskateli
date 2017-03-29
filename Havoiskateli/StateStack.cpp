#include "stdafx.h"
#include "StateStack.h"

StateStack::StateStack() {}

void StateStack::pushState(State * state)
{
	m_states.push(state);
}

void StateStack::popState()
{
	if (!m_states.empty()) {
		delete m_states.top();
		m_states.pop();
	}
}

void StateStack::changeState(State *state)
{
	if (!m_states.empty()) {
		popState();
	}
	pushState(state);
}

State * StateStack::peekState()
{
	if (m_states.empty()) {
		return nullptr;
	}
	else {
		return m_states.top();
	}
}
