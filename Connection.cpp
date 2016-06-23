#include "Connection.h"

unsigned Connection::connectionsNumber = 0;

Connection::Connection(double w){

	Connection::connectionsNumber++;
	weight = w;

}

unsigned Connection::getConnectionsNumber(){

	return connectionsNumber;

}
