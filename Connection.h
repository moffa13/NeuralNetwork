#ifndef CONNECTION_H
#define CONNECTION_H

class Connection{

public:
	
	Connection(double w = 0);

	static unsigned getConnectionsNumber();

	double weight;

	double deltaWeight;

private:

	static unsigned connectionsNumber;

};


#endif