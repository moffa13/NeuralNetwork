#include <cstdlib>
#include "utils.h"
#include <ctime>
#include "Neuron.h"
#include <cmath>

namespace utils{

	double random(){
		return rand() / static_cast<double>(RAND_MAX);
	}

	double sigmoid(double x){
		return 1 / ( 1 + exp( -x / 0.19 ));
		//return x * 0.5;
	}

	double sigmoidDerivate(double x) {
		return (exp(-x / 0.19) / 19) / pow(1 + exp(-x / 0.19), 2);
		//return 0.5;
	}

}

