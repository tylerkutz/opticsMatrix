#include <iostream>
#include <fstream>
#include <vector>
#include <array>

#include "TString.h"
#include "TCut.h"
#include "TEventList.h"
#include "TChain.h"
#include "TH1F.h"

#include "InputDataManager.hh"
#include "SieveMap.hh"
#include "MatrixFitter.hh"

using namespace std;

int main(int argc, char** argv) {

	if (argc!=3) {
		cout << "Incorrect set of arguements!  Instead use:" << endl;
		cout << "\t ./opticsMatrix </path/to/input_file.root> <fit variable (0 = theta, 1 =phi)>" << endl;
		exit(1);
	}

	TString inFileName = argv[1];
	int fitVar = atoi(argv[2]);

	InputDataManager* inputDataMan = new InputDataManager(inFileName, "newT");
	inputDataMan->SetRemollBranchNames();

	SieveMap* sieve = new SieveMap("sieve_hole_centers.dat");
	inputDataMan->SetSieveMap(sieve);

	MatrixFitter* mFit = new MatrixFitter(fitVar);
	inputDataMan->SetMatrixFitter(mFit);


	inputDataMan->ProcessEvents();

	mFit->FitMatrix();

	return 0;

}
