/*!\file drawdata.c
 * \brief Ce fichier contient les fonctions qui gèrent les données généré par les algorithmes.
 * \author Anis CHALI anis.chali1@outlook.com 15612337
 * \date November 28, 2018
 *
*/
#include "drawdata.h"
/*!\brief le nombre à comparer*/
static int algos_number = 0;
/*!\brief le tableau représente une pile de tout les temps de la meme longeuer*/
static lentable_t *table = NULL;
/*!\brief le tableau représente une pile de toutes les données et leurs complexités*/
static table_t *datas = NULL;

/*!\brief Libère la mémoire alloué pour les piles de données.  
 * \param void
 * \return void
 */
void quit(void){
    if (datas != NULL){
        for (int i = 0; i < algos_number; ++i){
            datas[i].size = 0;
            datas[i].index = 0;
            if (datas[i].datas != NULL){
                free(datas[i].datas);
                datas[i].datas = NULL;
            }
        }
        free(datas);
        datas = NULL;
    }
    if (table != NULL){
        for (int i = 0; i < algos_number; ++i){
            table[i].size = 0;
            table[i].index = 0;
            table[i].length = 0;
            if (table[i].times != NULL){
                free(table[i].times);
                table[i].times = NULL;
            }
        }
        free(table);
        table = NULL; 
    }
    algos_number = 0;
    return;
}

/*!\brief Alloue la mémoire les piles de données.  
 * \param nombre_algos le nombre d'algorithme à comparer.
 * \return void
 */
void initDrawData(int nombre_algos){
    algos_number = nombre_algos;
    atexit(quit);
    if (!table){
        table = calloc(sizeof *table, algos_number);
        for (int i = 0; i < algos_number; ++i){
            table[i].size = INITIAL_SIZE;
            table[i].index = 0;
            table[i].times = calloc(sizeof *(table[i].times), INITIAL_SIZE);
            if (!table[i].times){
                fprintf(stderr, "Allocation de tableau times à échoué\n");
                exit(-1);
            }
        }
    }
    if (!datas){
        datas = calloc(sizeof *datas, algos_number);
        if (!datas){
            fprintf(stderr, "Allocation de tableau des algorithmes à échoué\n");
            exit(-1);
        }
        for (int i = 0; i < algos_number; ++i){
            datas[i].size = INITIAL_SIZE;
            datas[i].index = 0;
            datas[i].datas = calloc(sizeof *(datas[i].datas), INITIAL_SIZE);
            if (!datas[i].datas){
                fprintf(stderr, "Allocation de tableau des données à échoué\n");
                exit(-1);
            }
        }  
    }

}

/*!\brief Calcule le temps moyen d'évolution.  
 * \param algo l'algorithme pour lequel on récupère le temps moyen.
 * \return void
 */
float averageTime(int algo){
    float average = 0.0;
    float *pt = table[algo].times;
    int n = table[algo].index;
    for (int i = 0; i < n; ++i){
        average += pt[i];
    }
    average /= (float) n;
    return average;
}

/*!\brief Algorithme dichotomique pour trouver une longueur déja présente dans le tableau.  
 * \param length la longueur recherché dans le tableau datas.
 * \param algo l'algorithme pour laquel on récupère l'index.
 * \return int index de la longueur recherché.
 */
int findWithLength(int length, int algo){
    int middle = 0, start = 0, end = datas[algo].index;
    while(start <= end){
        middle = (int)((start + end) / 2); 
        if (length > datas[algo].datas[middle].length){
            start = middle + 1;
        }
        else if (length < datas[algo].datas[middle].length){
            end = middle - 1;
        }
        else {
            return middle;
        }
    }
    return -1;
}

/*!\brief Ajouter une data contenant les différnts temps d'évolution et de complexité.
 * \param algo l'algorithme pour lequel on ajoute les données.  
 * \param length la longueur de la droite pour laquel on ajoute les temps.
 * \param time temps moyen.
 * \param min temps de meilleur des cas.
 * \param max temps de pire des cas.
 * \param storage espace mémoire.
 * \return void
 */
