#ifndef __EXPORT_HPP__
#define __EXPORT_HPP__

//-----------------------------------------------------------------------------

#if !defined(DLL_EXPORT)
#	define DLL_EXPORT __declspec(dllimport)
#else
#	define DLL_EXPORT __declspec(dllexport)
#endif

//-----------------------------------------------------------------------------

#endif // __EXPORT_HPP__
