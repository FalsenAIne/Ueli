#pragma once
#include "Macro.h"

#include "Network/Layer.h"

#include <vector>

namespace Ueli {

	namespace Network {

		class UELI_API Network
		{
		public:
			Network(int batchSize);
			~Network();

			void AddLayer(int neuronCount);

			void ForwardPass(Math::Matrix& input);
			void BackwardPass();

			int GetBatchSize() const { return m_BatchSize; }
		private:
			std::vector<Layer*> m_Layers;

			int m_BatchSize;
		};

	}
}