//
// Created by patryk on 07.11.2022.
//

#ifndef PEA_ZAD1_GRAPH_H
#define PEA_ZAD1_GRAPH_H

#include <string>
#include "vector"

using namespace std;
/**
 * Klasa odpowiedzialna za inicjalizacje oraz wykonanie algorytmow na grafie
 * @param size - ilosc miast
 * @param matrix - reprezentacja grafu w postaci tablicy dynamicznej, reprezentujacej macierz kosztow
 * @param cost - uzyskany przez algorytm najnizszy koszt przejscia
 * @param path - uzyskana przez algorytm sciezka o najnizszym koszcie przejscia
 *
 * @param bits -
 * @param dpTemp -
 * @param dpDivisions -
 * @param dpTrack -
 */
class Graph {
public:
    int size;
    int ** matrix;

    Graph();
    ~Graph();

    bool readFromFile(string filename);
    void generateRandomMatrix(int userSize);
    void printMatrix();
    void printResult();

    void bruteForce();

    void dpInit();
    void startDynamicProgramming();
    void dpResetValues();

private:
    //Zmiennie wspolne
    int cost;
    vector<int> path;


    //zmienne do DP
    int bits;
    int ** dpTemp;
    int ** dpDivisions;
    int ** dpTrack;


    int dynamicProgramming(int nodeIndex, int nodeBits);
    void dpCountPath(int nodeIndex, int nodeBits);
};


#endif //PEA_ZAD1_GRAPH_H
