#include "Ueli.h"
#include <iostream>

#include "Config.h"

#ifndef UELI_TEST

#define X 2

int main()
{
	Utils::Logger::Init();

	std::cout << "Ueli API" << std::endl;
	std::cout << std::endl;

	std::vector<float>v1;
	std::vector<float>v2;

	for (size_t i = 0; i < 256 * 1024; i++)
	{
		v1.push_back(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / X)));
		v2.push_back(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / X)));
	}

	{
		Utils::Timer timer;

		float dot = Ueli::Math::Dot<4>(v1.data(), v2.data(), v1.size());

		UELI_INFO("Vectorized scope last : {0} us", timer.ElapsedMicroseconds());

		UELI_TRACE("Dot product is equal {0}", dot);
	}

	std::cout << std::endl;

	{
		Utils::Timer timer;

		float dot = 0;

		for (size_t i = 0; i < 256 * 1024; i++)
		{
			dot += v1[i] * v2[i];
		}

		UELI_INFO("Scalar scope last : {0} us", timer.ElapsedMicroseconds());

		UELI_TRACE("Dot product is equal {0}", dot);
	}


	
	Ueli::Math::Matrix mat(1000, 1000);
	{
		Utils::Timer timer;
		mat.Zeros();

		UELI_INFO("Matrix.Zesos() has taken : {0} us", timer.ElapsedMicroseconds());
		//std::cout << mat.ToString();
	}


	Utils::Logger::Shutdown();

	return 0;
}

#endif // !UELI_TEST