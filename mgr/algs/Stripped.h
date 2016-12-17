/*
 * Stripped.h
 *
 *  Created on: 30.10.2016
 *      Author: WYQ
 */

#ifndef STRIPPED_H_
#define STRIPPED_H_
#include "BasicAlg.h"
class Stripped: public BasicAlg
{
public:
	Stripped();
	virtual ~Stripped();
protected:
	virtual bool holds(vector<vector<int>*> &C);
	virtual void product(vector<vector<int>*> &A, vector<vector<int>*> &B);
	virtual void prepareCandidate(vector<Candidate*>& C1);
	virtual void doBeforeProduct(Candidate *Ck);
	void clearStrippedPartitionArrayRepresentation(vector<vector<int> *> &A);
};

#endif /* STRIPPED_H_ */
