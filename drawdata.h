#ifndef DRAWDATA_H
#define DRAWDATA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 1024
enum{
    AAS = 0,
    DDA = 1,
    TWO = 2
};


typedef struct data_t{
    int length;
    float best_time;
    float worst_time;
    float average_time;
    int storage;
}data_t;

typedef struct lentable_t{
    int size;
    int index;
    int length;
    float *times;
}lentable_t;



typedef struct table_t{
    int size;
    int index;
    data_t *datas;
}table_t;

table_t * getDatas(void);
void freeDatas(table_t *tab);
void pushTable(int length, float time, int algo);
void initDrawData(int nombre_algos); 
float max_time(table_t *table, int algo);
int max_length(table_t *table, int algo);

#endif