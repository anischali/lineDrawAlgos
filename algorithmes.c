/*!\file algorithmes.c
 * \brief Ce fichier les algorithme B&B AAS 2000 et B DDA 65 et l'améliorartion.
 * \author Anis CHALI anis.chali1@outlook.com 15612337
 * \date November 28, 2018
 *
*/
#include "algorithmes.h"

/*!\brief déssine une droite de \a u et \a v avec l'algorithme de 
 * Bresenham DDA 65.
 * \param u représente (x2 - x1), en pixels.
 * \param v représente (y2 - y1), en pixels.
 * \return void
 */
void droite_br65(int u, int v) {
    int x, y, delta, incD, incH; 
    incH   = v << 1;
    delta  = incH - u;
    incD   = delta - u;
    for (x = 0, y = 0; x <= u; x++) 
    {
        if (delta > 0) {
            y++;
            delta += incD;
        }
        else {
            delta += incH;
        }
    }
}

/*!\brief déssine une droite de \a u et \a v avec l'algorithme de 
 * Bourdin & Boyer AAS 2000.
 * \param u représente (x2 - x1), en pixels.
 * \param v représente (y2 - y1), en pixels.
 * \return void
 */
void droite_AAS(int u, int v){
    int E = 0, incXA = 0, incXB = 0;
    int XB = (u - v) / v;
    int XA = XB + 1;    
    incXA   = XA * 2 * v;
    E  = incXA - u;
    incXB   = XA * 2 * (v - u);    
    int y = 0;                    
    for (int x = 0; x <= u;){     
        if (E < 0){
            x += XA;
            ++y;
            ++x;
            E += incXA;            
        }else{
            x += XB;
            ++y;
            ++x;
            E += incXB;
        }
    }
}


/*!\brief déssine une droite de \a u et \a v avec une tentative d'amélioration de l'algorithme de 
 * Bourdin & Boyer AAS 2000.
 * \param u représente (x2 - x1), en pixels.
 * \param v représente (y2 - y1), en pixels.
 * \return void
 */
void droite_AASPLUS(int u,int v){
    int y = 0;
    float xa = u / (float) v;
    float x = xa;  
    for (y = 0; y < v;)
    {
        y++;
	//dessin
        x += xa;
	
    }
}
