#include "Network/Layer.h"

#include <iostream>

namespace Ueli {

	namespace Network {

		Layer::Layer(int neuronCount, int inputCount, float(*function)(float))
			: m_NeuronCount(neuronCount), m_InputCount(inputCount), p_ActivationFunction(function)
		{
			m_Weights = new Math::Matrix(inputCount, neuronCount);
			m_Weights->Random();

			UELI_INFO("Weights: ");
			std::cout << m_Weights->ToString();
			//m_Weights->Ones();

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
			delete m_Activations;
		}

		void Layer::ForwardPass(Math::Matrix& input)
		{
			m_Sums->Mul(input, *m_Weights);
			m_Sums->AddVector(*m_Biases);

			m_Activations->ApplyFunction(*m_Sums, p_ActivationFunction);
		}

		void Layer::BackwardPass()
		{
		}

	}
}