#ifndef MATHLIB_INCLUDES
#define MATHLIB_INCLUDES

#ifdef MATHLIB_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

#endif