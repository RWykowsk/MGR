/*
 * Stripped.cpp
 *
 *  Created on: 30.10.2016
 *      Author: WYQ
 */

#include "Stripped.h"

Stripped::Stripped()
{
	// TODO Auto-generated constructor stub

}

Stripped::~Stripped()
{
	// TODO Auto-generated destructor stub
}

virtual void Stripped::doBeforeProduct(Candidate *Ck)
{
	groups.clear();
	GroupsNo = Ck->GroupsNo;
}

virtual void Stripped::product(vector<vector<int> *> &A,
		vector<vector<int> *> &B)
{
	vector<vector<int> > S;
	S.resize(dataRowsNumber);
	int RecordsNo = 0;
	partitionArrayRepresentation(A);
	set<int> AGroupIds; //set, bo groupsID moze sie powtarzac, a my nie chcemy
	for (unsigned int i = 0; i < B.size(); i++)
	{ //petla obslugujaca kazda grupe B
		AGroupIds.clear();
		int j;
		for (unsigned int k = 0; k < B.at(i)->size(); k++)
		{ //petla obslugujaca kazdy element z grupy z B
			j = T.at(B.at(i)->at(k)); // B.at(i).at(k) - oid
			if (j == -1)
				GroupsNo++;
			else
			{
				S.at(j).push_back(B.at(i)->at(k)); //S[j]
				AGroupIds.insert(j);
			}

		}
		set<int>::iterator it;
		for (it = AGroupIds.begin(); it != AGroupIds.end(); ++it)
		{
			if (S.at(*it).size() > 1)
			{ //utworz grupy tylko niesingletonowe
				groups.push_back(new vector<int>(S.at(*it)));
				RecordsNo = RecordsNo + S.at(*it).size();
			}
			GroupsNo++;

		}
		S.clear();
		S.resize(dataRowsNumber);
		GroupsNo--;
	}
	clearStrippedPartitionArrayRepresentation(A);
	rNo = RecordsNo;
}

virtual bool Stripped::holds(vector<vector<int> *> &C)
{
	for (unsigned int i = 0; i < C.size(); i++)
	{ //petla obslugujaca kazda grupe z C
		int oid = C.at(i)->at(0);
		int firstGroup = delta.at(oid);
		if (firstGroup == -1)
			return false;
		for (unsigned int k = 1; k < C.at(i)->size(); k++)
		{ //petla obslugujaca kazdy element z grupy z C
			oid = C.at(i)->at(k);
			int nextGroup = delta.at(oid);
			if (firstGroup != nextGroup)
				return false;
		}
	}
	return true;
}

virtual void Stripped::prepareCandidate(vector<Candidate*>& C1)
{
	for (unsigned int z = 0; z < C1.size(); z++)
	{
		C1.at(z)->GroupsNo = C1.at(z)->groups.size();
		for (int a = 0; a < C1.at(z)->groups.size(); a++)
		{
			//przystrzyz grupy
			if (C1.at(z)->groups.at(a)->size() == 1)
			{
				delete C1.at(z)->groups.at(a);
				C1.at(z)->groups.erase(C1.at(z)->groups.begin() + a);
				a--;
			}
		}
	}

}

void Stripped::clearStrippedPartitionArrayRepresentation(vector<vector<int> *> &A)
{
	for (unsigned int i = 0; i < A.size(); i++)
		for (unsigned int j = 0; j < A.at(i)->size(); j++)
			T.at(A.at(i)->at(j)) = -1;
}



