//#ifndef FUNCTIONS_H
//#define FUNCTIONS_H
//
//#include <vector>
//#include <list>
//#include <map>
//#include <set>
////#include <fstream>
////#include <sstream>
////#include <string>
//#include <iostream>
//#include <ctime>
//#include <cstdlib>
//
//using namespace std;
//struct dictionary{
//    string word;
//    int id;
//    dictionary(string a, int b){
//        word=a;
//        id=b;
//    }
//};
//
//struct Candidate
//{ //pi
//	vector<vector<int>*> groups;
//	int GroupsNo; //ile roznych grup
//	int RecordsNo;
//	extBitset Cand_id;
//	//vector <int> Cand_id;//id kandydata, wektor z id atrybutow
//};
//
//bool StrippedHolds(vector<int> &T, vector<vector<int>*> &C);
//bool SuperHolds(vector <vector <int>* > &C);
//void StrippedPartitionArrayRepresentation(vector <vector <int>* > &A, vector <int> &T);
//void ClearStrippedPartitionArrayRepresentation(vector <vector <int>* > &A, vector <int> &T);
//
//
//void StrippedProduct(vector<vector<int>*> &A,
//		vector<vector<int>*> &B,
//		int BGroupNo,
//		vector<vector<int>*> &C,
//		int &GNo,
//		vector<int> &T,
//		int N,
//		int &RNo);
//void strippedFunGen(vector<Candidate*> &Ck,
//		int k,
//		vector<Candidate*> &output,
//		vector<int> &T,
//		int N);
//
//void SuperFunGenAB(vector <int> &delta,vector <Candidate*> &Ck,int k, vector <Candidate*> &output, vector <int> &T, int &N);
//void SuperFunGenBA(vector<int> &delta,
//		vector<Candidate*> &Ck,
//		int k,
//		vector<Candidate*> &output,
//		vector<int> &T,
//		int N);
//void InitializeParenthood(Candidate *A,Candidate *B, Candidate *&X, Candidate *&Y,int k);
//void UpdateParenthood(Candidate *E, Candidate *&X, Candidate *&Y,int k);
//void DecisionProduct(vector <int> &delta,vector <vector <int>* > &A, vector <vector <int>* > &B, Candidate *&C,vector <int> &T,int &N);
//bool IsGroupContainedInAnyDecisionClass(vector<int>  &S, vector <int> &delta);
//
//void Stripped_algorythm(vector<Candidate*> &C1,
//		int id_row,
//		vector<Candidate*> &Rk,
//		int d_column,
//		string output_file);
//void Super_Fun_algorythmAB(vector <Candidate*> &C1,int id_row, vector <Candidate*> &Rk,int d_column, string output_file);
//void Super_Fun_algorythmBA(vector<Candidate*> &C1,
//		int id_row,
//		vector<Candidate*> &Rk,
//		int d_column,
//		string output_file);
//int CountRecords(Candidate *C);
//
////statystyki
//static int No_candidates;
//static int No_divisions = 0;
//static int No_divisions2 = 0;
//static int sum_groups_before = 0;
//static int sum_records_before = 0;
//static int sum_records = 0;
//static int sum_groups = 0;
//
//#endif // FUNCTIONS_H
