//
// Created by patry on 07.11.2022.
//

#include <iostream>
#include <vector>
#include "Graph.h"
#include "fstream"
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
    cout << "Najmniejsza suma wag: " << minPathValue << endl;
    for(int j: bestPath)
        cout << j << " -> ";
    cout << "0" << endl;

}