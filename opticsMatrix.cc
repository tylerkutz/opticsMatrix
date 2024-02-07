#include <iostream>
#include <fstream>
#include <vector>
#include <array>

#include "TString.h"
#include "TCut.h"
#include "TEventList.h"
#include "TChain.h"
#include "TH1F.h"

#include "DataManager.hh"

using namespace std;

int main(int argc, char** argv) {

	if (argc!=2) {
		cout << "Incorrect set of arguements!  Instead use:" << endl;
		cout << "\t ./opticsMatrix /path/to/input_file.root" << endl;
		exit(1);
	}

	TString inFileName = argv[1];

	DataManager* fDataMan = new DataManager(inFileName);
	cout << "This file has " << fDataMan->GetNumEvents() << " events" << endl;
	

	return 0;

}
