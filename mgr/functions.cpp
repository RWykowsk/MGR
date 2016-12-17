#include "functions.h"



void strippedFunGen(vector<Candidate *> &Ck,
		int k,
		vector<Candidate *> &output,
		vector<int> &T,
		int N)
{
	for (unsigned int i = 0; i < Ck.size(); i++)
		for (unsigned int j = i + 1; j < Ck.size(); j++)
		{
			bool ok_to_merge = false;
			int prefix;
			prefix = extBitsetPREFIX(Ck.at(i)->Cand_id, Ck.at(j)->Cand_id);
			if (prefix + 1 == k)
				ok_to_merge = true;
			if (ok_to_merge)
			{
				extBitset Cand_id = Ck.at(i)->Cand_id;
				extBitsetUNION(Cand_id, Ck.at(j)->Cand_id);
				vector<vector<int>*> groups;
				int GroupsNo, RNo;
				StrippedProduct(Ck.at(i)->groups, Ck.at(j)->groups,
						Ck.at(j)->GroupsNo, groups, GroupsNo, T, N, RNo);
				No_divisions++;
				sum_groups_before = sum_groups_before + GroupsNo;
				sum_records_before = sum_records_before + RNo;
				bool cand_validate = false;
				int pos;
				pos = extBitsetGETNEXT(Cand_id, 0);
				extBitset cand_validator;
				while (pos > 0)
				{ //petla do tworzenia sprawdzianow
					cand_validator = Cand_id;
					extBitsetREMOVE(cand_validator, pos);
					for (unsigned int o = 0; o < Ck.size(); o++)
					{ //sprawdzenie czy sprawdzian spelnia warunki
						cand_validate = false;
						if (cand_validator == Ck.at(o)->Cand_id)
						{ //sprawdz czy istnieje podzbior
							cand_validate = true;
							if (GroupsNo == Ck.at(o)->GroupsNo) //sprawdz czy podzbior ma tyle samo grup
							{
								cand_validate = false;
							}
							break;
						}
					}
					if (cand_validate == false)
					{ //jezeli nie spelnia to nie sprawdzaj dalszych sprawdzianow

						break;
					}
					pos = extBitsetGETNEXT(Cand_id, pos);
				}
				if (cand_validate == true)
				{
					//cout<<"bla2"<<endl;
					output.push_back(new Candidate);
					output.back()->Cand_id = Cand_id;
					//output.back()->Cand_id = new vector <int> (Cand_id);
					output.back()->GroupsNo = GroupsNo;
					output.back()->groups = groups;
					No_divisions2++;
					sum_groups = sum_groups + GroupsNo;
					sum_records = sum_records + RNo;
				}
				else
				{

					extBitsetPRINT(Cand_id);
					cout << endl;
				}

			}
		}
}



