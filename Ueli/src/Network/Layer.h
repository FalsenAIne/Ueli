#pragma once

#include "Macro.h"

#include "Math/Matrix.h"

namespace Ueli {

	namespace Network {

		class UELI_API Layer
		{
		public:
			Layer(int neuronCount, int inputCount);
			~Layer();

			void ForwardPass(Math::Matrix& input);
			void BackwardPass();

			int GetNeuronCount() const { return m_NeuronCount; }

			Math::Matrix GetOutput() { return *m_Sums; }
		private:
			int m_NeuronCount;
			int m_InputCount;

			Math::Matrix* m_Weights;
			Math::Matrix* m_Biases;
			Math::Matrix* m_Sums;
			Math::Matrix* m_Activations;
		};

	}
}