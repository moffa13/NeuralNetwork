#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include "Neuron.h"
#include "typedef.h"
#include <fstream>


typedef union charDouble charDouble;
union charDouble {

	char* c;
	double* d;

};

class Network{


public:

	Network(const std::vector<unsigned> &model);
	void feedForward(const std::vector<double> &inputValues);
	void training(const std::vector<double> &expectedValues);
	void getResults(std::vector<double> &results) const;
	double getError()const { return m_error; }
	std::vector<Layer> const getLayers() const { return m_layers; }
	static Network read(std::string const filename);
	bool write(std::string const filename);

private:

	std::vector<Layer> m_layers;
	std::vector<unsigned> m_model;
	double m_error;
	std::vector<Connection> getConnections() const;
	static void writeDouble(std::ofstream &stream, double d);
	static void writeByte(std::ofstream &stream, char c);
	static double readDouble(std::ifstream &stream);
	static char readByte(std::ifstream &stream);

};

#endif