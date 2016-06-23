#include "Network.h"
#include <vector>
#include <chrono>
#include <iostream>
#include "utils.h"
#include "TrainingUtils.h"

using namespace std;

int main(){
	
	
	vector<unsigned> model = { 2, 10, 1 };


	Network n = Network::read("test.txt");

	//Network n(model);

	//TrainingUtils::additionTraining(n, 200);



	while (true) {

		cout << "Enter Input value : ";
		double input1;
		cin >> input1;

		cout << "Enter second input value : ";
		double input2;
		cin >> input2;

		n.feedForward({input1, input2});
		vector<double> res;
		n.getResults(res);

		cout << input1 << " XOR " << input2 << " test with neural network is " << res[0] << endl << endl;

	}

	//cout << "Program executed in " << double(double(duration) / 1000000) << " seconds" << endl;*

//	system("pause");*/

	

}