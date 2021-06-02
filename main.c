/*
Author: Abida Hassan
Filier: SDAD
*/
#include<stdio.h>
#include<stdlib.h>

#include "tableauReel.c"
#include "tableauEntier.c"
#include "remplirMatriceReelle.c"
#include "remplirTableauReel.c"
#include "matriceReelle.c"
#include "afficherMatriceReelle.c"
#include "afficherTableauReel.c"
#include "libererTableauReel.c"
#include "libererMatriceReelle.c"
#include "maxTabReel.c"
#include "posMaxTabReel.c"
#include "posMinPositifTabReel.c"

int main(){
	
	double* tableauReel(int N);
	int* tableauEntier(int N);
	double** matriceReelle(int L,int C);
	void remplirMatriceReelle(double **A, int L,int C,FILE *pfichier);
	void remplirTableauReel(double *T, int N,FILE *pfichier);
	void afficherMatriceReelle(double **A,int L,int C);
	void afficherTableauReel(double *T,int N);
	void libererTableauReel(double *T);
	void libererMatriceReelle(double **A,int L);
	double maxTabReel(double *T,int N);
	int posMaxTabReel(double *T,int N);
	int posMinPositifTabReel(double *T,int N);
	//nombre de contraintes
	int m;
	//nombre de variable de décision
	int n;
	//pointeur sur le ficher donnee.txt
   	FILE *pFichier;
   	
   	//vecteur reel de taille m
	double* rapport;
	//vecteur entier de base de taille m 
	int* J;
	//la matrice A de taille (m*n)
	double** A;
	//vecteur C de taille n
	double* C;
	//vecteur B de taille m
	double* B;
	//le max de la fonction objective
	double maxC;
	double max;
	//les indices i et j
	int i,j;
	int indiceE,indiceS;
	double pivot;
	double cIndiceE;
	
	
   	if ((pFichier = fopen("donnee.txt","r")) == NULL){
       	printf("Erreur dans l\'overture du fichier!");
       	exit(1);
   	}
   	
   		
   	fscanf(pFichier,"%d", &n);
   	fscanf(pFichier,"%d", &m);
	
	//réserver l'espace mémoire
	A = matriceReelle(m,n);
	B = tableauReel(m);
	C = tableauReel(n);
	
	//remplir les donnés
	remplirMatriceReelle(A,m,n,pFichier);
	remplirTableauReel(B,m,pFichier);
	remplirTableauReel(C,n,pFichier);
	
	//nombre de contrainte et d'inégalités
	printf("nombre de contraintes = %d nombre de variables de décision = %d \n",m,n);
	//afficher la matrice 
	printf("la matrice A\n");
	afficherMatriceReelle(A,m,n);
	
	//afficher le vecteur B
	printf("\n le vecteur B:\n");
	afficherTableauReel(B,m);
	
	//afficher le vecteur C
	printf("\n le vecteur C:\n");
	afficherTableauReel(C,n);
	
	//réserver l'espace mémoire pour rapport
	rapport = tableauReel(m);
	
		
	//réserver l'espace mémoire pour le vecteur J
	J = tableauEntier(m);
		
	//remplir J
	for(i = 1;i<=m;i++){
		J[i] = n - m + i;
	}	
	
	//début du simplex
	maxC = 1;
	max = 0;
	int index = 1;
	while(maxC > 0){
	
	maxC = maxTabReel(C,n);	
	if(maxC>0){
	printf("\n\n######################################");
	printf("\nEtape %d\n",index);
	
	indiceE = posMaxTabReel(C,n);
	printf("indice d\'entré = %d\n",indiceE);
	for(i = 1;i<=m;i++){
		if(A[i][indiceE] != 0){
			rapport[i] = B[i]/A[i][indiceE];	
		}else{
			rapport[i] = -1;
		}
	}
	
	
	indiceS = posMinPositifTabReel(rapport,m);
	printf("indice de sortie = %d\n",indiceS);
	
	J[indiceS] = indiceE;
	
	pivot = A[indiceS][indiceE];
	printf("Le pivot = %lf\n",pivot);
	if(pivot != 1){
		for(j = 1;j<=n;j++){
			A[indiceS][j] /= pivot;
			
	}
		B[indiceS] /= pivot;	
		}
	
	// les combinaison linéaires des lignes avec la ligne du pivot
	 for(i = 1;i<=m;i++){
	 	if(i != indiceS){
	 		B[i] -= A[i][indiceE]*B[indiceS];
	 		for(j = 1;j<=n;j++){
	 			A[i][j] -= A[i][indiceS]*A[indiceS][j]; 
	 		}
	 		
		 }
	 }
	
	 cIndiceE = C[indiceE];	 	 
	 for(j = 1;j<=n;j++){
	 	C[j] = C[j] - cIndiceE*A[indiceS][j];
	 }
	 
	//mise à jour du max
	max -= maxC*B[indiceS];
	
	//detail des operations de chaque étape
	printf("\nla matrice A\n");
	afficherMatriceReelle(A,m,n);
	
	
	printf("\nla vecteur B\n");
	afficherTableauReel(B,m);
	printf("\nla vecteur C\n");
	afficherTableauReel(C,n);
	printf("\n-max = %lf",max);
	
	
	index++;
	} 
	}
	//afficher la solution
	printf("\n----------------------------------\n");	
	printf("\nSolution\n");
	printf("-Max = %lf\n",max);
	printf("la vecteur B\n");
	afficherTableauReel(B,m);
	printf("la vecteur J\n");
	for(i=1;i<=m;i++){
		printf("%d ",*(J+i));
	}
	printf("\n");	
	//fermer les fichier et libération de la mémoire			   	
   	fclose(pFichier); 
 	libererTableauReel(B);
 	libererTableauReel(C);
 	libererTableauReel(rapport);
 	
 	libererMatriceReelle(A,m);	
   	return 0;
 		
}
