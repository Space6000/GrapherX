#include "WindowInput.h"
namespace Grapher
{
	bool WindowInput::IsKeyPressed(int key)
	{
		if (GetKeyState(key) & 0x80)
		{
			return true;
		}
		return false;
	}
}