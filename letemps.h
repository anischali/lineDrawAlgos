/*!\file letemps.h
 * \brief Ce fichier contient les prototypes et structures qui r�cup�re le temps d'�x�cution.
 * \author Anis CHALI anis.chali1@outlook.com 15612337
 * \date November 28, 2018
 *
*/
#ifndef LETEMPS_H
#define LETEMPS_H
#include "drawdata.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define N_TEST 1000



/**
 * \brief         fonction_t contenant un indice, un pointeur de fonction vers 
 *                la fonction � tester et le nom de l'algorithme.  
 */
typedef struct fonction_t {
  int algo; 
  void (* fct)(int , int);
  char name[30];
} fonction_t;
/**
 * \brief R�cup�re le temps d'�x�cution.
 */
void test_rapidite2(int length, int u, int v, fonction_t * algos);

#endif