/*
 * BasicAlg.h
 *
 *  Created on: 29.10.2016
 *      Author: WYQ
 */

#ifndef BASICALG_H_
#define BASICALG_H_
#include <vector>
//#include <list>
//#include <map>
#include <set>
#include "extBitset.h"
#include <cmath>
using namespace std;

struct Candidate
{ //pi
	vector<vector<int>*> *groups;
	int GroupsNo; //ile roznych grup
	int RecordsNo;
	extBitset Cand_id;
	//vector <int> Cand_id;//id kandydata, wektor z id atrybutow
};

class BasicAlg
{
public:
	BasicAlg(int N);
	virtual ~BasicAlg();
	virtual void processData(vector<Candidate*> &C1,
			int id_row,
			vector<Candidate*> &Rk,
			int d_column,
			string output_file);
protected:
	virtual bool holds(vector<vector<int>*> *C);
	virtual void partitionArrayRepresentation(vector<vector<int>*> *A);
	virtual void doBeforeProduct(Candidate *Ck);
	virtual void product(vector<vector<int>*> *A, vector<vector<int>*> *B
			);
	virtual void funGen(vector<Candidate*> &Ck,
			int k,
			vector<Candidate*> &output);
	virtual void prepareCandidate(std::vector<Candidate*>& C1);
	virtual void search4FunctionalDependencies(std::vector<Candidate*>* tmp,
			std::vector<Candidate*>& Rk);
	virtual void candidatesInitialProcessing(std::ofstream& output,
			std::vector<Candidate*>* tmp,
			std::vector<Candidate*>& Rk);
	virtual void candidatesFurtherProcessing(std::vector<Candidate*> tmp,
			std::ofstream& output,
			std::vector<Candidate*>& Rk);
	virtual void mergeCandidates(unsigned int i,
			unsigned int j,
			std::vector<Candidate*>& Ck,
			std::vector<Candidate*>& output);
	vector<int> T;
	vector<int> delta;
	vector<vector<int>*> *groups;
	void initializeStatistics();
	void printStatistics(std::ofstream& output);
	virtual void initialDeltaProcessing(std::vector<vector<int> *>* A);
	void deltaPartitionArrayRepresentation(vector<vector<int> *> *A);

	int No_candidates;
	int No_divisions = 0;
	int No_divisions2 = 0;
	int sum_groups_before = 0;
	int sum_records_before = 0;
	int sum_records = 0;
	int sum_groups = 0;
	int GroupsNo;
	int dataRowsNumber;
	int rNo;

private:
	void removeDecisionColumn(int d_column, std::vector<Candidate*>& C1);

	void printHeaders(std::ofstream& output);


	bool validateCandidate(extBitset Cand_id,
			std::vector<vector<int> *>* groups,
			std::vector<Candidate*>& Ck,
			std::vector<Candidate*>& output);
	void addCandidate(extBitset Cand_id,
			std::vector<vector<int> *>* groups,
			std::vector<Candidate*>& output);



};

#endif /* BASICALG_H_ */
