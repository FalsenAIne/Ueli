#include "Math/Matrix.h"
#include <memory>
#include <sstream>

#include "Macro.h"

namespace Ueli {

    namespace Math {

        Matrix::Matrix(int rows, int columns)
            : m_Rows(rows), m_Columns(columns), m_ElementCount(rows * columns)
        {
            m_Data = (float*)_aligned_malloc(m_ElementCount * sizeof(float), alignof(float)); //alignof(float)
        }

        Matrix::~Matrix()
        {
            _aligned_free(m_Data);
        }

        void Matrix::Zeros()
        {
            memset(m_Data, 0, m_ElementCount * sizeof(float));
        }

        void Matrix::Ones()
        {
            // version for debuging
            for (int i = 0; i < m_ElementCount; ++i)
                m_Data[i] = 1.0f;
        }

        void Matrix::Random()
        {
            // version for debuging
            for (int i = 0; i < m_ElementCount; ++i)
                m_Data[i] = static_cast <float>(rand() / static_cast <float>(RAND_MAX));
        }

		void Matrix::SetData(float* data, int count)
		{
            UELI_ASSERT(count == m_ElementCount, "Data count does not match element count of matrix");

            for (int i = 0; i < m_ElementCount; ++i)
            {
                m_Data[i] = data[i];

                //UELI_TRACE("m_Data: {0} --- new_Data: {1}", m_Data[i], data[i]);
            }
		}

        void Matrix::Mul(Matrix& m1, Matrix& m2)
        {
            UELI_ASSERT(m1.GetColumns() == m2.GetRows(), "Matrix::Mul: Wrong dimension of the matrices!");
            UELI_ASSERT(this != &m1 && this != &m2, "Matrix::Mul: Destination Matrix must be distinct from given matrices!");

            int sharedDimension = m1.GetColumns();

            for (int r = 0; r < m1.GetRows(); ++r)
            {
                for (int c = 0; c < m2.GetColumns(); ++c)
                {
                    float dot = 0;

                    for (int d = 0; d < sharedDimension; ++d)
                    {
                        dot += m1(r, d) * m2(d, c);
                    }

                    this->operator()(r, c) = dot;
                }
            }
        }

        void Matrix::Multiply(Matrix& m)
        {
            UELI_ASSERT(m_ElementCount == m.GetElementCount(), "Matrix::ElementWise: Different matrices dimension!");
        
            for (int i = 0; i < m_ElementCount; ++i)
                m_Data[i] *= m.GetData()[i];
        }

        void Matrix::Add(Matrix& m)
        {
            UELI_ASSERT(m_ElementCount == m.GetElementCount(), "Matrix::ElementWise: Different matrices dimension!");

            for (int i = 0; i < m_ElementCount; ++i)
                m_Data[i] += m.GetData()[i];
        }

        void Matrix::Subtract(Matrix& m)
        {
            UELI_ASSERT(m_ElementCount == m.GetElementCount(), "Matrix::ElementWise: Different matrices dimension!");

            for (int i = 0; i < m_ElementCount; ++i)
                m_Data[i] -= m.GetData()[i];
        }

        void Matrix::Multiply(float number)
        {
            for (int i = 0; i < m_ElementCount; ++i)
                m_Data[i] *= number;
        }

        void Matrix::Add(float number)
        {
            for (int i = 0; i < m_ElementCount; ++i)
                m_Data[i] += number;
        }

        void Matrix::Subtract(float number)
        {
            for (int i = 0; i < m_ElementCount; ++i)
                m_Data[i] -= number;
        }

        void Matrix::AddVector(Matrix& m)
        {
            UELI_ASSERT(m.GetRows() == 1, "Vector row dimension must be 1!");
            UELI_ASSERT(m_Columns == m.GetColumns(), "Vector lenght must match matrix columns!");

            for (int i = 0; i < m_ElementCount; ++i)
                m_Data[i] += m(0, i % m.GetColumns());
        }

        std::string Matrix::ToString() const
        {
            std::ostringstream oss;

            for (int i = 0; i < m_Rows; i++)
            {
                for (int j = 0; j < m_Columns; j++)
                {
                    oss << m_Data[j + i * m_Columns ] << " ";
                }
            
                oss << std::endl;
            }

            //for (int i = 0; i < m_ElementCount; ++i)
            //    oss << m_Data[i];

            return oss.str();
        }

    }

}
