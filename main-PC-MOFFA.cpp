#include "Network.h"
#include <vector>
#include <chrono>
#include <iostream>
#include "utils.h"

using namespace std;

int main(){


	vector<double> firstInput;
	vector<double> secondInput;
	vector<double> output;
	unsigned testsToCreate = 10000;

	for (unsigned i = 0; i < testsToCreate; ++i) {

		int i1 = (int)(2.0 * rand() / double(RAND_MAX));
		int i2 = (int)(2.0 * rand() / double(RAND_MAX));

		firstInput.push_back((double)i1);
		secondInput.push_back((double)i2);
		output.push_back((double)(i1 ^ i2));

	}







	vector<unsigned> model = { 2, 6, 1 };

	//chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	//chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

	//auto duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();

	//cout << "Program executed in " << double(double(duration) / 1000000) << " seconds" << endl;
	Network n(model);
	
	vector<double> results = {};

	for (unsigned i = 0; i < testsToCreate; ++i) {

		

		n.feedForward({ firstInput[i], secondInput[i] });
		n.getResults(results);
		cout << "Test " << i + 1 << " of " << testsToCreate << endl
			<< "First input is " << firstInput[i] << endl
			<< "Second input is " << secondInput[i] << endl
			<< "Got value is " << results[0] << endl
			<< "Expected value is " << output[i] << endl
			<< "Network rate error is " << n.getError() << endl << endl;
		n.training({ output[i] });

	}

	

}