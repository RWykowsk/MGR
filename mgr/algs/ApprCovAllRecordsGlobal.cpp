/*
 * ApprCovAllRecordsGlobal.cpp
 *
 *  Created on: Jun 13, 2017
 *      Author: wyq
 */

#include "ApprCovAllRecordsGlobal.h"

ApprCovAllRecordsGlobal::ApprCovAllRecordsGlobal(int N,double alfa,double beta, double groupNoReq, string outputFile): ApprCovAllRecords(N,alfa,beta,groupNoReq,outputFile) {

}

ApprCovAllRecordsGlobal::~ApprCovAllRecordsGlobal() {
	// TODO Auto-generated destructor stub
}

bool ApprCovAllRecordsGlobal::holds(vector<vector<int>*> *C)
{
	fill(groupsOKCounter->begin(), groupsOKCounter->end(), 0);
//	cout<< alfa << '\t'<< decCardinalities->size()<<'\t'<< decCounters->size()<<'\t'<<coverages->size()<<'\n';
	for (unsigned int i = 0; i < C->size(); i++)
	{ //petla obslugujaca kazda grupe z C
		fill(decCounters->begin(), decCounters->end(), 0);
//		for (unsigned int k = 0; k < decCounters->size(); k++){
//			decCounters->at(k)=0;
//		}
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
		}
		bool isMaxCoverageOK=false;
		double maxCoverageinGroup=0;
		double secondMaxCoverageinGroup=0;
		int groupId;
		int matchedRecordsNo;
		for (unsigned int k = 0; k < coverages->size(); k++){
					//wartosc mianownika
					//TODO ensure that there is more than one decision in dataset
					double lowerValue=(double) (sumCoverages- coverages->at(k))/(decCardinalities->size()-1);
					if(lowerValue==0){
						//infinite coverage
						isMaxCoverageOK=true;
						maxCoverageinGroup=INFINITY;
						groupId=k;
						matchedRecordsNo=decCounters->at(k);
						//cout<<maxCoverageinGroup<< '\t'<<matchedRecordsNo<<'\n';
						break;
					}
					double value=coverages->at(k)/lowerValue;
					if(value>maxCoverageinGroup){
						secondMaxCoverageinGroup=maxCoverageinGroup;
						maxCoverageinGroup=value;
						groupId=k;
						matchedRecordsNo=decCounters->at(k);
						//cout<<matchedRecordsNo<<'\n';
						continue;
					}
					if(value>secondMaxCoverageinGroup){
						secondMaxCoverageinGroup=value;
					}
				}
		if(maxCoverageinGroup>=alfa && (maxCoverageinGroup-secondMaxCoverageinGroup)>beta){
			isMaxCoverageOK=true;
			groupsOKCounter->at(groupId)= groupsOKCounter->at(groupId)+matchedRecordsNo;
			//cout<<groupId<< '\t'<<groupsOKCounter->at(groupId)<< '\t'<<matchedRecordsNo<<'\n';
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
	//cout<<1;
	int sumMatchedRecords=0;
	for (unsigned int k = 0; k < groupsOKCounter->size(); k++){
		sumMatchedRecords=sumMatchedRecords+groupsOKCounter->at(k);
	}
	double percCov=(double)sumMatchedRecords/delta.size();
	//cout<< sumMatchedRecords << '\t'<< delta.size()<<'\t'<< groupNoReq<<'\t'<< percCov<<'\n';
	if(percCov<groupNoReq){
		return false;
	}
	ofstream output(outputFile.c_str(),ios::app);
		for (unsigned int k = 0; k < groupsOKCounter->size(); k++){
			double percGroupCov=(double)groupsOKCounter->at(k)/decCardinalities->at(k);
			output << percGroupCov << '\t';
		}
		output << '\n';
		output.close();
	return true;

}

