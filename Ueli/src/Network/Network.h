#pragma once
#include "Macro.h"

#include "Network/Layer.h"

#include <vector>

namespace Ueli {

	namespace Network {

		class UELI_API Network
		{
		public:
			Network();
			~Network();

			void Init(int InputNeuronCount, int outputNeuronCount, int batchSize);

			void AddLayer(int neuronCount);

			void ForwardPass();
			void BackwardPass();
		private:
			std::vector<Layer*> m_Layers;
		};

	}
}