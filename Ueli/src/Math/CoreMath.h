#pragma once

#include <smmintrin.h>
#include <immintrin.h>
#include <xmmintrin.h>

#include "Macro.h"

namespace Math {

	// Horizontal sum of 4 lanes of the vector
	__forceinline float hadd_ps(__m128 r4)
	{
		// Add 4 values into 2
		const __m128 r2 = _mm_add_ps(r4, _mm_movehl_ps(r4, r4));
		// Add 2 lower values into the final result
		const __m128 r1 = _mm_add_ss(r2, _mm_movehdup_ps(r2));
		// Return the lowest lane of the result vector.
		// The intrinsic below compiles into noop, modern compilers return floats in the lowest lane of xmm0 register.
		return _mm_cvtss_f32(r1);
	}

	// Horizontal sum of 8 lanes of the vector
	__forceinline float hadd_ps(__m256 r8)
	{
		const __m128 low = _mm256_castps256_ps128(r8);
		const __m128 high = _mm256_extractf128_ps(r8, 1);
		return hadd_ps(_mm_add_ps(low, high));
	}

	template<int Accumulators>
	float Dot(const float* v1, const float* v2, size_t count)
	{
		UELI_ASSERT(Accumulators >= 1 && Accumulators <= 4, "Incorrect number of accumulators!");
		constexpr int valuesPerLoop = Accumulators * 8;
		UELI_ASSERT(count % valuesPerLoop == 0, "Incorrect count to valuesPerLoop ratio!");

		const float* const v1End = v1 + count;

		// 4 independent accumulators, don't care for "unused variable" warrning for now
		__m256 dot0, dot1, dot2, dot3;

		// For first values we have nothing to do
		{
			__m256 a = _mm256_loadu_ps(v1);
			__m256 b = _mm256_loadu_ps(v2);
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
				dot3 = _mm256_mul_ps(a, b);
			}

			v1 += valuesPerLoop;
			v2 += valuesPerLoop;
		}

		for (; v1 < v1End; v1 += valuesPerLoop, v2 += valuesPerLoop)
		{
			__m256 a = _mm256_loadu_ps(v1);
			__m256 b = _mm256_loadu_ps(v2);
			dot0 = _mm256_fmadd_ps(a, b, dot0);

			if constexpr (Accumulators > 1)
			{
				a = _mm256_loadu_ps(v1 + 8);
				b = _mm256_loadu_ps(v2 + 8);
				dot1 = _mm256_fmadd_ps(a, b, dot1);
			}

			if constexpr (Accumulators > 2)
			{
				a = _mm256_loadu_ps(v1 + 16);
				b = _mm256_loadu_ps(v2 + 16);
				dot2 = _mm256_fmadd_ps(a, b, dot2);
			}

			if constexpr (Accumulators > 3)
			{
				a = _mm256_loadu_ps(v1 + 24);
				b = _mm256_loadu_ps(v2 + 24);
				dot3 = _mm256_fmadd_ps(a, b, dot3);
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

}