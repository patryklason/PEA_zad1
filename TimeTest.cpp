//
// Created by patry on 22.11.2022.
//

#include <ntdef.h>
#include <profileapi.h>
#include "TimeTest.h"
#include "iostream"
#include "iomanip"
#include "Graph.h"

using namespace std;

void TimeTest::runTest(int iterations, int size, int algorithm) {
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
    long long int totalTime = 0;

    Graph g;
    if(algorithm == 0) {
        for (int i = 0; i < iterations; ++i) {
            g.generateRandomMatrix(size);

            start = read_QPC();
            g.bruteForce();
            elapsed = read_QPC() - start;

            totalTime += elapsed;
        }
    }
    else if(algorithm == 1){
        g.generateRandomMatrix(size);
        g.dpInit();
        for (int i = 0; i < iterations; ++i) {
            g.generateRandomMatrix(size);
            g.dpResetValues();

            start = read_QPC();
            g.startDynamicProgramming();
            elapsed = read_QPC() - start;

            totalTime += elapsed;
        }
    }
    /*start = read_QPC();
     // kod ktorego czas wykonania mierzymy
    elapsed = read_QPC() - start;*/



    cout << "Avg Time [s] = " << fixed << setprecision(3) << ((float)totalTime / (float)iterations)/ (float)frequency << endl;
    cout << "Avg Time [ms] = " << setprecision(3) << (1000.0 * (float)totalTime / iterations) / (float)frequency << endl;
    cout << "Avg Time [us] = " << setprecision(3) << (1000000.0 * (float)totalTime / iterations) / (float)frequency << endl << endl;
    //system("PAUSE");
}

long long int TimeTest::read_QPC() {
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return((long long int)count.QuadPart);
}
