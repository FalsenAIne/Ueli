#include "Network/Layer.h"

namespace Ueli {

	namespace Network {

		Layer::Layer(int neuronCount, int inputCount)
			: m_NeuronCount(neuronCount), m_InputCount(inputCount)
		{
			m_Weights = new Math::Matrix(inputCount, neuronCount);
			m_Weights->Random();

			m_Biases = new Math::Matrix(1, neuronCount);
			m_Biases->Zeros();

			m_Sums = new Math::Matrix(3, neuronCount);

			m_Activations = new Math::Matrix(3, neuronCount);
		}

		Layer::~Layer()
		{
			delete m_Weights;
			delete m_Biases;
			delete m_Sums;
			delete m_Biases;
		}

		void Layer::ForwardPass(Math::Matrix& input)
		{
			m_Sums->Mul(input, *m_Weights);
			m_Sums->AddVector(*m_Biases);
		}

		void Layer::BackwardPass()
		{
		}

	}
}