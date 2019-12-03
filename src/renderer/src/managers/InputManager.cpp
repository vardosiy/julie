#include "renderer/managers/InputManager.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

void InputManager::processKey(KeyCodeT _key, bool _isPressed) noexcept
{
	m_keyStates[_key] = _isPressed;
}

//-----------------------------------------------------------------------------

bool InputManager::isPressed(KeyCodeT _key) const noexcept
{
	auto it = m_keyStates.find(_key);
	return it != m_keyStates.end() ? it->second : false;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
