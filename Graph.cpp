//
// Created by patry on 07.11.2022.
//

#include <iostream>
#include <vector>
#include "Graph.h"
#include "fstream"
#include "ctime"
using namespace std;
/**
 * Funkcja wczytuje macierz z pliku do reprezentacji macierzy wag w postaci dynamicznej tablicy dwuwymiarowej
 * @param filename - nazwa pliku
 * @return
 *      true - plik odczytany poprawnie
 *      false - blad odczytu pliku
 */
bool Graph::readFromFile(string filename) {
    fstream file(filename, ios_base::in);

    if(file.is_open()) {

        int a;
        file >> a;
        size = a;

        matrix = new int *[size];
        for (int i = 0; i < size; i++) {
            matrix[i] = new int[size];
        }
        int row = 0;
        int column = 0;

        while (file >> a) {
            matrix[row][column] = a;

            if (column >= (size - 1)) {
                ++row;
                column = 0;
            } else
                ++column;

        }
        return true;
    }
    //wystapil blad odczytu
    return false;
}


/**
 * Funkcja wyswietla reprezentacje macierzow kosztow grafu
 */
void Graph::printMatrix() {
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
/**
 * Funkcja przeprowadza algorytm Brute Force i wyswietla wyniki na ekranie
 * Algorytm sprawdza wszystkie kombinacje, zakladajac 0 jako wierzcholek poczatkowy.
 * Zlozonosc algorytmu wynosi (n-1)!, poniewaz 0 na poczatku jest nieruszane
 * @param permutation - tablica przechowujaca aktualna permutacje (0 na poczatku jest stale)
 * @param bestPath - droga o najnizszym koszcie
 * @param minPathValue - najmniejszy koszt dojscia
 * @param currPathValue - zmienna pomocnicza, przechowuje koszt dla danej iteracji
 */
void Graph::bruteForce() {
    path.clear();

    vector<int> permutation;
    vector<int> bestPath;
    int minPathValue = INT_MAX, currPathValue = 0;



    for(int i = 0; i < size; i++) {
        // przypisanie po kolei indeksow wierzcholkow
        permutation.push_back(i);
    }

    int i;
    do{
        // wyzerowanie aktualnej sumy wag
        currPathValue = 0;
        // przypisanie do sumy kosztow wag kolejnych przejsc w permutacji
        for(i = 0; i < size - 1; i++)
            currPathValue += matrix[permutation[i]][permutation[i + 1]];

        // dodanie kosztu przejscia z ostatniego wierzcholka do wierzcholka 0
        currPathValue += matrix[permutation[i]][permutation[0]];

        // ustawienie nowego minimalnego kosztu oraz sciezki
        if(currPathValue < minPathValue) {
            minPathValue = currPathValue;
            bestPath = permutation;
        }
        // next_permutation - funkcja podmienia liczby w tablicy, tworzac wszystkie mozliwe permutacje
    } while (next_permutation(std::next(permutation.begin()), permutation.end()));

    // wypisanie wynikow
    cost = minPathValue;
    path = bestPath;

    /*cout << "Najmniejsza suma wag: " << minPathValue << endl;
    for(int j: bestPath)
        cout << j << " -> ";
    cout << "0" << endl;*/

}
/**
 * Funkcja inicjalizuje niezbędne dane do przeprowadzenia algorytmu Dynamic Programming
 * cost = 0
 * dpTemp - wypelnione danymi z matrix
 * bits = 1 na miejscu o 1 dalszym niz ilosc miast
 * dpDivisions - wypelnione -1
 * dpTrack - wypelnione -1
**/
void Graph::dpInit() {
    cost = 0;

    bits = 1 << size;

    dpTemp = new int *[size];
    for (int i = 0; i < size; i++) {
        dpTemp[i] = new int[size];
    }


    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            dpTemp[i][j] = matrix[i][j];
        }
    }


    dpDivisions = new int *[size];
    for (int i = 0; i < size; i++) {
        dpDivisions[i] = new int[bits];
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < bits; ++j) {
            dpDivisions[i][j] = -1;
        }
    }


    dpTrack = new int *[size];
    for (int i = 0; i < size; i++) {
        dpTrack[i] = new int[bits];
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < bits; ++j) {
            dpTrack[i][j] = -1;
        }
    }
}
/**
 * Funkcja rozpoczyna algorytm Dynamic Programming
 * bits - jedynki na indeksie kazdego miasta (do wlasciwej funkcji przekazujemy 0 na miejscu wierzcholka startowego)
 * do dpDivisions przekazujemy wartosci {1,2,3}, 0
 */
