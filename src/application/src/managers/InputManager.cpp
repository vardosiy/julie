#include "managers/InputManager.hpp"

//-----------------------------------------------------------------------------

void InputManager::processKey(int _key, bool _isPressed) noexcept
{
	m_keyStates[_key] = _isPressed;
}

//-----------------------------------------------------------------------------

bool InputManager::isPressed(int _key) const noexcept
{
	auto it = m_keyStates.find(_key);
	return it != m_keyStates.end() ? it->second : false;
}

//-----------------------------------------------------------------------------
