#pragma once

#include <string>

#include "Utils/Log.h"

namespace Ueli {

	namespace Math {

		class UELI_API Matrix
		{
		public:
			Matrix(int rows, int columns);
			~Matrix();

			void Zeros();
			void Ones();
			void Random();

			//MATH
			void Mul(Matrix& m1, Matrix& m2);
			void Multiply(Matrix& m);
			void Add(Matrix& m);
			void Subtract(Matrix& m);
			void Multiply(float number);
			void Add(float number);
			void Subtract(float number);

			float* GetData() const { return m_Data; }
			int GetRows() const { return m_Rows; }
			int GetColumns() const { return m_Columns; }
			int GetElementCount() const { return m_ElementCount; }

			std::string ToString() const;

			float& operator()(int row, int col)
			{
				UELI_ASSERT(row >= 0 && col >= 0, "Matrix: Indices mustbe positive!");
				UELI_ASSERT(row < m_Rows && col < m_Columns, "Matrix: Indices out of range!");
				return m_Data[row + col * row];
			}

		private:
			int m_Rows, m_Columns;
			int m_ElementCount;

			float* m_Data;
		};

	}
}