#include <iostream>


#include "MatrixFitter.hh"


MatrixFitter::MatrixFitter(int fitdepvar) {

	fFitDepVar = fitdepvar;

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
	fFit->AddRow(V, D[fFitDepVar], E);
}

void MatrixFitter::AddTest(double* V, double* D, double E) {
	fFit->AddTestRow(V, D[fFitDepVar], E);
}

void MatrixFitter::FitMatrix() {

	// Print out the statistics
        fFit->Print("s");
        fFit->MakeHistograms();
        fFit->FindParameterization();
        fFit->Print("rc");
	fFit->Fit("M");
	fFit->Print("fc v");
	fFit->MakeCode(Form("mdf_fitvar_%i",fFitDepVar));
	const TVectorD* fitCoeff = fFit->GetCoefficients();
	std::cout << "Best fit coefficients:" << std::endl;
	fitCoeff->Print();
	std::cout << std::endl;
	

}
