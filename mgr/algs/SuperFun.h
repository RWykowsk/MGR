/*
 * SuperFun.h
 *
 *  Created on: 13.11.2016
 *      Author: WYQ
 */

#ifndef SUPERFUN_H_
#define SUPERFUN_H_

#include "Stripped.h"

class SuperFun: public Stripped
{
public:
	SuperFun();
	virtual ~SuperFun();
protected:
	virtual void funGen(vector<Candidate*> &Ck,
			int k,
			vector<Candidate*> &output);
	virtual void product(vector<vector<int>*> &A, vector<vector<int>*> &B);
	virtual void candidatesFurtherProcessing(std::vector<Candidate*> tmp,
			const std::ofstream& output,
			std::vector<Candidate*>& Rk);
	virtual void mergeCandidates(unsigned int i,
			unsigned int j,
			std::vector<Candidate*>& Ck,
			std::vector<Candidate*>& output);
	virtual void doDecisionProduct(Candidate* X,
			Candidate* Y,
			Candidate** Cand);

private:
	bool superHolds(vector<vector<int>*> &C);
	void InitializeParenthood(Candidate *A,
			Candidate *B,
			Candidate *&X,
			Candidate *&Y,
			int k);
	void UpdateParenthood(Candidate *E, Candidate *&X, Candidate *&Y, int k);
	void DecisionProduct(vector<vector<int>*> &A,
			vector<vector<int>*> &B,
			Candidate *&C);
	bool IsGroupContainedInAnyDecisionClass(vector<int> &S);
	int CountRecords(Candidate *C);
};

#endif /* SUPERFUN_H_ */
