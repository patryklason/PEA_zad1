//
// Created by patryk on 07.11.2022.
//

#ifndef PEA_ZAD1_GRAPH_H
#define PEA_ZAD1_GRAPH_H

#include <string>

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


    bool readFromFile(string filename);
    void printMatrix();
    void bruteForce();
};


#endif //PEA_ZAD1_GRAPH_H
