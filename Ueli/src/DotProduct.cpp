#include "DotProduct.h"
#include "Macro.h"


namespace Math {

	
	/*
	template<int Accumulators>
	__forceinline float avx_vertical_multiplication(const float* v1, const float* v2, size_t count)
	{
		UELI_ASSERT(Accumulators >= 1 && Accumulators <= 4, "Incorrect number of accumulators!");
		constexpr int valuesPerLoop = Accumulators * 8;
		UELI_ASSERT(count % valuesPerLoop == 0, "Incorrect count to valuesPerLoop ratio!");

		const float* const v1End = v1 + count;

		// 4 independent accumulators, don't care for "unused variable" warrning for now
		__m256 dot0, dot1, dot2, dot3;

		// For first values we have nothing to do
		{
			__m265 a = _mm256_loadu_ps(v1);
			__m265 b = _mm256_loadu_ps(v2);
			dot0 = _mm256_mul_ps(a, b);

			if constexpr (Accumulators > 1)
			{
				a = _mm256_loadu_ps(v1 + 8);
				b = _mm256_loadu_ps(v2 + 8);
				dot1 = _mm256_mul_ps(a, b);
			}

			if constexpr (Accumulators > 2)
			{
				a = _mm256_loadu_ps(v1 + 16);
				b = _mm256_loadu_ps(v2 + 16);
				dot2 = _mm256_mul_ps(a, b);
			}

			if constexpr (Accumulators > 3)
			{
				a = _mm256_loadu_ps(v1 + 24);
				b = _mm256_loadu_ps(v2 + 24);
				dot2 = _mm256_mul_ps(a, b);
			}

			v1 += valuesPerLoop;
			v2 += valuesPerLoop;
		}

		for (; v1 < v1End; v1 += valuesPerLoop, v2 += valuesPerLoop)
		{
			__m256 a = _mm256_loadu_ps(v1);
			__m256 b = _mm256_loadu_ps(v2);
			dot0 = _mm_fmadd_ps(a, b, dot0);

			if constexpr (Accumulators > 1)
			{
				a = _mm256_loadu_ps(v1 + 8);
				b = _mm256_loadu_ps(v2 + 8);
				dot1 = _mm_fmadd_ps(a, b, dot1);
			}

			if constexpr (Accumulators > 2)
			{
				a = _mm256_loadu_ps(v1 + 16);
				b = _mm256_loadu_ps(v2 + 16);
				dot2 = _mm_fmadd_ps(a, b, dot2);
			}

			if constexpr (Accumulators > 3)
			{
				a = _mm256_loadu_ps(v1 + 24);
				b = _mm256_loadu_ps(v2 + 24);
				dot3 = _mm_fmadd_ps(a, b, dot3);
			}
		}

		//Adding dots using parwise approach for slightly better precission -> (dot0 + dot1) + (dot2 + dot3)
		if constexpr (Accumulators > 1)
			dot0 = _mm256_add_ps(dot0, dot1);
		if constexpr (Accumulators > 3)
			dot2 = _mm256_add_ps(dot2, dot3);
		if constexpr (Accumulators > 2)
			dot0 = _mm256_add_ps(dot0, dot2);

		// horizontal summ of 8 floats from 256 register using helper function
		return hadd_ps(dot0);
	}

	//template<int AccumulatorsT>
	//float DotProduct(const float* v1, const float* v2, size_t count)
	//{
	//	return avx_vertical_multiplication<T>(v1, v2, count);
	//}

	*/

}