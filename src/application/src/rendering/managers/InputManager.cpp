#include "rendering/managers/InputManager.hpp"

//-----------------------------------------------------------------------------

void InputManager::processKey(unsigned char _key, bool _isPressed) noexcept
{
	m_keyStates[_key] = _isPressed;
}

//-----------------------------------------------------------------------------

bool InputManager::isPressed(unsigned char _key) const noexcept
{
	return m_keyStates[_key];
}

//-----------------------------------------------------------------------------
