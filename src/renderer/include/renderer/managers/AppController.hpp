#pragma once

class IOpenGlContextOwner
{
public:
	virtual ~IOpenGlContextOwner() = default;

	virtual void makeContextCurrent() = 0;
};

class AppController
{
public:
	static void setContextOwner(IOpenGlContextOwner* _contextOwner) noexcept;
	static void makeContextCurrent();

private:
	static IOpenGlContextOwner* s_contextOwner;
};
