#pragma once

#include "utils/Singleton.hpp"

#include <unordered_map>

// ASCII key codes for arrows
enum Arrows { Left = 37, Up, Right, Down };

class InputManager : public utils::Singleton<InputManager>
{
	friend class utils::Singleton<InputManager>;

public:
	using KeyCodeType = int;

	void processKey(KeyCodeType _key, bool _bIsPressed) noexcept;
	bool isPressed(KeyCodeType _key) const noexcept;

private:
	std::unordered_map<KeyCodeType, bool> m_keyStates;
};