void Stripped_algorythm(vector<Candidate *> &C1,
		int id_row,
		vector<Candidate *> &Rk,
		int d_column,
		string output_file)
{
	clock_t start, end;
	start = clock();
	vector<int> T;
	T.resize(id_row);
	for (unsigned int i = 0; i < T.size(); i++)
		T.at(i) = -1;
	vector<int> delta;
	delta.resize(id_row);
	for (unsigned int i = 0; i < delta.size(); i++)
		delta.at(i) = -1;
	for (unsigned int z = 0; z < C1.size(); z++) //dodaj GroupsNo
		C1.at(z)->GroupsNo = C1.at(z)->groups.size();
	for (unsigned int z = 0; z < C1.size(); z++) //dla kazdego atrybutu
		for (int a = 0; a < C1.at(z)->groups.size(); a++) //przystrzyz grupy
			if (C1.at(z)->groups.at(a)->size() == 1)
			{
				delete C1.at(z)->groups.at(a);
				C1.at(z)->groups.erase(C1.at(z)->groups.begin() + a);
				a--;
			}

	StrippedPartitionArrayRepresentation(C1.at(d_column - 1)->groups, delta);
	for (unsigned int z = 0; z < C1.at(d_column - 1)->groups.size(); z++)
	{ //atrybut ostatni(decyzja) wszystkie grupy -usuwanie
//        for (unsigned int a = 0; a < C1.at(d_column - 1)->groups.at(z)->size(); a++) {//wszystkie elementy z grupy
//            delete C1.at(d_column - 1)->groups.at(z)->at(a);
//        }
		delete C1.at(d_column - 1)->groups.at(z);
	}
	delete C1.at(d_column - 1);
	C1.erase(C1.begin() + d_column - 1);
	vector<Candidate *> tmp;
	tmp = C1;
	ofstream output(output_file.c_str());
	output << "Liczba kandydatow o dlugosci : " << '\t';
	output << "Liczba wszystkich wytworzonych podzialow " << '\t';
	output << "Suma wszystkich grup " << '\t';
	output << "Srednia liczba grup " << '\t';
	output << "Suma wszystkich rekordow " << '\t';
	output << "Srednia liczba rekordow " << '\t';
	output
			<< "Liczba wytworzonych podzialow po czyszczeniu kandydatów(pruning) "
			<< '\t';
	output << "Suma wszystkich grup po czyszczeniu kandydatów(pruning) "
			<< '\t';
	output << "Srednia liczba grup po czyszczeniu kandydatów(pruning) "
			<< '\t';
	output << "Suma wszystkich rekordow po czyszczeniu kandydatów(pruning) "
			<< '\t';
	output << "Srednia liczba rekordow po czyszczeniu kandydatów(pruning) "
			<< endl;
	for (int k = 1; tmp.size() > 0; k++)
	{

		output << tmp.size() << '\t';
		for (int z = 0; z < tmp.size(); z++)
			if (StrippedHolds(delta, tmp.at(z)->groups))
			{
				Rk.push_back(tmp.at(z));
//                extBitsetPRINTTOFILE(tmp.at(z)->Cand_id, output);
//                output<<"\n";
				tmp.erase(tmp.begin() + z);
				z--;

			}
		No_divisions = 0;
		No_divisions2 = 0;
		sum_groups = 0;
		sum_records = 0;
		sum_groups_before = 0;
		sum_records_before = 0;
		vector<Candidate *> tmp2;
		strippedFunGen(tmp, k, tmp2, T, id_row);
		output << No_divisions << '\t';
		output << sum_groups_before << '\t';
		double avg_groups_before = double(sum_groups_before) / No_divisions2;
		output << avg_groups_before << '\t';
		output << sum_records_before << '\t';
		double avg_records_before = double(sum_records_before) / No_divisions2;
		output << avg_records_before << '\t';
		output << No_divisions2 << '\t';
		output << sum_groups << '\t';
		double avg_groups = double(sum_groups) / No_divisions2;
		output << avg_groups << '\t';
		output << sum_records << '\t';
		double avg_records = double(sum_records) / No_divisions2;
		output << avg_records << endl;
		tmp = tmp2;

	}
	end = clock();
	output.close();

}

bool StrippedHolds(vector<int> &T, vector<vector<int> *> &C)
{
	for (unsigned int i = 0; i < C.size(); i++)
	{ //petla obslugujaca kazda grupe z C
		int oid = C.at(i)->at(0);
		int firstGroup = T.at(oid);
		if (firstGroup == -1)
			return false;
		for (unsigned int k = 1; k < C.at(i)->size(); k++)
		{ //petla obslugujaca kazdy element z grupy z C
			oid = C.at(i)->at(k);
			int nextGroup = T.at(oid);
			if (firstGroup != nextGroup)
				return false;
		}
	}
	return true;
}

void StrippedPartitionArrayRepresentation(vector<vector<int> *> &A,
		vector<int> &T)
{
	for (unsigned int i = 0; i < A.size(); i++)
		for (unsigned int j = 0; j < A.at(i)->size(); j++)
			T.at(A.at(i)->at(j)) = i;
}

