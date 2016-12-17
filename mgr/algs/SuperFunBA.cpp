/*
 * SuperFunBA.cpp
 *
 *  Created on: 13.11.2016
 *      Author: WYQ
 */

#include "SuperFunBA.h"

SuperFunBA::SuperFunBA()
{
	// TODO Auto-generated constructor stub

}

SuperFunBA::~SuperFunBA()
{
	// TODO Auto-generated destructor stub
}

virtual void SuperFun::doDecisionProduct(Candidate* X,
		Candidate* Y,
		Candidate** Cand)
{
	DecisionProduct(Y->groups, X->groups, *Cand);
}

