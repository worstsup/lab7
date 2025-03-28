#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct.h"

int main() {
    long sz = 0;
    printf("Input array size: ");
    scanf("%li", &sz);
    School *x = genArray(sz);
    School *y = copyArray(x, sz);
    School *z = copyArray(x, sz); // 3 одинаковых массива для 3 сортировок
    // указатель на функцию сравнения (будет возвращать положительное, отрицательное или 0 в зависимости от отличия элементов и выбора возрастания/убывания)
    int (*compare)(const School*, const School*) = NULL; 
    // массив указателей на все функции сортировки
    void (*sort[])(School*, long, int (*compare)(const School*, const School*)) = {shaker_sort, merge_sort1, quick_sort};
    School *arrays[] = {x, y, z};
    const char *names[] = {"Shaker", "Merge", "Quick"};
    int choice;
    // printSchoolArray(x, sz, "Original Array");
    printf("Choose the sort:\n");
    printf("1 - In ascending order\n");
    printf("2 - In descending order\n");
    scanf("%d", &choice);
    switch(choice){
        case 1: 
            compare = compare_up_wrapper;
            break;
        case 2:
            compare = compare_down_wrapper;
            break;
        default: printf("Incorrect choice. Try again.\n");
    }
    for(int i = 0; i < 3; i++){
        checkSort(names[i], sort[i], arrays[i], sz, compare);
        // printSchoolArray(arrays[i], sz, names[i]);
    }
    free(x);
    free(y);
    free(z);
    return 0;
}