void Graph::startDynamicProgramming() {
    bits--;

    for(int i = 0; i < size; ++i) {
        dpDivisions[i][0] = dpTemp[i][0];
    }

    cost = dynamicProgramming(0, bits - 1);
    dpCountPath(0, bits - 1);
}
/**
 *
 * @param nodeIndex - index wierzcholka startowego dla danego wywolania
 * @param nodeBits - bity okreslajace sprawdzany podproblem dla danego wykonania
 * @return cost - najniszy uzyskany koszt dla danego problemu
 */
int Graph::dynamicProgramming(int nodeIndex, int nodeBits) {
    // zmienna lokalna, potrzebna do kontroli zapisania uzyskanego rozwiazania
    int result = -1;
    // jezeli dany podproblem ma juz rozwiazanie, zwroc jego wynik
    if(dpDivisions[nodeIndex][nodeBits] != -1)
        return dpDivisions[nodeIndex][nodeBits];

    for (int i = 0; i < size; i++) {
        //ustawia bit 0 na i-tym wierzcholku
        int mask = bits - (1 << i);
        // bitowy AND miedzy poczatkowymi bitami a maska
        int masked = nodeBits & mask;
        //jesli poprawnie wyznaczono nowe bity, przechodzimy dalej
        if(masked != nodeBits) {
            // value - przechowuje koszt z wezla startowego do wezla i-tego + koszt od i-tego do pozostalych
            int value = dpTemp[nodeIndex][i] + dynamicProgramming(i, masked);

            // jezeli nie ma jeszcze rozwiazania badz nowe jest lepsze, zapisz je
            if(result == -1 || value < result) {
                result = value;
                // przypisanie kolejnego wezla do macierzy przejsc
                dpTrack[nodeIndex][nodeBits] = i;
            }
        }
    }
    // przypisanie zapisanego rozwiazania do macierzy podproblemow
    dpDivisions[nodeIndex][nodeBits] = result;
    return result;
}
/**
 * sluzy do odnalezienia i zapisania sciezki o najmniejszym koszcie
 * @param nodeIndex - index wierzcholka startowego dla danego wywolania
 * @param nodeBits - bity okreslajace sprawdzany podproblem dla danego wykonania
 */
void Graph::dpCountPath(int nodeIndex, int nodeBits) {
    // dodanie wierzcholka poczatkowego
    path.push_back(0);
    int nextNode = dpTrack[nodeIndex][nodeBits];

    // jezeli istnieje kolejny wezel
    while (nextNode != -1) {
        path.push_back(nextNode);
        // ustawia 0 na indeksie odwiedzonego miasta
        int mask = bits - (1 << nextNode);
        // wynikiem jest zbior miast nieodwiedzonych
        int masked = nodeBits & mask;

        nextNode = dpTrack[nextNode][masked];
        nodeBits = masked;
    }
    // dodanie na koniec spowrotem wierzcholka startowego
    path.push_back(0);
}



void Graph::printResult() {

    cout << "Najkrotsza sciezka: ";
    for (int i = 0; i < path.size() - 1; ++i) {
        cout << path[i] << " -> ";
    }
    cout << path[path.size() - 1] << endl;
    cout << "Minimalny koszt: " << cost << endl;


    for (int i = 0; i < size; ++i) {
        delete[] dpDivisions[i];
        delete[] dpTemp[i];
        delete[] dpTrack[i];
    }
    delete[] dpDivisions;
    delete[] dpTemp;
    delete[] dpTrack;
    path.clear();
    cost = 0;
}

Graph::Graph() {

}

Graph::~Graph() {
    /*for (int i = 0; i < size; ++i) {
        delete[] dpDivisions[i];
        delete[] dpTemp[i];
        delete[] dpTrack[i];
        delete[] matrix[i];
    }
    delete[] dpDivisions;
    delete[] dpTemp;
    delete[] dpTrack;
    delete[] matrix;*/
    path.clear();
    cost = 0;
}

void Graph::generateRandomMatrix(int userSize) {
    this->size = userSize;

    srand(time(NULL));

    matrix = new int *[size];
    for (int i = 0; i < size; ++i) {
        matrix[i] = new int [size];
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if(i != j)
                matrix[i][j] = rand() % 99 + 1;
            else
                matrix[i][j] = 0;
        }

    }
}

void Graph::dpResetValues() {
    cost = 0;
    path.clear();
    bits = 1 << size;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            dpTemp[i][j] = matrix[i][j];
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < bits; ++j) {
            dpDivisions[i][j] = -1;
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < bits; ++j) {
            dpTrack[i][j] = -1;
        }
    }
}



