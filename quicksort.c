#include <stdio.h>
#include "quicksort.h"

void swap(unsigned int* a, unsigned int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(unsigned int arr[], unsigned int indexes[], int low, int high) {
    int pivot = arr[high];  
    int j,i = (low - 1);  
  
    for (j = low; j <= high - 1; j++) {
        if (arr[j] >= pivot) {
            i++;  
            swap(&arr[i], &arr[j]);
            swap(&indexes[i], &indexes[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    swap(&indexes[i + 1], &indexes[high]);
    return (i + 1);
}

void quickSort(unsigned int arr[], unsigned int indexes[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, indexes, low, high);
        quickSort(arr, indexes, low, pi - 1);
        quickSort(arr, indexes, pi + 1, high);
    }
}

void sortByIndex(unsigned int values[][NR_SUBJECTS], unsigned int indexes[]) {
    unsigned int temp[NR_SCORE][NR_SUBJECTS];
    unsigned int tempIndex, i, k ;
    for (i = 0; i < NR_SCORE; i++) {
            tempIndex = indexes[i];
            for (k = 0; k < NR_SUBJECTS; k++) {
                temp[i][k] = values[tempIndex][k];

            }
    }

    for (i = 0; i < NR_SCORE; i++) {
            for (k = 0; k < NR_SUBJECTS; k++) {
                values[i][k] = temp[i][k];

            }
    }

}

/* code for testing 
#define NR_SCORE 10
int main() {
    int scores[NR_SCORE] = {90, 78, 85, 92, 88, 70, 95, 82, 80, 75};
    int indexes[NR_SCORE];
    
    // Inizializza l'array degli indici
    for (int i = 0; i < NR_SCORE; i++) {
        indexes[i] = i;
    }
    
    // Ordina gli array dei punteggi e degli indici usando quicksort
    quickSort(scores, indexes, 0, NR_SCORE - 1);
    
    // Stampa gli indici ordinati
    printf("Indici ordinati (in ordine decrescente):\n");
    for (int i = 0; i < NR_SCORE; i++) {
        printf("%d ", indexes[i]);
    }
    printf("\n");

    // Stampa l'array ordinato
    printf("Valori ordinati (in ordine decrescente):\n");
    for (int i = 0; i < NR_SCORE; i++) {
        printf("%d ", scores[i]);
    }
    printf("\n");
    
    return 0;
}
*/


/*
#define NR_SCORE 5
int main() {
    int scores[NR_SCORE][NR_SUBJECTS] = {
        {90, 85, 78},
        {92, 88, 80},
        {70, 75, 72},
        {95, 90, 88},
        {82, 79, 84}
    };
    int indexes[NR_SCORE] = {4, 2, 0, 3, 1};
    
    // Ordina l'array dei punteggi in base agli indici
    sortByIndex(scores, indexes, NR_SCORE);
    
    // Stampa l'array dei punteggi e degli indici ordinati
    printf("Punteggi ordinati:\n");
    for (int i = 0; i < NR_SCORE; i++) {
        printf("[");
        for (int j = 0; j < NR_SUBJECTS; j++) {
            printf("%d ", scores[i][j]);
        }
        printf("]\n");
    }
    
    printf("Indici utilizzati per ordinare:\n");
    for (int i = 0; i < NR_SCORE; i++) {
        printf("%d ", indexes[i]);
    }
    printf("\n");
    
    return 0;
}
*/