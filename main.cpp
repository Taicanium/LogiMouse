#include <Windows.h>

#include <kernelspecs.h>

#include <iostream>
#include <stdio.h>

#pragma comment (lib, "winmm.lib")

#include <joystickapi.h>

int main()
{
	bool _APPRUNNING = true;
	bool WaitingForButton = true;

	int BUTTON_LEFT = 0;
	int BUTTON_RIGHT = 0;
	int BUTTON_MIDDLE = 0;

	JOYINFO inf;
	MMRESULT mmr;

	bool lmdown = false;
	bool rmdown = false;
	bool mmdown = false;

	int prevX = 0, prevY = 0, prevZ = 0;
	int x = 0, y = 0, z = 0;

	float r = 0;

	std::cout << "Press a button on your joystick to use in place of the left mouse button..." << std::endl;
	while (WaitingForButton)
	{
		mmr = joyGetPos(JOYSTICKID1, &inf);

		if (mmr == 0)
		{
			for (int i = 1; i < 17; i++)
			{
				if (inf.wButtons & i)
				{
					BUTTON_LEFT = i;
					WaitingForButton = false;
				}
			}
		}
	}

	WaitingForButton = true;

	std::cout << "Press a button on your joystick to use in place of the right mouse button..." << std::endl;
	while (WaitingForButton)
	{
		mmr = joyGetPos(JOYSTICKID1, &inf);

		if (mmr == 0)
		{
			for (int i = 1; i < 17; i++)
			{
				if (inf.wButtons & i)
				{
					BUTTON_RIGHT = i;
					WaitingForButton = false;
				}
			}
		}
	}

	WaitingForButton = true;

	std::cout << "Press a button on your joystick to use in place of the middle mouse button..." << std::endl;
	while (WaitingForButton)
	{
		mmr = joyGetPos(JOYSTICKID1, &inf);

		if (mmr == 0)
		{
			for (int i = 1; i < 17; i++)
			{
				if (inf.wButtons & i)
				{
					BUTTON_MIDDLE = i;
					WaitingForButton = false;
				}
			}
		}
	}

	while (_APPRUNNING == true)
	{
		mmr = joyGetPos(JOYSTICKID1, &inf);

		if (mmr == 0)
		{
			r = inf.wZpos / 100000.0f;

			prevX = x;
			prevY = y;
			prevZ = z;

			x = (int)(r * inf.wXpos / 10.0f);
			y = (int)(r * inf.wYpos / 10.0f);
			z = (int)(r * inf.wZpos / 10.0f);

			mouse_event(MOUSEEVENTF_MOVE, (DWORD)(x - prevX), (DWORD)(y - prevY), 0, 0);

			if (inf.wButtons & BUTTON_LEFT)
			{
				if (lmdown == false)
				{
					mouse_event(MOUSEEVENTF_LEFTDOWN, (DWORD)(x - prevX), (DWORD)(y - prevY), 0, 0);
					lmdown = true;
				}
			}
			else
			{
				if (lmdown == true)
				{
					mouse_event(MOUSEEVENTF_LEFTUP, (DWORD)(x - prevX), (DWORD)(y - prevY), 0, 0);
					lmdown = false;
				}
			}

			if (inf.wButtons & BUTTON_RIGHT)
			{
				if (rmdown == false)
				{
					mouse_event(MOUSEEVENTF_RIGHTDOWN, (DWORD)(x - prevX), (DWORD)(y - prevY), 0, 0);
					rmdown = true;
				}
			}
			else
			{
				if (rmdown == true)
				{
					mouse_event(MOUSEEVENTF_RIGHTUP, (DWORD)(x - prevX), (DWORD)(y - prevY), 0, 0);
					rmdown = false;
				}
			}

			if (inf.wButtons & BUTTON_MIDDLE)
			{
				if (mmdown == false)
				{
					mouse_event(MOUSEEVENTF_MIDDLEDOWN, (DWORD)(x - prevX), (DWORD)(y - prevY), 0, 0);
					mmdown = true;
				}
			}
			else
			{
				if (mmdown == true)
				{
					mouse_event(MOUSEEVENTF_MIDDLEUP, (DWORD)(x - prevX), (DWORD)(y - prevY), 0, 0);
					mmdown = false;
				}
			}
		}
	}

	return 0;
}