void pushData(int algo, int length, float time, float min, float max, int storage){
  int n = datas[algo].index;
  data_t * data = datas[algo].datas;
    if ( !(n < datas[algo].size) ){
        datas[algo].size *= 2;
        datas[algo].datas = realloc(datas[algo].datas, (datas[algo].size) * sizeof(data_t));
    }
    if (data[n - 1].length > length){
        int index = 0;
        if ((index = findWithLength(length, algo)) != -1){
            data[index].average_time += time;
            data[index].average_time /= 2.0;
            if (data[index].best_time > min){
                data[index].best_time = min;
            }
            if (data[index].worst_time < max){
                data[index].worst_time = max;
            }
            data[index].storage = storage;
            return;
        }
    }
    data[n].length = length;
    data[n].average_time = time;
    data[n].worst_time = max;
    data[n].best_time = min;
    data[n].storage = storage;
    datas[algo].index++;
}

/*!\brief Calcule de la complexité mémoire.
 * \param algo l'algorithme pour lequel on calcule la complexité mémoire.  
 * \return int un entier représentant la complexité mémoire.
 */
int calculateStorage(int algo){
    int storage_complexity[2];
    storage_complexity[DDA] = 20;
    storage_complexity[AAS] = 20;
    return storage_complexity[algo];
}

/*!\brief Ajouter une data contenant les différnts temps d'évolution et de complexité.
 * \param algo l'algorithme pour lequel on ajoute les données.  
 * \param length la longueur de la droite pour laquel on ajoute les temps.
 * \param time temps moyen.
 * \param min temps de meilleur des cas.
 * \param max temps de pire des cas.
 * \param storage espace mémoire.
 * \return void
 */
float max_time(table_t *table, int algo, int field){
    float max_time = 0.0;
    float curr_time[COMPLEXITY];
    if (field == STORAGE) return (float) calculateStorage(algo);
    for (int i = 0; i < table[algo].index-1; ++i){
        curr_time[AVERAGE] = table[algo].datas[i].average_time;
        curr_time[WORST] = table[algo].datas[i].worst_time;
        curr_time[BEST] = table[algo].datas[i].best_time;
        if (max_time < curr_time[field]){
            max_time = curr_time[field];
        }
    }
    return max_time;
}

/*!\brief Récupère le temps minimum pour le meilleur des cas.
 * \param algo l'algorithme pour lequel on récupère le meilleur des cas.  
 * \return float qui correspond au meilleur des cas.
 */
float min_time_bis(int algo){
    float min_time = 0.0;
    float *pt = table[algo].times;
    int n = table[algo].index;
    min_time = pt[0];
    for (int i = 1; i < n; ++i){
        if (min_time > pt[i]){
            min_time = pt[i];
        }
    } 
    return min_time;
}

/*!\brief Récupère le temps maximum pour le pire des cas.
 * \param algo  l'algorithme pour lequel on récupère le pire des cas.  
 * \return float qui correspond au pire des cas.
 */
float max_time_bis(int algo){
    float max_time = 0.0;
    float *pt = table[algo].times;
    int n = table[algo].index;
    for (int i = 0; i < n; ++i){
        if (max_time < pt[i]){
            max_time = pt[i];
        }
    }
    return max_time;
}

/*!\brief Ajoute les temps d'évolutions des droites de la même longueur.
 * \param length  la longueur pour laquel on récupère les temps. 
 * \param time  le temps concernant une longueur donné.
 * \param algo  l'algorithme pour lequel on met le temps.  
 * \return void
 */
void pushTable(int length, float time, int algo){
    if ( !(table[algo].index < table[algo].size) ){
        table[algo].size *= 2;
        table[algo].times = realloc(table[algo].times, table[algo].size * sizeof *(table[algo].times));
    }
    if (table[algo].length != length){ //vérifier si ce n'est pas la même longueur
        float aver_time = averageTime(algo);//pour l'ajouter dans les données.
        float mini_time = min_time_bis(algo);
        float maxi_time = max_time_bis(algo);
        int storage = calculateStorage(algo);
        pushData(algo, table[algo].length, aver_time, mini_time, maxi_time, storage);
        table[algo].index = 0;
    }
    table[algo].times[table[algo].index] = time;
    table[algo].length = length;
    table[algo].index++;
}

