/*
 * ApprCovAllGroupsNumber.cpp
 *
 *  Created on: May 24, 2017
 *      Author: wyq
 */

#include "ApprCovAllGroupsNumber.h"

ApprCovAllGroupsNumber::ApprCovAllGroupsNumber(int N,double alfa,double beta, double groupNoReq): ApprCov(N,alfa,beta) {
	// TODO Auto-generated constructor stub
	this->groupsOKCounter= new vector<int>();
	this->groupNoReq=groupNoReq;
}


ApprCovAllGroupsNumber::~ApprCovAllGroupsNumber() {
	// TODO Auto-generated destructor stub
}

void ApprCovAllGroupsNumber::initialDeltaProcessing(std::vector<vector<int> *>* A) {
	coverages->resize(A->size());
	groupsOKCounter->resize(A->size());
	for (unsigned int i = 0; i < A->size(); i++) {
		decCardinalities->push_back(A->at(i)->size());
		decCounters->push_back(0);
		for (unsigned int j = 0; j < A->at(i)->size(); j++) {
			delta.at(A->at(i)->at(j)) = i;
		}
	}
}

bool ApprCovAllGroupsNumber::holds(vector<vector<int>*> *C)
{
	fill(groupsOKCounter->begin(), groupsOKCounter->end(), 0);
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
						isMaxCoverageOK=true;
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
			groupsOKCounter->at(groupId)++;
		}
		if(!isMaxCoverageOK){
			return false;
		}
		//TODO zapisywac dla ktorej klasy dec zostalo zapamietane, i holds tylko jezeli wszystkie klasy obsluzone
		//- jako inny wariant algorytmu
		//dodatkowo zapisywac liczbe w kazdej klasie (przez wiele grup) i ja inkrementowac,
		//jezeli kazda grupa obluzona w pewnym stopniou to ok- jako kolejny
		//jako kolejny, ze x rekordow w kazdej decyzji i jak procentowo zostalo wstawione
		//jako kolejny, ze x rekordow w kazdej decyzji i jak procentowo zostalo wstawione, kazdy w innym stopniu moze byc,
		//zapisywac coverages i sum coverages do statystyk i jaka grupa, procentowe pokrycie reduktow
		//jakies funkcje rankingujace?
		//testy na minimum 1, 2 zbiorach danych

	}
	for (unsigned int k = 0; k < groupsOKCounter->size(); k++){
		if(groupsOKCounter->at(k)<groupNoReq){
			return false;
		}
	}
	return true;

}

