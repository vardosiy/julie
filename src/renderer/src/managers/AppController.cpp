#include "renderer/managers/AppController.hpp"

//-----------------------------------------------------------------------------

IOpenGlContextOwner* AppController::s_contextOwner = nullptr;

//-----------------------------------------------------------------------------

void AppController::setContextOwner(IOpenGlContextOwner* _contextOwner) noexcept
{
	s_contextOwner = _contextOwner;
}

//-----------------------------------------------------------------------------

void AppController::makeContextCurrent()
{
	if (s_contextOwner)
	{
		s_contextOwner->makeContextCurrent();
	}
}

//-----------------------------------------------------------------------------
