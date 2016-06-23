#include "TrainingUtils.h"
#include <vector>
#include <iostream>

/*cout << "Test " << i + 1 << " of " << testsToCreate << endl
			<< "First input is " << firstInput[i] << endl
			<< "Second input is " << secondInput[i] << endl
			<< "Got value is " << results[0] << endl
			<< "Expected value is " << output[i] << endl
			<< "Network rate error is " << roundf(n.getError() * 100000) / 100000 << endl << endl;*/


			/*for (unsigned i = 0; i < testsToCreate; ++i) {

			double total = 1 - utils::random();

			double n1;

			do {

			n1 = utils::random();

			} while (n1 > total);

			double n2 = total - n1;

			firstInput.push_back(n1);
			secondInput.push_back(n2);
			output.push_back(total);


			}*/


namespace TrainingUtils {

	using namespace std;

	void startHumanTest(Network &n, unsigned inputNumber) {

		vector<double> inputs;
		for (unsigned i = 0; i < inputNumber; ++i) {

			cout << "Enter input n" << i + 1 << " : ";
			double d; 
			cin >> d;
			inputs.push_back(d);

		}

		n.feedForward(inputs);
		
		vector<double> results;

		n.getResults(results);

		cout << "Results are ";

		

		for (unsigned i = 0; i < results.size(); ++i) {

			cout << results[i] << ", ";

		}




	}

	void additionTraining(Network &network, unsigned testsNumber) {

		vector<double> firstInput;
		vector<double> secondInput;
		vector<double> output;
		vector<double> results = {};

		for (unsigned i = 0; i < testsNumber; ++i) {

			int i1 = (int)(2.0 * rand() / double(RAND_MAX));
			int i2 = (int)(2.0 * rand() / double(RAND_MAX));

			firstInput.push_back((double)i1);
			secondInput.push_back((double)i2);
			output.push_back((double)(i1 ^ i2));

		}

		for (unsigned i = 0; i < testsNumber; ++i) {

			network.feedForward({ firstInput[i], secondInput[i] });
			
			network.getResults(results);

			cout << "Test " << i + 1 << " of " << testsNumber << endl
				<< "First input is " << firstInput[i] << endl
				<< "Second input is " << secondInput[i] << endl
				<< "Got value is " << results[0] << endl
				<< "Expected value is " << output[i] << endl
				<< "Network rate error is " << roundf(network.getError() * 100000) / 100000 << endl << endl;

			network.training({results[0]});

		}

	}

}