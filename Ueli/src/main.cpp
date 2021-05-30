#include <iostream>

#include <vector>

#include "Utils/Timer.h"
#include "Utils/Log.h"
#include "Macro.h"
#include "Math/CoreMath.h"

#define X 2

void Hello()
{
	std::cout << "Hello Ueli!" << std::endl;
}

int main()
{
	Utils::Logger::Init();

	std::cout << "Ueli API" << std::endl;
	std::cout << std::endl;

	Utils::Logger::Shutdown();

	return 0;
}