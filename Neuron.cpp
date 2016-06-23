#include "Neuron.h"
#include "utils.h"
#include <iostream>
using namespace std;

double Neuron::learningRate = 0.5;

double Neuron::momentum = 0.5;

Neuron::Neuron(unsigned outputs, unsigned index){

	m_indexInLayer = index;
	m_gradient = 0.0;

	for (unsigned i = 0; i < outputs; ++i){
		m_outputWeights.push_back(Connection());
		m_outputWeights.back().weight = utils::random();
		cout << "Created a connection with " << m_outputWeights.back().weight << " as weight" << endl;
	}

	cout << "Created a neuron" << endl;

}

void Neuron::setOutputValue(double value){

	m_outputValue = value;

}

double Neuron::getOutputValue() const{

	return m_outputValue;

}

void Neuron::feedForward(const Layer &previousLayer){

	double sum = 0.0;

	for (unsigned i = 0; i < previousLayer.size(); ++i){

		Neuron const &neuron = previousLayer[i];

		sum += neuron.getOutputValue() * neuron.m_outputWeights[m_indexInLayer].weight;


	}

	setOutputValue(utils::sigmoid(sum));

}

void Neuron::calculateGradient(Layer const & nextLayer){

	double weightGradientSum = 0.0;
	
	for (unsigned i = 0; i < nextLayer.size() - 1; i++) {

		weightGradientSum += m_outputWeights[i].weight * nextLayer[i].m_gradient;

	}

	m_gradient = utils::sigmoidDerivate(m_outputValue) * weightGradientSum;

}

void Neuron::calculateWeights(Layer &previousLayer){

	//unsigned iterationForgetBias = 

	for (unsigned i = 0; i < previousLayer.size(); ++i) {

		Neuron &neuron = previousLayer[i];

		double oldDeltaWeight = neuron.m_outputWeights[m_indexInLayer].deltaWeight;

		double newDeltaWeight = Neuron::learningRate * neuron.m_outputValue * m_gradient;

		neuron.m_outputWeights[m_indexInLayer].weight += newDeltaWeight;

		neuron.m_outputWeights[m_indexInLayer].deltaWeight = newDeltaWeight;


	}

}
