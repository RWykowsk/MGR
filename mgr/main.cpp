
#include <iostream>
#include <ctime>
#include <cstdlib>
//#include "functions.h"
#include "fileUtils.h"
#include "algs/BasicAlg.h"
#include "algs/Stripped.h"
#include "algs/SuperFun.h"
#include "algs/SuperFunBA.h"
#include "algs/ApprCov.h"
#include "algs/ApprCovAllGroups.h"
#include "algs/ApprCovAllGroupsNumber.h"
#include "algs/ApprCovAllRecords.h"
#include "algs/ApprCovAllRecordsGlobal.h"


using namespace std;



int main(int argc, char *argv[])
{

    clock_t start,end;

    int decisionColumn=1;//number of column where decision is
    int decisionType=1;// id of decision type
	int a_type = 1; // id of algorythm type
	int number_of_transactions = 100;
	double alfa = 2;
	double beta = 1;
	double reqGroupNo = 1;
    string input_file="letters.data";
	if (argc < 5)
	{
		// Tell the user how to run the program
		cerr << "Usage: " << argv[0] << " error" << endl;

		return 1;
	}
	input_file = argv[1];
	number_of_transactions = atoi(argv[2]);
	decisionColumn = atoi(argv[3]);
	a_type = atoi(argv[4]);
	alfa = atof(argv[5]);
	beta = atof(argv[6]);
	if(a_type>=7){
		reqGroupNo= atof(argv[7]);
	}
    string output_file=create_file_name(a_type,number_of_transactions, alfa, beta, reqGroupNo,input_file);




    //TODO
    //Menu do wprowadzania danych z konsoli, do dodania parametr number_of_transactions
    //void Menu(int &d_column, int &d_type, int &a_type, string &input_file,string &output_file);
    //Menu(d_column, d_type, a_type, input_file, output_file);
    start=clock();
    //create_modified_file(input_file, decision_column, decision_type);
    end=clock();
    double dif1=(end - start) / (double)(CLOCKS_PER_SEC / 1000);
    //cout<<"koniec przetwarzania pliku- czas: "<<dif1<<endl;




    vector <Candidate*> C1;//wektor do trzymania kandydatów o dlugosci 1
    start=clock();
    int id_row=read_from_modified_file(input_file,C1,number_of_transactions);
    cout<<"Liczba rekordow: "<<id_row+1<<endl;
    vector <Candidate*> Rk;
	BasicAlg *alg;
    switch(a_type)

                   {
//                    case 4:
//
//                    Super_Fun_algorythmBA(C1,id_row+1,Rk,decisionColumn, output_file);
//                    break;
//                   case 3:
//                        Super_Fun_algorythmAB(C1,id_row+1,Rk,decisionColumn, output_file);
//                        break;
//
//                   case 2:
//                        Stripped_algorythm(C1,id_row+1,Rk,decisionColumn, output_file);
//                        break;
    case 9:
        alg = new ApprCovAllRecordsGlobal(id_row + 1,alfa,beta,reqGroupNo,output_file);
        break;
    case 8:
        alg = new ApprCovAllRecords(id_row + 1,alfa,beta,reqGroupNo,output_file);
        break;
    case 7:
        alg = new ApprCovAllGroupsNumber(id_row + 1,alfa,beta,reqGroupNo);
        break;
    case 6:
    	alg = new ApprCovAllGroups(id_row + 1,alfa,beta);
    	break;
	case 5:
		alg = new ApprCov(id_row + 1,alfa,beta);
		break;
	case 4:
		alg = new SuperFunBA(id_row + 1);
		break;
	case 3:
		alg = new SuperFun(id_row + 1);
		break;
	case 2:
		alg = new Stripped(id_row + 1);
		break;
                   case 1:
		alg = new BasicAlg(id_row + 1);
//                        BasicAlg.Basic_algorythm(C1,id_row+1,Rk,decisionColumn,output_file);
                        break;
                   default:
                       std::cerr << "Wrong algorythm number";
                       break;
                   }
	alg->processData(C1, id_row + 1, Rk, decisionColumn, output_file);





    end=clock();
    double dif2=(end - start) / (double)(CLOCKS_PER_SEC / 1000);
    double dif3=dif1+dif2;
    save_to_outputfile(Rk,a_type,id_row+1,input_file,dif1,dif2,dif3,alfa,beta,reqGroupNo);





    cout<<"Czas wykonania algorytmu "<<dif2<<endl;

return 0;
}