void StrippedProduct(vector<vector<int> *> &A,
		vector<vector<int> *> &B,
		int BGroupNo,
		vector<vector<int> *> &C,
		int &GNo,
		vector<int> &T,
		int N,
		int &RNo)
{
	vector<vector<int> > S;
	C.clear();
	S.resize(N);
	int GroupsNo = BGroupNo;
	int RecordsNo = 0;
	StrippedPartitionArrayRepresentation(A, T);
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
				C.push_back(new vector<int>(S.at(*it)));
				RecordsNo = RecordsNo + S.at(*it).size();
			}
			GroupsNo++;

		}
		S.clear();
		S.resize(N);
		GroupsNo--;
	}
	GNo = GroupsNo;
	ClearStrippedPartitionArrayRepresentation(A, T);
	RNo = RecordsNo;
}
void SuperFunGenAB(vector<int> &delta,
		vector<Candidate *> &Ck,
		int k,
		vector<Candidate *> &output,
		vector<int> &T,
		int &N)
{
	//cout<<Ck->size()<<endl;
	for (unsigned int i = 0; i < Ck.size(); i++)
		for (unsigned int j = i + 1; j < Ck.size(); j++)
		{
			bool ok_to_merge = false;
			int prefix;
			prefix = extBitsetPREFIX(Ck.at(i)->Cand_id, Ck.at(j)->Cand_id);
			if (prefix + 1 == k)
				ok_to_merge = true;
			if (ok_to_merge)
			{
				extBitset Cand_id = Ck.at(i)->Cand_id;
				extBitsetUNION(Cand_id, Ck.at(j)->Cand_id);
				Candidate *X, *Y;
				InitializeParenthood(Ck.at(i), Ck.at(j), X, Y, k);

				bool cand_validate = true;
				Candidate *E;

				int pos;
				pos = extBitsetGETNEXT(Cand_id, 0);
				extBitset cand_validator;
				while (pos > 0)
				{ //petla do tworzenia sprawdzianow
					cand_validator = Cand_id;
					extBitsetREMOVE(cand_validator, pos);
					if ((cand_validator == Ck.at(i)->Cand_id)
							|| (cand_validator == Ck.at(j)->Cand_id)) //jezeli jest równy ktoremus ojcu
					{
						pos = extBitsetGETNEXT(Cand_id, pos);
						continue; //to przejdz do nastepnego sprawdzianu, m++
					}
					for (unsigned int o = 0; o < Ck.size(); o++)
					{ //sprawdzenie czy sprawdzian spelnia warunki
						cand_validate = false;
						if (cand_validator == Ck.at(o)->Cand_id)
						{ //sprawdz czy istnieje podzbior
							cand_validate = true;
							E = Ck.at(o);
							break;
						}
					}
					if (cand_validate == false)
						break;
					else
						UpdateParenthood(E, X, Y, k);
					pos = extBitsetGETNEXT(Cand_id, pos);
				}

				if (cand_validate)
				{
					Candidate *Cand = new Candidate;
					DecisionProduct(delta, X->groups, Y->groups, Cand, T, N);
					No_divisions++;
					sum_groups_before = sum_groups_before + Cand->GroupsNo;
					sum_records_before = sum_records_before + Cand->RecordsNo;
					Cand->Cand_id = Cand_id;
					if ((Cand->RecordsNo != X->RecordsNo)
							|| (Cand->GroupsNo != X->GroupsNo))
					{
						output.push_back(Cand);
						No_divisions2++;
						sum_groups = sum_groups + Cand->GroupsNo;
						sum_records = sum_records + Cand->RecordsNo;
					}
					else
						delete Cand;

				}

			}

		}

}

void InitializeParenthood(Candidate *A,
		Candidate *B,
		Candidate *&X,
		Candidate *&Y,
		int k)
{
	if (k == 1)
	{
		A->RecordsNo = CountRecords(A);
		B->RecordsNo = CountRecords(B);
	}
	if ((A->RecordsNo < B->RecordsNo)
			|| ((A->RecordsNo == B->RecordsNo) && (A->GroupsNo > B->GroupsNo)))
	{
		X = A;
		Y = B;
	}
	else
	{
		X = B;
		Y = A;
	}
}

