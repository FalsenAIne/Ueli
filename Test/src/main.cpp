#include "Ueli.h"
#include <iostream>

#define X 2

int main()
{
	Utils::Logger::Init();

	std::cout << "Ueli API" << std::endl;
	std::cout << std::endl;

#if 0
	float input[4] = { 1.0f, 2.0f, 3.0f, 2.5f };
	float weights[3][4] = { { 0.2f ,  0.8f , -0.5f ,  1.0f},
							{ 0.5f , -0.91f,  0.26f, -0.5f},
							{-0.26f, -0.27f,  0.17 ,  0.87} };
	float biases[3] = { 2.0f, 3.0f, 0.5f };
	float outputs[3];

	{
		Utils::Timer timer;

		for (int i = 0; i < 3; ++i)
		{
			outputs[i] = input[0] * weights[i][0] + input[1] * weights[i][1] + input[2] * weights[i][2] + input[3] * weights[i][3] + biases[i];
		}

		std::cout << "[ ";
		for (int i = 0; i < 3; ++i)
		{
			std::cout << outputs[i] << " ";
		}
		std::cout << "]" << std::endl;

		UELI_INFO("Scope last : {0} us", timer.ElapsedMicroseconds());
	}
#endif

	std::vector<float>v1;
	std::vector<float>v2;

	for (size_t i = 0; i < 256 * 1024; i++)
	{
		v1.push_back(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / X)));
		v2.push_back(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / X)));
		//v1.push_back(1.0f);
		//v2.push_back(1.0f);
	}

	{
		Utils::Timer timer;

		float dot = Math::Dot<4>(v1.data(), v2.data(), v1.size());

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


	Math::Matrix mat(1000, 1000);
	{
		Utils::Timer timer;

		mat.Zeros();

		UELI_INFO("Matrix.Zesos() has taken : {0} us", timer.ElapsedMicroseconds());
		//std::cout << mat.ToString();
	}
	

	Utils::Logger::Shutdown();

	return 0;
}