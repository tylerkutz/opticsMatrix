#include <iostream>


#include "MatrixFitter.hh"


MatrixFitter::MatrixFitter(int fitvar) {

	fFitVar = fitvar;

	int nVars = 4;
			//	r  r' ph ph'
	int mPowers[] = {	0, 0, 0, 0,
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1,
				1, 1, 0, 0,
				1, 0, 1, 0,
				1, 0, 0, 1,
				0, 1, 1, 0,
				0, 1, 0, 1,
				0, 0, 1, 1,
				2, 0, 0, 0,
				0, 2, 0, 0,
				0, 0, 2, 0,
				0, 0, 0, 2};


	fFit = new TMultiDimFit(nVars, TMultiDimFit::kMonomials);
	fFit->SetPowers(mPowers, 15);
	
}

MatrixFitter::~MatrixFitter() {
}

void MatrixFitter::AddTrain(double* V, double* D, double E) {
	fFit->AddRow(V, D[fFitVar], E);
}

void MatrixFitter::AddTest(double* V, double* D, double E) {
	fFit->AddTestRow(V, D[fFitVar], E);
}

void MatrixFitter::FitMatrix() {

	// Print out the statistics
        fFit->Print("s");
        fFit->MakeHistograms();
        fFit->FindParameterization();
        fFit->Print("rc");
	fFit->Fit("M");
	fFit->Print("fc v");
	fFit->MakeCode(Form("mdf_fitvar_%i",fFitVar));

}