int CountRecords(Candidate *C)
{
	int records = 0;
	for (unsigned int z = 0; z < C->groups.size(); z++) //wszystkie grupy
		for (unsigned int a = 0; a < C->groups.at(z)->size(); a++) //wszystkie elementy z grupy
			records++;
	return records;
}

void UpdateParenthood(Candidate *E, Candidate *&X, Candidate *&Y, int k)
{
	if (k == 1)
		E->RecordsNo = CountRecords(E);
	if (X->RecordsNo < Y->RecordsNo)
	{
		if (E->RecordsNo < X->RecordsNo)
		{
			Y = X;
			X = E;
		}
		else if (E->RecordsNo == X->RecordsNo)
		{
			if (E->GroupsNo > X->GroupsNo)
			{
				Y = X;
				X = E;
			}
			else
				Y = E;
		}
		else if (E->RecordsNo < Y->RecordsNo)
			Y = E;
		else if (E->RecordsNo == Y->RecordsNo)
		{
			if (E->GroupsNo > Y->GroupsNo)
			{
				Y = E;
			}
		}

	}
	else if (E->RecordsNo < X->RecordsNo)
		X = E;
	else if (E->RecordsNo == X->RecordsNo)
	{
		if (E->GroupsNo > X->GroupsNo)
		{
			X = E;
		}
		else if (E->GroupsNo > Y->GroupsNo)
			Y = E;
	}

}

void DecisionProduct(vector<int> &delta,
		vector<vector<int> *> &A,
		vector<vector<int> *> &B,
		Candidate *&C,
		vector<int> &T,
		int &N)
{
	vector<vector<int> > S;
	C->groups.clear();
	C->GroupsNo = 0;
	C->RecordsNo = 0;
	S.resize(N);
	StrippedPartitionArrayRepresentation(B, T);
	set<int> BGroupIds; //set, bo groupsID moze sie powtarzac, a my nie chcemy
	for (unsigned int i = 0; i < A.size(); i++)
	{ //petla obslugujaca kazda grupe A
		BGroupIds.clear();
		int j;
		for (unsigned int k = 0; k < A.at(i)->size(); k++)
		{ //petla obslugujaca kazdy element z grupy z A
			j = T.at(A.at(i)->at(k)); // A.at(i).at(k) - oid
			if (j != -1)
			{
				S.at(j).push_back(A.at(i)->at(k)); //S[j]
				BGroupIds.insert(j);
			}
		}
		set<int>::iterator it;
		for (it = BGroupIds.begin(); it != BGroupIds.end(); ++it)
		{
			if (IsGroupContainedInAnyDecisionClass(S.at(*it), delta) == false)
			{
				//C->groups.push_back(new vector<int *>());
				C->groups.push_back(new vector<int>(S.at(*it)));
//                for (unsigned int x = 0; x < S.at(*it).size(); x++) {//insertowanie S[j] do C
//                    C->groups.back()->push_back(new int(S.at(*it).at(x)));
				C->RecordsNo = C->RecordsNo + S.at(*it).size();
//                }
				C->GroupsNo++;
			}

		}
		S.clear();
		S.resize(N);
	}
	ClearStrippedPartitionArrayRepresentation(B, T);
}

