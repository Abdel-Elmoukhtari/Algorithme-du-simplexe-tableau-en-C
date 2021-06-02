/*
Author: Abida Hassan
Filier: SDAD
*/
#include<stdlib.h>

void libererMatriceReelle(double** A,int L){
	int i;
	for(i = 1;i<=L;i++){
		free(A[i]+1);
		
	}
	A = NULL;
	free(A);
}
