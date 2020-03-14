#pragma once

#include "renderer/Types.hpp"

#include "utils/Singleton.hpp"

#include <unordered_map>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class InputManager : public utils::Singleton<InputManager>
{
	friend class utils::Singleton<InputManager>;
	
//-----------------------------------------------------------------------------
public:
	using KeyCodeT = s32;

	// ASCII key codes for arrows
	enum Arrows
	{
		Left = 37,
		Up,
		Right,
		Down
	};
	
//-----------------------------------------------------------------------------
	void processKey(KeyCodeT _key, bool _bIsPressed) noexcept;
	bool isPressed(KeyCodeT _key) const noexcept;
	
//-----------------------------------------------------------------------------
private:
	std::unordered_map<KeyCodeT, bool> m_keyStates;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
