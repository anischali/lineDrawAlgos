#ifndef LETEMPS_H
#define LETEMPS_H
#include "drawdata.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define N_TEST 1000




typedef struct fonction_t {
  int algo;
  void (* fct)(int , int);
  char name[30];
} fonction_t;



void test_rapidite(int ,int , int , fonction_t * );
void test_rapidite2(int, int, int, fonction_t *);

#endif