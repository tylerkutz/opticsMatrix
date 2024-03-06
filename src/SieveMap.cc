#include <iostream>
#include <fstream>
#include <math.h>

#include "SieveMap.hh"

using namespace std;

SieveMap::SieveMap(TString sieveHoleFile) {

	for(int i = 0; i < 7; i++) {
		double thisShift = ((1./14.) + (i/7.))* (2*M_PI);
		localPhiShifts.push_back(thisShift);
	}

	LoadSieveHoles(sieveHoleFile);

	sieve_z = 4700.;

}

SieveMap::~SieveMap() {
}

void SieveMap::LoadSieveHoles(TString sieveHoleFile) {

	ifstream holeIn(sieveHoleFile);
	string dummy;

	getline(holeIn,dummy);

	int holeid;
	double thisR, thisTheta, thisPhi, thisLocalPhi;

	while(holeIn >> holeid >> thisR >> thisPhi >> thisTheta) {

		SieveHole thisHole;
		thisHole.R = thisR;
		thisHole.Theta = thisTheta;
		thisHole.Phi = thisPhi;
		for(int i = 0; i < 7; i++) {
			if(holeid > (i+1)*10 && holeid < (i+2)*10) {
				thisHole.LocalPhi = thisPhi - localPhiShifts[i];
			}
		}
		sieveMap[holeid] = thisHole;
	}

}

double SieveMap::GetHoleTheta(int holeid, double zfoil) {

	return atan(sieveMap[holeid].R / (sieve_z - zfoil));

}


