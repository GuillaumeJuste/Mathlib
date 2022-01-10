#include <Misc/Callback.hpp>

namespace Mathlib
{
	errorCallbackFunction Callback::errorCallback = 0;

	void Callback::SetErrorCallback(errorCallbackFunction _errorCallback)
	{
		errorCallback = _errorCallback;
	}

	void Callback::CallErrorCallback(const char* _class, const char* _function, const char* _errorMessage)
	{
		if (errorCallback != 0)
			errorCallback(_class, _function, _errorMessage);
	}
}