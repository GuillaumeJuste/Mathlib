#pragma once

#ifndef MATHLIB_DLLEXPORT
#define MATHLIB_DLLEXPORT

/**
*	\file DllExport.hpp
*
*	\brief implementation of dll macro.
*/

#ifdef MATHLIB_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

#endif