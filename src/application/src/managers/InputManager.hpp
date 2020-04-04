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

	void processKey(int _key, bool _bIsPressed) noexcept;
	bool isPressed(int _key) const noexcept;

private:
	InputManager() = default;
	~InputManager() = default;

	std::unordered_map<int, bool> m_keyStates;
};
