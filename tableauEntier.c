/*
Author: Abida Hassan
Filier: SDAD
*/
#include<stdio.h>

int* tableauEntier(int N){
	
	int *T;
	T = (int*) malloc(N*sizeof(int));
	if(T == NULL){
		printf("tableauReel: pas assez de memoire\n");
		exit(-1);
	}
	
	return T - 1;
}
