/*
 * ApprCov.cpp
 *
 *  Created on: 06.03.2017
 *      Author: wyq
 */

#include "ApprCov.h"

ApprCov::ApprCov(int N,double alfa)
:BasicAlg(N) {
//	this->rNo = N;
//	this->dataRowsNumber = N;
	this->decCardinalities=new vector<int>();
	this->decCounters= new vector<int>();
	this->coverages= new vector<double>();
	this->alfa=alfa;

}

//ApprCov::ApprCov(int N) :
//		BasicAlg(N)
//{
//
//}

ApprCov::~ApprCov() {
	// TODO Auto-generated destructor stub
}

void ApprCov::initialDeltaProcessing(vector<vector<int> *> *A)
{
	for (unsigned int i = 0; i < A->size(); i++) {
		decCardinalities->push_back(A->size());
		decCounters->push_back(0);
		coverages->resize(A->size());
		for (unsigned int j = 0; j < A->at(i)->size(); j++) {
			delta.at(A->at(i)->at(j)) = i;
		}
	}

}

bool ApprCov::holds(vector<vector<int>*> *C)
{
	for (unsigned int i = 0; i < C->size(); i++)
	{ //petla obslugujaca kazda grupe z C
		for (unsigned int k = 0; k < C->at(i)->size(); k++)
		{ //petla obslugujaca kazdy element z grupy z C
			int oid = C->at(i)->at(k);
			int groupId = delta.at(oid);
			decCounters->at(groupId)++;
		}

		double sumCoverages=0;
		for (unsigned int k = 0; k < decCounters->size(); k++){
			double coverage=(double)decCounters->at(k)/decCardinalities->at(k);
			sumCoverages=sumCoverages+coverage;
			coverages->at(k)=coverage;
			decCounters->at(k)=0;
		}
		//double maxCoverage=0;
		bool maxCoverageInGroupGreaterThanAlfa=false;
		for (unsigned int k = 0; k < coverages->size(); k++){
					//wartosc mianownika
					//TODO ensure that there is more than one decision in dataset
					double lowerValue=(double) (sumCoverages-coverages->at(k))/(decCardinalities->size()-1);
					if(lowerValue==0){
						//infinite coverage
						maxCoverageInGroupGreaterThanAlfa=true;
						break;
					}
					double value=coverages->at(k)/lowerValue;
					if(value>=alfa){
						maxCoverageInGroupGreaterThanAlfa=true;
						break;
					}
				}
		if(!maxCoverageInGroupGreaterThanAlfa){
			return false;
		}

	}
	return true;

}

