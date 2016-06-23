#ifndef NEURON_H
#define NEURON_H

#include "typedef.h"
#include "Connection.h"
#include <vector>

class Neuron{

public:

	Neuron(unsigned outputs, unsigned index);
	void setOutputValue(double value);
	double getOutputValue() const;
	void feedForward(Layer const &previousLayer);
	void setGradient(double gradient) { m_gradient = gradient; }
	void calculateGradient(Layer const &nextLayer);
	void calculateWeights(Layer &previousLayer);
	std::vector<Connection> const getConnections() const { return m_outputWeights; };

private:
		
	double m_outputValue = 0.0;
	unsigned m_indexInLayer;
	static double learningRate;
	static double momentum;
	double m_gradient;
	std::vector<Connection> m_outputWeights;


};

#endif