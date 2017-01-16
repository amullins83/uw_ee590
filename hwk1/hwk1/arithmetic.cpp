#include <vector>
#include "arithmetic.h"

namespace dmath
{
	// Verifies that matrixC == matrixA + matrixB
	bool verifyAdd(float* matrixA, float* matrixB, float* matrixC, size_t width, size_t height)
	{
		const size_t s = width*height;
		for (size_t i = 0; i < s; i++)
		{
			if (matrixC[i] != matrixA[i] + matrixB[i])
				return false;
		}
		return true;
	}


	// Sequential Add with C++ STL
	// @param[in] pA NxN matrix
	// @param[in] pB NxN matrix
	// @param[out] pC NxN matrix to populate with pA + pB
	void add(const std::vector<float>& pA, const std::vector<float>& pB, std::vector<float>* pC)
	{
		if (pA.empty() || pB.empty() || pA.size() != pB.size() || !pC)
			throw "invalid input";

		const size_t mSize = pA.size();
		for (size_t i = 0; i<mSize; i++)
			(*pC)[i] = pA[i] + pB[i];
	}

	// Sequential Add with C
	void add(float* matrixA, float* matrixB, float* matrixC, size_t width, size_t height)
	{
		const size_t s = width*height;
		for(size_t i=0; i<s; i++)
			matrixC[i] = matrixA[i] + matrixB[i];
	}

	// @param[in] pA scalar value
	// @param[in] pX N length vector
	// @param[in] pY N length vector
	// @param[out] pZ output results of pA*pX+pY
	void saxpy_1d(float pA, float* pX, float* pY, float* pZ, size_t width)
	{
		for (size_t i = 0; i < width; i++)
		{
			pZ[i] = pA*pX[i] + pY[i];
		}
	}

	// @param[in] pA scalar value
	// @param[in] pX N length vector
	// @param[in] pY N length vector
	// @param[out] pZ output results of pA*pX+pY
	void saxpy_1d(float pA, const std::vector<float>& pX, const std::vector<float>& pY, std::vector<float>* pZ)
	{
		if (pX.empty() || pY.empty() || !pZ   // general checks
			|| pX.size() != pY.size())		  // require pX and pY be Nx1
			throw "invalid input";

		const size_t N = pX.size();
		for (size_t i = 0; i < N; i++)
		{
			(*pZ)[i] = pA*pX[i] + pY[i];
		}
	}

	// @param[in] pA MxM matrix of values
	// @param[in] pX MxN matrix of values
	// @param[in] pY MxN matrix of values
	// @param[out] pZ output results of pA*pX+pY
	void saxpy_2d(const std::vector<std::vector<float> >& pA, const std::vector<std::vector<float> >& pX, const std::vector<std::vector<float> >& pY, std::vector<std::vector<float> >* pZ)
	{
		if (pA.empty() || pX.empty() || pY.empty() || !pZ // general checks
			|| pA.size() != pA.front().size()             // require pA MxM in size
			|| pA.size() != pX.size()				 	  // require pX be MxN
			|| pA.size() != pY.size())					  // require pY be MxN
			throw "invalid input";

		const size_t M = pA.size();
		const size_t N = pX.front().size();
		for (size_t row = 0; row < M; row++)
		{
			for (size_t col = 0; col < N; col++)
			{
				// Multiply the row of pA by the column of pX to get the row, column of product.  
				for (size_t inner = 0; inner < M; inner++)
				{
					(*pZ)[row][col] += pA[row][inner] * pX[inner][col];
				}
				// Add pY
				(*pZ)[row][col] += pY[row][col];
			}
		}
	}

	void saxpy_2d(float* pA, float* pX, float* pY, float* pZ, size_t M, size_t N)
	{
		const size_t a_width = M;
		const size_t xyz_width = N;
		for (size_t row = 0; row < M; row++)
		{
			for (size_t col = 0; col < N; col++)
			{
				// Multiply the row of pA by the column of pX to get the row, column of product.  
				const size_t xyz_id = row*xyz_width + col;
				pZ[xyz_id] += pY[xyz_id];
				for (size_t inner = 0; inner < a_width; inner++)
				{
					const size_t innerRowId = row*a_width + inner;
					const size_t innerColId = inner*xyz_width + col;
					pZ[xyz_id] += pA[innerRowId] * pX[innerColId];
				}
			}
		}
	}
} // end namespace dmath