void Super_Fun_algorythmAB(vector<Candidate *> &C1,
		int id_row,
		vector<Candidate *> &Rk,
		int d_column,
		string output_file)
{
	clock_t start, end;
	start = clock();
	vector<int> T;
	T.resize(id_row);
	for (unsigned int i = 0; i < T.size(); i++)
		T.at(i) = -1;
	vector<int> delta;
	delta.resize(id_row);
	for (unsigned int i = 0; i < delta.size(); i++)
		delta.at(i) = -1;
	for (unsigned int z = 0; z < C1.size(); z++) //dodaj GroupsNo
		C1.at(z)->GroupsNo = C1.at(z)->groups.size();
	for (unsigned int z = 0; z < C1.size(); z++) //dla kazdego atrybutu
		for (int a = 0; a < C1.at(z)->groups.size(); a++) //przystrzyz grupy
			if (C1.at(z)->groups.at(a)->size() == 1)
			{
				//delete C1.at(z)->groups.at(a)->at(0);
				delete C1.at(z)->groups.at(a);
				C1.at(z)->groups.erase(C1.at(z)->groups.begin() + a);
				a--;
			}

	StrippedPartitionArrayRepresentation(C1.at(d_column - 1)->groups, delta);

	for (unsigned int z = 0; z < C1.at(d_column - 1)->groups.size(); z++)
	{ //atrybut ostatni(decyzja) wszystkie grupy -usuwanie
//        for (unsigned int a = 0; a < C1.at(d_column - 1)->groups.at(z)->size(); a++) {//wszystkie elementy z grupy
//            delete C1.at(d_column - 1)->groups.at(z)->at(a);
//        }
		delete C1.at(d_column - 1)->groups.at(z);
	}
	delete C1.at(d_column - 1);
	C1.erase(C1.begin() + d_column - 1);
	vector<Candidate *> tmp;
	tmp = C1;
	ofstream output(output_file.c_str());
	output << "Liczba kandydatow o dlugosci : " << '\t';
	output << "Liczba wszystkich wytworzonych podzialow " << '\t';
	output << "Suma wszystkich grup " << '\t';
	output << "Srednia liczba grup " << '\t';
	output << "Suma wszystkich rekordow " << '\t';
	output << "Srednia liczba rekordow " << '\t';
	output
			<< "Liczba wytworzonych podzialow po czyszczeniu kandydatów(pruning) "
			<< '\t';
	output << "Suma wszystkich grup po czyszczeniu kandydatów(pruning) "
			<< '\t';
	output << "Srednia liczba grup po czyszczeniu kandydatów(pruning) "
			<< '\t';
	output << "Suma wszystkich rekordow po czyszczeniu kandydatów(pruning) "
			<< '\t';
	output << "Srednia liczba rekordow po czyszczeniu kandydatów(pruning) "
			<< endl;
	for (int k = 1; tmp.size() > 0; k++)
	{

		output << tmp.size() << '\t';
		if (k == 1)
		{
			for (int z = 0; z < tmp.size(); z++)
				if (StrippedHolds(delta, tmp.at(z)->groups))
				{
					Rk.push_back(tmp.at(z));
//                    extBitsetPRINTTOFILE(tmp.at(z)->Cand_id, output);
//                    output<<"\n";
					tmp.erase(tmp.begin() + z);
					z--;
				}
		}
		else
		{
			for (int z = 0; z < tmp.size(); z++)
				if (SuperHolds(tmp.at(z)->groups))
				{
					Rk.push_back(tmp.at(z));
//                    extBitsetPRINTTOFILE(tmp.at(z)->Cand_id, output);
//                    output<<"\n";
					tmp.erase(tmp.begin() + z);
					z--;
				}
		}
		No_divisions = 0;
		No_divisions2 = 0;
		sum_groups = 0;
		sum_records = 0;
		sum_groups_before = 0;
		sum_records_before = 0;
		vector<Candidate *> tmp2;
		SuperFunGenAB(delta, tmp, k, tmp2, T, id_row);
		output << No_divisions << '\t';
		output << sum_groups_before << '\t';
		double avg_groups_before = double(sum_groups_before) / No_divisions2;
		output << avg_groups_before << '\t';
		output << sum_records_before << '\t';
		double avg_records_before = double(sum_records_before) / No_divisions2;
		output << avg_records_before << '\t';
		output << No_divisions2 << '\t';
		output << sum_groups << '\t';
		double avg_groups = double(sum_groups) / No_divisions2;
		output << avg_groups << '\t';
		output << sum_records << '\t';
		double avg_records = double(sum_records) / No_divisions2;
		output << avg_records << endl;
		tmp = tmp2;

	}
	end = clock();
	output.close();

}

