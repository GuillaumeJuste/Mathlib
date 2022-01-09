#pragma once

#ifndef MATHLIB_CALLBACK
#define MATHLIB_CALLBACK

#include "Includes.hpp"


typedef void (*errorCallbackFunction)(const char*, const char*, const char*);

namespace Mathlib
{
	class MATHLIBRARY_API Callback
	{
	private:
		static errorCallbackFunction errorCallback;

	public:
	/**
	*	\brief Set Callback function called in case of error
	*
	* 	\param[in] _errorCallback function to call.
	*/
	static void SetErrorCallback(errorCallbackFunction _errorCallback);

	/**
	*	\brief Call the error callback function.
	*
	* 	\param[in] _class class name from which the callback function is called.
	* 	\param[in] _function function from which the callback function is called.
	* 	\param[in] _errorMessage details on the error.
	*/
	static void CallErrorCallback(const char* _class, const char* _function, const char* _errorMessage);
	};
}

#endif