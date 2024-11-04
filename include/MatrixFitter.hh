#ifndef MATFIT_HH
#define MATFIT_HH

#include "TMultiDimFit.h"

class MatrixFitter{

public:

	MatrixFitter(int);
	~MatrixFitter();

	void AddTrain(double*, double*, double);
	void AddTest(double*, double*, double);
	void FitMatrix();
	TMultiDimFit* fFit;	

private:

	static const int nVars = 4;
	std::string fVarNames[nVars] = {"r", "r_prime", "phi", "phi_prime"};

	static const int nDepVars = 2;
	std::string fDepVarNames[nDepVars] = {"theta_targ", "phi_targ"};

	int fFitDepVar;		// index of dependent variable being fit


};

#endif