bool IsGroupContainedInAnyDecisionClass(vector<int> &S, vector<int> &delta)
{
	if (S.size() > 1)
	{
		int oid = S.at(0);
		int firstGroup = delta.at(oid);
		if (firstGroup == -1)
			return false;
		for (unsigned int k = 1; k < S.size(); k++)
		{ //petla obslugujaca kazdy element z grupy z S
			oid = S.at(k);
			int nextGroup = delta.at(oid);
			if (firstGroup != nextGroup)
				return false;
		}
	}

	return true;
}

bool SuperHolds(vector<vector<int> *> &C)
{
	if (C.size() == 0)
		return true;
	return false;
}

void SuperFunGenBA(vector<int> &delta,
		vector<Candidate *> &Ck,
		int k,
		vector<Candidate *> &output,
		vector<int> &T,
		int N)
{
	for (unsigned int i = 0; i < Ck.size(); i++)
		for (unsigned int j = i + 1; j < Ck.size(); j++)
		{
			bool ok_to_merge = false;
			int prefix;
			prefix = extBitsetPREFIX(Ck.at(i)->Cand_id, Ck.at(j)->Cand_id);
			if (prefix + 1 == k)
				ok_to_merge = true;
			if (ok_to_merge)
			{
				extBitset Cand_id = Ck.at(i)->Cand_id;
				extBitsetUNION(Cand_id, Ck.at(j)->Cand_id);
				Candidate *X, *Y;
				InitializeParenthood(Ck.at(i), Ck.at(j), X, Y, k);

				bool cand_validate = true;
				Candidate *E;

				int pos;
				pos = extBitsetGETNEXT(Cand_id, 0);
				extBitset cand_validator;
				while (pos > 0)
				{ //petla do tworzenia sprawdzianow
					cand_validator = Cand_id;
					extBitsetREMOVE(cand_validator, pos);
					if ((cand_validator == Ck.at(i)->Cand_id)
							|| (cand_validator == Ck.at(j)->Cand_id)) //jezeli jest równy ktoremus ojcu
					{
						pos = extBitsetGETNEXT(Cand_id, pos);
						continue; //to przejdz do nastepnego sprawdzianu, m++
					}
					for (unsigned int o = 0; o < Ck.size(); o++)
					{ //sprawdzenie czy sprawdzian spelnia warunki
						cand_validate = false;
						if (cand_validator == Ck.at(o)->Cand_id)
						{ //sprawdz czy istnieje podzbior
							cand_validate = true;
							E = Ck.at(o);
							break;
						}
					}
					if (cand_validate == false)
						break;
					else
						UpdateParenthood(E, X, Y, k);
					pos = extBitsetGETNEXT(Cand_id, pos);
				}

				if (cand_validate)
				{
					Candidate *Cand = new Candidate;
					DecisionProduct(delta, Y->groups, X->groups, Cand, T, N);
					No_divisions++;
					sum_groups_before = sum_groups_before + Cand->GroupsNo;
					sum_records_before = sum_records_before + Cand->RecordsNo;
					Cand->Cand_id = Cand_id;
					if ((Cand->RecordsNo != X->RecordsNo)
							|| (Cand->GroupsNo != X->GroupsNo))
					{
						output.push_back(Cand);
						No_divisions2++;
						sum_groups = sum_groups + Cand->GroupsNo;
						sum_records = sum_records + Cand->RecordsNo;
					}
					else
						delete Cand;

				}

			}

		}

}

