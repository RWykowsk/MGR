/*
 * SuperFunBA.cpp
 *
 *  Created on: 13.11.2016
 *      Author: WYQ
 */

#include "SuperFunBA.h"


SuperFunBA::SuperFunBA(int N) :
		SuperFun(N)
{
//	this->rNo = N;
//	this->dataRowsNumber = N;
//
}
void SuperFunBA::doDecisionProduct(Candidate* X,
		Candidate* Y,
		Candidate** Cand)
{
	DecisionProduct(Y->groups, X->groups, *Cand);
}

