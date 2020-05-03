/*!\file algorithmes.h
 * \brief Ce fichier les algorithme B&B AAS 2000 et B DDA 65 et l'améliorartion.
 * \author Anis CHALI anis.chali1@outlook.com 15612337
 * \date November 28, 2018
 *
*/
#ifndef ALGORITHMES_H
#define ALGORITHMES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!\brief déssine une droite de \a u et \a v avec l'algorithme de 
 * Bresenham DDA 65.
 * \param u représente (x2 - x1), en pixels.
 * \param v représente (y2 - y1), en pixels.
 * \return void
 */
void droite_br65(int u, int v);

/*!\brief déssine une droite de \a u et \a v avec l'algorithme de 
 * Bourdin & Boyer AAS 2000.
 * \param u représente (x2 - x1), en pixels.
 * \param v représente (y2 - y1), en pixels.
 * \return void
 */
void droite_AAS(int u, int v);

/*!\brief déssine une droite de \a u et \a v avec une tentative d'amélioration de l'algorithme de 
 * Bourdin & Boyer AAS 2000.
 * \param u représente (x2 - x1), en pixels.
 * \param v représente (y2 - y1), en pixels.
 * \return void
 */
void droite_AASPLUS(int u,int v);


#endif
