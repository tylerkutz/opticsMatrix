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
	int fFitVar;



};

#endif
