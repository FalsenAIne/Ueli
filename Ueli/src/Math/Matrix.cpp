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
        //for (int i = 0; i < Rows; i++)
        //{
        //    for (int j = 0; j < Cols; j++)
        //    {
        //        (Data)[i][j] = 0.0f;
        //    }
        //}

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
        float* temp;
      
        Data = (float**)malloc(rows * sizeof(float*));
        UELI_ASSERT(Data, "Cannot alloc Memory");

        temp = (float*)malloc(rows * cols * sizeof(float));
        UELI_ASSERT(temp, "Cannot alloc Memory");
        if (temp == NULL)
        {
            free(Data);
        }

        for (int i = 0; i < rows; i++)
        {
            (Data)[i] = temp + (i) * cols;
        }

	}

	void Matrix::Free()
	{
        for (int i = 0; i < Rows; i++)
        {
            free((Data)[i]);
        }
        free(*Data);
        *Data = NULL;
	}

}