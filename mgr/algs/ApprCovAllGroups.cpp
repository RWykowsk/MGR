/*
 * ApprCovAllGroups.cpp
 *
 *  Created on: May 24, 2017
 *      Author: wyq
 */

#include "ApprCovAllGroups.h"

ApprCovAllGroups::ApprCovAllGroups(int N,double alfa,double beta): ApprCov(N,alfa,beta) {
	// TODO Auto-generated constructor stub
	this->allGroupsOK= new vector<bool>();

}


ApprCovAllGroups::~ApprCovAllGroups() {
	// TODO Auto-generated destructor stub
}

void ApprCovAllGroups::initialDeltaProcessing(std::vector<vector<int> *>* A) {
	coverages->resize(A->size());
	allGroupsOK->resize(A->size());
	for (unsigned int i = 0; i < A->size(); i++) {
		decCardinalities->push_back(A->at(i)->size());
		decCounters->push_back(0);
		for (unsigned int j = 0; j < A->at(i)->size(); j++) {
			delta.at(A->at(i)->at(j)) = i;
		}
	}
}

bool ApprCovAllGroups::holds(vector<vector<int>*> *C)
{
	fill(allGroupsOK->begin(), allGroupsOK->end(), false);
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
		bool isMaxCoverageOK=false;
		double maxCoverageinGroup=0;
		double secondMaxCoverageinGroup=0;
		int groupId;
		for (unsigned int k = 0; k < coverages->size(); k++){
					//wartosc mianownika
					//TODO ensure that there is more than one decision in dataset
					double lowerValue=(double) (sumCoverages-coverages->at(k))/(decCardinalities->size()-1);
					if(lowerValue==0){
						//infinite coverage
						//isMaxCoverageOK=true;
						maxCoverageinGroup=INFINITY;
						groupId=k;
						break;
					}
					double value=coverages->at(k)/lowerValue;
					if(value>maxCoverageinGroup){
						secondMaxCoverageinGroup=maxCoverageinGroup;
						maxCoverageinGroup=value;
						groupId=k;
						continue;
					}
					if(value>secondMaxCoverageinGroup){
						secondMaxCoverageinGroup=value;
					}
				}
		if(maxCoverageinGroup>=alfa && (maxCoverageinGroup-secondMaxCoverageinGroup)>beta){
			isMaxCoverageOK=true;
			allGroupsOK->at(groupId)=true;
		}
		if(!isMaxCoverageOK){
			return false;
		}
		//TODO zapisywac dla ktorej klasy dec zostalo zapamietane, i holds tylko jezeli wszystkie klasy obsluzone
		//- jako inny wariant algorytmu
		//dodatkowo zapisywac liczbe w kazdej klasie (przez wiele grup) i ja inkrementowac,
		//jezeli kazda grupa obluzona w pewnym stopniou to ok- jako kolejny

	}
	for (unsigned int k = 0; k < allGroupsOK->size(); k++){
		if(!allGroupsOK->at(k)){
			return false;
		}
	}
	return true;

}

