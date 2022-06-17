#pragma once

#ifndef MATHLIB_DLLEXPORT
#define MATHLIB_DLLEXPORT

/**
*	\file DllExport.hpp
*
*	\brief implementation of dll macro.
*/

#ifdef _WIN32
#ifdef MATHLIB_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else //MATHLIB_EXPORTS
#define MATHLIBRARY_API __declspec(dllimport)
#endif //MATHLIB_EXPORTS
#else //_WIN32
#define MATHLIBRARY_API 
#endif //_WIN32

#endif