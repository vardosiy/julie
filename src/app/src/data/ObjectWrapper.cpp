#include "ObjectWrapper.hpp"

//-----------------------------------------------------------------------------

ObjectWrapper::ObjectWrapper(jl::Object& _obj, std::string _name)
	: m_obj(&_obj)
	, m_name(std::move(_name))
{
}

//-----------------------------------------------------------------------------
