#pragma once

#include <string>

#include "Utils/Log.h"

namespace Math {

	class UELI_API Matrix
	{
	public:
		float** Data;
		int Rows, Cols;

	public:
		Matrix(int rows, int cols);
		~Matrix();

		void Zeros();

		std::string ToString();
	private:
		void Allocate(int rows, int cols);
		void Free();
	};


}