#include "Math/Matrix.h"
#include <memory>
#include <sstream>

#include "Macro.h"

namespace Math {

	Matrix::Matrix(int rows, int cols)
        : Rows(rows), Cols(cols)
	{
        Data = nullptr;
        Allocate(Rows, Cols);
	}

	Matrix::~Matrix()
	{
        Free();
	}

    void Matrix::Zeros()
    {
        memset(*Data, 0.0f, Rows * Cols * sizeof(float));
    }

    std::string Matrix::ToString()
    {
        std::ostringstream oss;

        for (int i = 0; i < Rows; i++)
        {
            for (int j = 0; j < Cols; j++)
            {
                oss << (Data)[i][j] << " ";
            }

            oss << std::endl;
        }

        return oss.str();
    }

	void Matrix::Allocate(int rows, int cols)
	{ 
        float* block;

        Data = (float**)_aligned_malloc(rows * sizeof(float*), alignof(float*));
        UELI_ASSERT(Data, "Cannot alloc Memory");

        block = (float*)_aligned_malloc(rows * cols * sizeof(float), alignof(float)); //alignof(float)

        UELI_ASSERT(block, "Cannot alloc Memory");
        if (block == NULL)
        {
            free(Data);
        }

        for (int i = 0; i < rows; i++)
        {
            (Data)[i] = block + (i) * cols;
        }

	}

	void Matrix::Free()
	{
        _aligned_free(*Data);
        _aligned_free(Data);
        Data = NULL;
	}

}