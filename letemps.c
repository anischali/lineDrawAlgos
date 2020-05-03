/*!\file letemps.c
 * \brief Ce fichier contient les fonctions qui r�cup�re le temps d'�x�cution.
 * \author Anis CHALI anis.chali1@outlook.com 15612337
 * \date November 28, 2018
 *
*/
#include "letemps.h"

/*!\brief R�cup�re le temps d'�x�cution d'une fonction pass� en param�tre. 
 * \param length, la longueur de la droite � dessiner.
 * \param u repr�sente (x2 - x1), en pixels.
 * \param v repr�sente (y2 - y1), en pixels.
 * \param algos, structure contenant l'algorithme et le nom de l'algorithme.
 * \return void.
 */
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
        algos++;
    }
}
