#include <iostream>

#include "Env/Scene.h"
#include "Dots/Dot.h"
#include "Utils.h"

#include <Windows.h>

#include <random>

int main()
{
	int sceneWidth = 50;
	int sceneHeight = 20;
	int dotCount = 5;

	Scene scene(sceneWidth, sceneHeight, dotCount);

	for (int it = 0; true; it++)
	{
		std::cout << it << '\n';
		scene.Update(true);
		scene.DrawScene();
		Sleep(25);
	}

	return 0;
}