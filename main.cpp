#include <iostream>
#include "Graph.h"
#include "TimeTest.h"

using namespace std;


void readFromFile(Graph *g) {
    string filename;

    cout << endl << "Podaj sciezke do pliku: ";
    cin >> filename;

    if(!g->readFromFile(filename))
        cout << "Blad odczytu pliku!" << endl;
    else
        cout << "Plik wczytany prawidlowo!" << endl;
}

bool mainMenu(Graph *g){
    char choice;

    cout << "============== Menu Glowne ==============" << endl;
    cout << "[0] Wyjscie z programu" << endl;
    cout << "[1] Wczytaj dane z pliku" << endl;
    cout << "[2] Wyswietl reprezentacje grafu" << endl;
    cout << "[3] Rozpocznij algorytm Brute Force" << endl;
    cout << "[4] Rozpocznij algorytm Dynamic Programming" << endl;

    cout << endl << "Twoj wybor: ";
    cin >> choice;
    cout << endl;

    switch (choice) {
        case '0': return false;
        case '1': {readFromFile(g); break;}
        case '2': {g->printMatrix(); break;}
        case '3': {g->bruteForce(); break;}
        case '4': {g->dpInit(); g->startDynamicProgramming(); g->printResult(); break;}
        default: cout << "Blad wyboru!" << endl;
    }
    return true;
}

int main() {


    //TimeTest timeTest;
    //timeTest.runTest(100, 6, 1);
    /*Graph g;
    if(!g.readFromFile("../tsp_13.txt"))
        cout << "Blad odczytu pliku!";
    else
        g.printMatrix();
    cout << endl << endl;*/
    Graph g;
    while(mainMenu(&g));

    return 0;
}