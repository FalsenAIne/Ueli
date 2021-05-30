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


	Ueli::Math::Matrix m1(3, 4);
	float inputData[12] = { 1.0f, 2.0f, 3.0f, 2.5f, 2.0f, 5.0f, -1.0f, 2.0f, -1.5f, 2.7f, 3.3f, -0.8f };
	m1.SetData(inputData, 12);
	UELI_INFO("Inputs x batches");
	std::cout << m1.ToString();

	Ueli::Math::Matrix v(1, 4);
	v.Ones();
	UELI_INFO("Biases");
	std::cout << v.ToString();

	m1.AddVector(v);
	UELI_INFO("Sum");
	std::cout << m1.ToString();

	
	Ueli::Math::Matrix m2(4, 5);
	m2.Random();
	UELI_INFO("Weights");
	std::cout << m2.ToString();

	Ueli::Math::Matrix m3(3,5);
	m3.Mul(m1, m2);
	UELI_INFO("Inputs x Weights");
	std::cout << m3.ToString();
	
	

	Utils::Logger::Shutdown();

	return 0;
}

#endif // !UELI_TEST