/*!\brief Libère un tableau de datas.
 * \param *tab  le tableau à libéré. 
 * \return void
 */
void freeDatas(table_t *tab){
    if (tab != NULL){
        for (int i = 0; i < algos_number; ++i){
            tab[i].size = 0;
            tab[i].index = 0;
            if (tab[i].datas != NULL){
                free(tab[i].datas);
                tab[i].datas = NULL;
            }
        }
        free(tab);
        tab = NULL;
    }
}

/*!\brief Fonction passé à qsort pour trier les données en fonction de leurs longueur.
 * \param *data1  la donnée à comparer.
 * \param *data2  la donnée à comparer. 
 * \return int  résultat de la comparaison.
 */
int compare(const void *data1, const void *data2){
    return ((data_t *) data1)->length - ((data_t *) data2)->length;
}

/*!\brief Fonction qui récupère le tableau des données pour les passer à d'autres fonctions.
 * \param void
 * \return table_t* le tableau de données.
 */
table_t * getDatas(void){
    table_t * final = calloc(sizeof *final, algos_number);
    if (!final){
        fprintf(stderr, "Allocation de tableau des résultats a échoué\n");
        exit(-1);
    }
    for (int i = 0; i < algos_number; ++i){
        final[i].size = datas[i].size;
        final[i].index = datas[i].index;
        final[i].datas = calloc(sizeof *(final[i].datas), final[i].size);
        final[i].datas = memcpy(final[i].datas, datas[i].datas, final[i].size * sizeof *(final[i].datas));
        if (!final[i].datas){
            fprintf(stderr, "Allocation de tableau des données finaux a échoué\n");
            freeDatas(final);
            exit(-1);
        }
        qsort(final[i].datas, final[i].index,sizeof *(final[i].datas), compare);
        final[i].datas[0].length = 0;
        final[i].datas[0].average_time = 0.0;
        final[i].datas[0].best_time = 0.0;
        final[i].datas[0].worst_time = 0.0;
    }      
    return final;
}

/*!\brief Fonction qui récupère la longueur maximal de tableau des données.
 * \param *table le tableau de données.
 * \param algo  pour lequel on récupère la longueur maximal.
 * \return int  la longueur maximal.
 */
int max_length(table_t *table, int algo){
    return table[algo].datas[table[algo].index - 1].length;
}

/*!\brief Fonction qui sauvegarde le tableau des données sous un fichier texte.
 * \param *path     chemin de sauvegarde.
 * \param *datas le tableau de données.
 * \return void.
 */
void saveAsFile(char *path, table_t *datas){
    FILE *file = fopen(path,"w");
    
    for (int i = 2; i < datas[DDA].index; ++i){
        fprintf(file,"DDA ==> len: %d (px) average: %.2f (CPU ticks) best: %.2f (CPU ticks) worst: %.2f (CPU ticks) storage: %d (octet)\n",
        datas[DDA].datas[i].length,
        datas[DDA].datas[i].average_time,
        datas[DDA].datas[i].best_time,
        datas[DDA].datas[i].worst_time,
        datas[DDA].datas[i].storage);
        fprintf(file,"AAS ==> len: %d (px) average: %.2f (CPU ticks) best: %.2f (CPU ticks) worst: %.2f (CPU ticks) storage: %d (octet)\n",
        datas[AAS].datas[i-1].length,
        datas[AAS].datas[i-1].average_time,
        datas[AAS].datas[i-1].best_time,
        datas[AAS].datas[i-1].worst_time,
        datas[AAS].datas[i-1].storage);
        fprintf(file,"PLUS ==> len: %d (px) average: %.2f (CPU ticks) best: %.2f (CPU ticks) worst: %.2f (CPU ticks) storage: %d (octet)\n",
        datas[2].datas[i].length,
        datas[2].datas[i].average_time,
        datas[2].datas[i].best_time,
        datas[2].datas[i].worst_time,
        datas[2].datas[i].storage);
    }
    fclose(file);
    free(file);
}
