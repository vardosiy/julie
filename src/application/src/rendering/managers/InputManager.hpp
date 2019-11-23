#pragma once

#include "utils/Singleton.hpp"

// ASCII key codes for arrows
enum Arrows : unsigned char { Left = 37, Up, Rigth, Down };

class InputManager : public utils::Singleton<InputManager>
{
	friend class utils::Singleton<InputManager>;

public:
	void processKey(unsigned char _key, bool _bIsPressed) noexcept;
	bool isPressed(unsigned char _key) const noexcept;

private:
	bool m_keyStates[255];
};
