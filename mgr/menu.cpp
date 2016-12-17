//#include <iostream>
//#include <fstream>
//#include <sstream>
//
//using namespace std;
//
//bool Menu(int *d_column, int *d_type, int *a_type, ifstream *input_file, string filename, int *number_of_transaction) {
//    string inputFileName;
//    cout << "Podaj nazwę pliku z danymi:" << endl;
//    cin >> inputFileName;
//    (*input_file).open(inputFileName);
//    if (!input_file->is_open()) {
//        cout << "Nie prawidłowa nazwa pliku (plik nie istnieje) lub wystąpił inny błąd." << endl;
//        cout << "Podaj jeszcze raz nazwę pliku z danymi:" << endl;
//        cin >> inputFileName;
//        (*input_file).open(inputFileName);
//        if (!input_file->is_open()) {
//            cout <<
//            "Nie prawidłowa nazwa pliku (plik nie istnieje) - sprawdź czy plik jest w tym samym folderze co plik wykonywalny programu." <<
//            endl;
//            return false;
//        }
//    }
//
//    string firstLine;
//    getline(*input_file, firstLine);
//    std::istringstream input(firstLine);
//    int atributesNb = 0;
//    while (std::getline(input, firstLine, ',')) {
//        atributesNb++;
//    }
//    if (atributesNb <= 1) {
//        cout << "Nie prawidłowe dane w pliku - sprawdź czy separatorem danych jest znak ',' (przecinek)." << endl;
//        return false;
//    }
//
//    cout << "Podaj numer kolumny (od 1 do " << atributesNb << "), która jest kolumną z atrybutem decyzyjnym:" << endl;
//    cin >> *d_column;
//    if (*d_column < 1 || *d_column > atributesNb) {
//        cout << "Nieprawidłowy numer, podaj go jeszcze raz (liczba z przedziału od 1 do " << *d_column << "):" << endl;
//        cin >> *d_column;
//        if (*d_column < 1 || *d_column > atributesNb) {
//            cout << "Podano nie prawidłowy numer kolumny." << endl;
//            return false;
//        }
//    }
//
//    cout << "Wybierz sposób wyznaczania decyzji (wybierając jedną z 4 opcji):" << endl;
//    cout << "* d                                  :1" << endl;
//    cout << "* d_AT ^N - derivable decision       :2" << endl;
//    cout << "* uogólniona - generalized decision  :3" << endl;
//    cout << "* mi-decyzja                         :4" << endl;
//    cout << "Podaj liczbę 1, 2, 3 lub 4:" << endl;
//    cin >> *d_type;
//    if (*d_type != 1 && *d_type != 2 && *d_type != 3 && *d_type != 4) {
//        cout << "Błędna liczba, podaj liczbę 1, 2, 3 lub 4:" << endl;
//        cin >> *d_type;
//        if (*d_type != 1 && *d_type != 2 && *d_type != 3 && *d_type != 4) {
//            cout << "Błędna liczba" << endl;
//            return false;
//        }
//    }
//
//    cout << "Wybierz algorytm do wykonania (wybierając jedną z 3 opcji):" << endl;
//    cout << "* FUN          :1" << endl;
//    cout << "* FUN przystrzyżony      :2" << endl;
//    cout << "* Super FUN  :3" << endl;
//    cout << "Podaj liczbę 1, 2 lub 3:" << endl;
//    cin >> *a_type;
//    if (*a_type != 1 && *a_type != 2 && *a_type != 3) {
//        cout << "Błędna liczba, podaj liczbę 1, 2 lub 3:" << endl;
//        cin >> *a_type;
//        if (*a_type != 1 && *a_type != 2 && *a_type != 3) {
//            cout << "Błędna liczba" << endl;
//            return false;
//        }
//    }
//
//    cout << "Ile transakcji z pliku z danymi użyć w algorytmie? " << endl;
//    cin >> *number_of_transaction;
//    if (*number_of_transaction < 0) {
//        cout << "Liczba musi być dodatnia. Podaj ją jeszcze raz:" << endl;
//        cin >> *number_of_transaction;
//        if (*number_of_transaction < 0) {
//            cout << "Błędna liczba" << endl;
//            return false;
//        }
//    }
//
//    cout << "Wybrane parametry: plik wejściowy - " << inputFileName << " , numer kolumny z atrybutem decyzyjnym - " <<
//    *d_column << " , rodzaj decyzji - " << *d_type << " , rodzaj algorytmu - " << *a_type <<
//    " , liczba transkacji do wczytania - " << *number_of_transaction << endl;
//    return true;
//}
//
//
//int endProgram() {
//    cout << "Aby zakończyć działanie programu naciśnij Enter...";
//    getchar();
//    cin.ignore();
//    return 0;
//}
