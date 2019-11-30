#include "InputManager.hpp"

//-----------------------------------------------------------------------------

void InputManager::processKey(KeyCodeType _key, bool _isPressed) noexcept
{
	m_keyStates[_key] = _isPressed;
}

//-----------------------------------------------------------------------------

bool InputManager::isPressed(KeyCodeType _key) const noexcept
{
	auto it = m_keyStates.find(_key);
	return it != m_keyStates.end() ? it->second : false;
}

//-----------------------------------------------------------------------------
