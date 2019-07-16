#ifndef __EXPORT_HPP__
#define __EXPORT_HPP__

//-----------------------------------------------------------------------------

#if !defined(DLL_EXPORT)
#	define EXPORT __declspec(dllimport)
#else
#	define EXPORT __declspec(dllexport)
#endif

//-----------------------------------------------------------------------------

#endif // __EXPORT_HPP__
