#include "managers/InputManager.hpp"

//-----------------------------------------------------------------------------

void InputManager::keyPressed(int _key) noexcept
{
	m_keyStates[_key] = true;
}

//-----------------------------------------------------------------------------

void InputManager::keyReleased(int _key) noexcept
{
	m_keyStates[_key] = false;
}

//-----------------------------------------------------------------------------

bool InputManager::isPressed(int _key) const noexcept
{
	auto it = m_keyStates.find(_key);
	return it != m_keyStates.end() ? it->second : false;
}

//-----------------------------------------------------------------------------

InputManager::Modifiers InputManager::getModifiers() const noexcept
{
	return m_modifiers;
}

//-----------------------------------------------------------------------------

void InputManager::setModifiers(Modifiers _modifiers) noexcept
{
	m_modifiers = _modifiers;
}

//-----------------------------------------------------------------------------

bool InputManager::isCtrlPressed() const noexcept
{
	return m_modifiers & Modifiers::Ctrl;
}

//-----------------------------------------------------------------------------

bool InputManager::isAltPressed() const noexcept
{
	return m_modifiers & Modifiers::Alt;
}

//-----------------------------------------------------------------------------

bool InputManager::isShiftPressed() const noexcept
{
	return m_modifiers & Modifiers::Shift;
}

//-----------------------------------------------------------------------------