void Super_Fun_algorythmBA(vector<Candidate *> &C1,
		int id_row,
		vector<Candidate *> &Rk,
		int d_column,
		string output_file)
{
	clock_t start, end;
	start = clock();
	vector<int> T;
	T.resize(id_row);
	for (unsigned int i = 0; i < T.size(); i++)
		T.at(i) = -1;
	vector<int> delta;
	delta.resize(id_row);
	for (unsigned int i = 0; i < delta.size(); i++)
		delta.at(i) = -1;
	for (unsigned int z = 0; z < C1.size(); z++) //dodaj GroupsNo
		C1.at(z)->GroupsNo = C1.at(z)->groups.size();
	for (unsigned int z = 0; z < C1.size(); z++) //dla kazdego atrybutu
		for (int a = 0; a < C1.at(z)->groups.size(); a++) //przystrzyz grupy
			if (C1.at(z)->groups.at(a)->size() == 1)
			{
				delete C1.at(z)->groups.at(a);
				C1.at(z)->groups.erase(C1.at(z)->groups.begin() + a);
				a--;
			}

	StrippedPartitionArrayRepresentation(C1.at(d_column - 1)->groups, delta);

	for (unsigned int z = 0; z < C1.at(d_column - 1)->groups.size(); z++)
	{ //atrybut ostatni(decyzja) wszystkie grupy -usuwanie

		delete C1.at(d_column - 1)->groups.at(z);
	}
	delete C1.at(d_column - 1);
	C1.erase(C1.begin() + d_column - 1);
	vector<Candidate*> tmp;
	tmp = C1;
	ofstream output(output_file.c_str());
	output << "Liczba kandydatow o dlugosci : " << '\t';
	output << "Liczba wszystkich wytworzonych podzialow " << '\t';
	output << "Suma wszystkich grup " << '\t';
	output << "Srednia liczba grup " << '\t';
	output << "Suma wszystkich rekordow " << '\t';
	output << "Srednia liczba rekordow " << '\t';
	output
			<< "Liczba wytworzonych podzialow po czyszczeniu kandydatów(pruning) "
			<< '\t';
	output << "Suma wszystkich grup po czyszczeniu kandydatów(pruning) "
			<< '\t';
	output << "Srednia liczba grup po czyszczeniu kandydatów(pruning) "
			<< '\t';
	output << "Suma wszystkich rekordow po czyszczeniu kandydatów(pruning) "
			<< '\t';
	output << "Srednia liczba rekordow po czyszczeniu kandydatów(pruning) "
			<< endl;
	for (int k = 1; tmp.size() > 0; k++)
	{

		output << tmp.size() << '\t';
		if (k == 1)
		{
			for (int z = 0; z < tmp.size(); z++)
				if (StrippedHolds(delta, tmp.at(z)->groups))
				{
					Rk.push_back(tmp.at(z));
					tmp.erase(tmp.begin() + z);
					z--;
				}
		}
		else
		{
			for (int z = 0; z < tmp.size(); z++)
				if (SuperHolds(tmp.at(z)->groups))
				{
					Rk.push_back(tmp.at(z));
					tmp.erase(tmp.begin() + z);
					z--;
				}
		}
		No_divisions = 0;
		No_divisions2 = 0;
		sum_groups = 0;
		sum_records = 0;
		sum_groups_before = 0;
		sum_records_before = 0;
		vector<Candidate *> tmp2;
		SuperFunGenBA(delta, tmp, k, tmp2, T, id_row);
		output << No_divisions << '\t';
		output << sum_groups_before << '\t';
		double avg_groups_before = double(sum_groups_before) / No_divisions2;
		output << avg_groups_before << '\t';
		output << sum_records_before << '\t';
		double avg_records_before = double(sum_records_before) / No_divisions2;
		output << avg_records_before << '\t';
		output << No_divisions2 << '\t';
		output << sum_groups << '\t';
		double avg_groups = double(sum_groups) / No_divisions2;
		output << avg_groups << '\t';
		output << sum_records << '\t';
		double avg_records = double(sum_records) / No_divisions2;
		output << avg_records << endl;
		tmp = tmp2;

	}
	end = clock();
	output.close();

}

void ClearStrippedPartitionArrayRepresentation(vector<vector<int> *> &A,
		vector<int> &T)
{
	for (unsigned int i = 0; i < A.size(); i++)
		for (unsigned int j = 0; j < A.at(i)->size(); j++)
			T.at(A.at(i)->at(j)) = -1;
}
