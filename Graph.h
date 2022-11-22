//
// Created by patryk on 07.11.2022.
//

#ifndef PEA_ZAD1_GRAPH_H
#define PEA_ZAD1_GRAPH_H

#include <string>
#include "vector"

using namespace std;
/**
 * Klasa odpowiedzialna za operacje na grafie
 * @param size - ilosc miast
 * @param matrix - reprezentacja grafu w postaci tablicy dynamicznej prezentujacej macierz kosztow
 *
 */
class Graph {
public:
    int size;
    int ** matrix;


    void generateRandomMatrix(int userSize);

    void dpInit();

    void startDynamicProgramming();

    bool readFromFile(string filename);
    void printMatrix();
    void bruteForce();

    void printResult();

    Graph();
    ~Graph();

private:
    int dynamicProgramming(int nodeIndex, int nodeBits);
    void dpCountPath(int nodeIndex, int nodeBits);

    int cost;

    int ** dpTemp;
    vector<int> path;
    int bits;
    int ** dpDivisions;
    int ** dpTrack;
};


#endif //PEA_ZAD1_GRAPH_H
