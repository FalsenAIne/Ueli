#pragma once

#include "Macro.h"

#include "Math/Matrix.h"

namespace Ueli {

	namespace Network {

		class UELI_API Layer
		{
		public:
			Layer(int neuronCount);
			~Layer();

			void ForwardPass();
			void BackwardPass();
		private:
			int m_NeuronCount;

			Math::Matrix* m_Weights;
			Math::Matrix* m_Biases;

			//For debug 
			Math::Matrix* m_Sums;
			Math::Matrix* m_Activations;
		};

	}
}