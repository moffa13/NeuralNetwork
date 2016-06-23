#include "Network.h"
#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

Network::Network(const vector<unsigned> &model){

	unsigned totalLayers = 0;
	unsigned totalNeuron = 0;

	m_model = model;

	for (unsigned i = 0; i < model.size(); ++i){
		unsigned number = model[i];
		m_layers.push_back(Layer());
		cout << "Added a new layer" << endl;
		totalLayers++;

		unsigned outputNumber = (i == model.size() - 1) ? 0 :  model[i + 1];

		for (unsigned a = 0; a < number + 1; ++a){

			if (a == number)
				cout << "Added a new Neuron (BIAS)" << endl;
			else
				cout << "Added a new Neuron" << endl;
			totalNeuron++;
				
			m_layers.back().push_back(Neuron(outputNumber, a));
			
		}

		m_layers.back().back().setOutputValue(1.0);

	}

	cout << "Total of " << totalLayers << " layers and " << totalNeuron << " neurons with a total of " << Connection::getConnectionsNumber() << " connections" << endl;

}

void Network::feedForward(const vector<double> &inputValues){

	assert(m_layers[0].size() - 1 == inputValues.size()); // Be sure we have the same neurons number in input as <inputValues> 

	for (unsigned i = 0; i < inputValues.size(); ++i){ // Set output to the neurons in the first layer (our inputs)

		m_layers[0][i].setOutputValue(inputValues[i]);

	}

	for (unsigned i = 1; i < m_layers.size(); ++i){ // For each layer in the network except the first

		Layer &previousLayer = m_layers[i - 1];

		for (unsigned a = 0; a < m_layers[i].size() - 1; ++a){ // each neuron in the above layer

			m_layers[i][a].feedForward(previousLayer);

		}

	}

}

void Network::training(const vector<double> &expectedValues){

	assert(m_layers.back().size() - 1 == expectedValues.size()); // Be sure we have the same neurons number in output as <expectedValues> 

	Layer &lastLayer = m_layers.back();

	double sum = 0.0;

	for (unsigned i = 0; i < lastLayer.size() - 1; ++i) {

		double delta = expectedValues[i] - lastLayer[i].getOutputValue();

		lastLayer[i].setGradient(delta);

		sum += pow(delta, 2);

	}

	sum /= lastLayer.size() - 1;

	m_error = sqrt(sum); // Network error rate

	for (unsigned i = m_layers.size() - 2; i > 0; --i) {

		for (unsigned a = 0; a < m_layers[i].size(); ++a) {

			m_layers[i][a].calculateGradient(m_layers[i + 1]);

		}

	} 

	for (unsigned i = m_layers.size() - 1; i > 0; --i) {

		for (unsigned a = 0; a < m_layers[i].size() - 1; ++a) {

			m_layers[i][a].calculateWeights(m_layers[i - 1]);

		}

	}


}

void Network::getResults(std::vector<double>& results) const{

	results.clear();
	for (unsigned i = 0; i < m_layers.back().size() - 1; ++i) {

		results.push_back(m_layers.back()[i].getOutputValue());

	}

}

vector<Connection> Network::getConnections() const {

	vector<Connection> fin;

	for (unsigned i = 0; i < m_layers.size(); ++i) {
		Layer const &l = m_layers[i];
		for (unsigned b = 0; b < l.size(); ++b) {
			Neuron const &neuron = l[b];
			vector<Connection> connections = neuron.getConnections();
			for (unsigned c = 0; c < connections.size(); ++c) {
				Connection &connection = connections[c];
				fin.push_back(connection);
			}
		}

	}

	return fin;

}

Network Network::read(std::string const filename){

	ifstream file(filename, ios::beg | ios::binary);

	vector<unsigned> model;

	while (true) { // Get model 

		int c = Network::readByte(file);

		if (c == 0x1C) {
			c = Network::readByte(file);
			if (c == 0x1C) {
				break;
			}
		}

		model.push_back(c);

	}
	
	Network n(model);

	auto connections = n.getConnections();
	//readByte(file);

	for (unsigned i = 0; i < connections.size(); ++i) {

		double weight = readDouble(file);
		readByte(file);

		cout << "Changing connection " << i << " to weight = " << weight << endl;

		connections[i].weight = weight;

	}

	file.close();

	return n;

}


void Network::writeDouble(ofstream &stream, double d) {

	stream.write(reinterpret_cast<char *>(&d), sizeof(double));

}

void Network::writeByte(ofstream &stream, char c) {

	stream.write(reinterpret_cast<const char *>(&c), sizeof(char));

}


double Network::readDouble(ifstream &stream) {

	char buffer[8];

	stream.read(buffer, 8);

	union charDouble u;
	u.c = buffer;

	return *(u.d);

}

char Network::readByte(ifstream &stream) {

	char buffer[1];

	stream.read(buffer, 1);

	return buffer[0];

}

bool Network::write(std::string const filename) {
	ofstream file(filename, ios::beg | ios::binary);

	if (!file.is_open()) {

		return false;

	}

	for (unsigned i = 0; i < m_model.size(); ++i) {
		unsigned l = m_model[i];
		
		writeByte(file, l);
		writeByte(file, 0x1C);
		
	}

	writeByte(file, 0x1C);

	auto connections = getConnections();

	for (unsigned i = 0; i < connections.size(); ++i) {

		Connection &connection = connections[i];	
		
		writeDouble(file, connection.weight);
		writeByte(file, 0x1C);

	}
	
	file.close();

	return true;
}
