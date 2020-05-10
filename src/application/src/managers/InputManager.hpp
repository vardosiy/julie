#pragma once

#include "utils/Singleton.hpp"

#include <unordered_map>

class InputManager : public utils::Singleton<InputManager>
{
	friend class utils::Singleton<InputManager>;

public:
	enum Arrows
	{
		Left = 37,
		Up,
		Right,
		Down
	};

	enum Modifiers
	{
		None	= 0,
		Ctrl	= 1 << 0,
		Alt		= 1 << 1,
		Shift	= 1 << 2
	};

	void keyPressed(int _key) noexcept;
	void keyReleased(int _key) noexcept;
	bool isPressed(int _key) const noexcept;

	Modifiers getModifiers() const noexcept;
	void setModifiers(Modifiers _modifiers) noexcept;

	bool isCtrlPressed() const noexcept;
	bool isAltPressed() const noexcept;
	bool isShiftPressed() const noexcept;

private:
	InputManager() = default;
	~InputManager() = default;

	std::unordered_map<int, bool> m_keyStates;

	Modifiers m_modifiers;
};
