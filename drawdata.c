#include "drawdata.h"



static int algos_number = 0;
static lentable_t *table = NULL;
static table_t *datas = NULL;



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

void pushData(int algo, int length, float time){
    if ( !(datas[algo].index < datas[algo].size) ){
        datas[algo].size *= 2;
        datas[algo].datas = realloc(datas[algo].datas, datas[algo].size * sizeof *(datas[algo].datas));
    }
    
    if (datas[algo].datas[datas[algo].index - 1].length < length){
        int index = 0;
        if ((index = findWithLength(length, algo)) != -1){
            datas[algo].datas[index].average_time += time;
            datas[algo].datas[index].average_time /= 2.0;
            return;
        }
    }
    datas[algo].datas[datas[algo].index].length = length;
    datas[algo].datas[datas[algo].index].average_time = time;
    datas[algo].index++;
}

void pushTable(int length, float time, int algo){

    if ( !(table[algo].index < table[algo].size) ){
        table[algo].size *= 2;
        table[algo].times = realloc(table[algo].times, table[algo].size * sizeof *(table[algo].times));
    }
    if (table[algo].length != length){
        float aver_time = averageTime(algo);
        pushData(algo, table[algo].length, aver_time);
        table[algo].index = 0;
    }
    table[algo].times[table[algo].index] = time;
    table[algo].length = length;
    table[algo].index++;
}

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

int compare(const void *data1, const void *data2){
    
    return ((data_t *) data1)->length - ((data_t *) data2)->length;

}



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
    }      
    

    return final;
}


int max_length(table_t *table, int algo){
    return table[algo].datas[table[algo].index - 1].length;
}


float max_time(table_t *table, int algo){
    float max_time = 0.0;
    float curr_time = 0.0;
    for (int i = 0; i < table[algo].index; ++i){
        curr_time = table[algo].datas[i].average_time;
        if (max_time < curr_time){
            max_time = curr_time;
        }
    }
    return max_time;
}