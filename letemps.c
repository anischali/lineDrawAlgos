#include "letemps.h"







void test_rapidite(int length, int u, int v, fonction_t * algos) {
    float diff = 0.0, cost = 0.0;
    clock_t t1;
    clock_t t2;
    while(algos->fct) {
        diff = 0.0, cost = 0.0;
        
        for (int i = 0; i <= N_TEST; ++i){ 
            t1 = clock(); 
            algos->fct(u, v);
            t2 = clock();   
            diff += t2 - t1;
        }
        cost = diff / N_TEST;
        fprintf(stdout, "%s dessine la droite de longueur %d en \t%.6f secondes.\n",
	    algos->name, length, cost);
        algos++;
    }
}

void test_rapidite2(int length, int u, int v, fonction_t * algos) {
    float diff = 0.0, cost = 0.0;
    clock_t t1;
    clock_t t2;
    while(algos->fct) {
        diff = 0.0, cost = 0.0;
        t1 = clock();
        for (int i = 0; i <= N_TEST; ++i){  
            algos->fct(u, v);
        }
        t2 = clock();   
        diff = (float) t2 - t1;
        cost = diff / (float) N_TEST;
        pushTable(length, cost, algos->algo); 
        //fprintf(stdout, "%s dessine la droite de longueur %.0f en \t%.6f secondes.\n",
	    //algos->name, length, cost);
        algos++;
    }
}
