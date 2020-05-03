/*!\file drawdata.h
 * \brief Ce fichier contient les fonctions et les prototypes qui gèrent les données généré par les algorithmes.
 * \author Anis CHALI anis.chali1@outlook.com 15612337
 * \date November 28, 2018
 *
*/
#ifndef DRAWDATA_H
#define DRAWDATA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \brief taille initiale des piles.
 */
#define INITIAL_SIZE 1024

/**
 * \brief indice des algorithmes à comparer.
 */
enum{
    AAS = 0,
    DDA = 1,
    TWO = 2
};
/**
 * \brief indice des différentes complexités.
 */
enum{
    AVERAGE = 0, //moyen
    WORST = 1,   // pire
    BEST = 2,    // meilleur
    STORAGE = 3, // mémoire
    COMPLEXITY = 4 
};
/**
 * \brief structures pour les différents complexités ainsi que la longueur.
 */
typedef struct data_t{
    int length;
    float best_time;
    float worst_time;
    float average_time;
    int storage;
}data_t;
/**
 * \brief structures pour les données de la même longueur.
 */
typedef struct lentable_t{
    int size;
    int index;
    int length;
    float *times;
}lentable_t;


/**
 * \brief structures pour faire un tableau de données.
 */
typedef struct table_t{
    int size;
    int index;
    data_t *datas;
}table_t;
/**
 * \brief Récupère les données.
 */
table_t * getDatas(void);
/**
 * \brief Libère les données.
 */
void freeDatas(table_t *tab);
/**
 * \brief Ajoute les différents temps dans pile.
 */
void pushTable(int length, float time, int algo);
/**
 * \brief Initialise les piles données.
 */
void initDrawData(int nombre_algos);
/**
 * \brief Le temps maximum d'un algorithme.
 */ 
float max_time(table_t *table, int algo, int field);
/**
 * \brief La longueur maximal d'un algorithme.
 */
int max_length(table_t *table, int algo);
/**
 * \brief Sauvegarde dans un fichier.
 */
void saveAsFile(char *path, table_t *datas);
/**
 * \brief Calcule la complexité en espace mémoire.
 */
int calculateStorage(int algo);
#endif