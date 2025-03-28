#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct.h"
 
void generate_full_name(char* full_name) {
    const char* full_names[] = { "John Wick", "Mikhail Litvin",
    "Jack Daniels", "Emma Watson", "Mike Tyson", "Sarah Davis",
    "Tom Miller", "Lucy Wilson", "Sam Taylor", 
    "Grace Moore", "Ashab Tamaev", "Vitaliy Tsal", 
    "Kirill Pavlov", "Mell Stroy", "Ivan Zolo"};
    int index = rand() % 15;
    strcpy(full_name, full_names[index]);
}

void generate_quailification(char* qualification) {
    const char* qualifications[] = { "First", "Second", "High"};
    int index = rand() % 3;
    strcpy(qualification, qualifications[index]);
}

void generate_home_address(char* home_address) {
    const char* home_addresses[] = { "Litvinburg", "Bikini Bottom", "Mondstadt",
    "Springfield", "Cheboksary", "Kanash", "Pukovo",
    "Tsivilsk", "Odintsovo", "Orehovo-Zuevo"};
    int index = rand() % 10;
    strcpy(home_address, home_addresses[index]);
}

void generate_date_birth(char* date_birth) {
    int day = rand() % 28 + 1; // так-то несложно сюда добавить и проверку на февраль и високосный год, но было лень
    int month = rand() % 12 + 1;
    int year = 1980 + rand() % 15;
    sprintf(date_birth, "%02d.%02d.%d", day, month, year); // то же что и printf, но в массив
}

void generate_phone_number(char* phone_number) {
    phone_number[0] = '+';
    phone_number[1] = '7';
    for (int i = 2; i < 12; i++) {
        phone_number[i] = '0' + (rand() % 10);
    }
    phone_number[12] = '\0';
}

void generate_employment_date(char* employment_date) {
    int day = rand() % 28 + 1;
    int month = rand() % 12 + 1;
    int year = 2010 + rand() % 15;
    sprintf(employment_date, "%02d.%02d.%d", day, month, year);
}

School* genArray (long n) {
    srand(time(NULL));

    School* a = (School*)malloc(n * sizeof(School));
    if (!a) return NULL;
    for (int i = 0; i < n; i++) {
        generate_full_name(a[i].full_name);
        generate_quailification(a[i].qualification);
        generate_home_address(a[i].home_address);
        generate_date_birth(a[i].date_birth);
        generate_phone_number(a[i].phone_number);
        generate_employment_date(a[i].employment_date);
    }
    return a;
}

School* copyArray(School *a, long n) {
    School *x = (School*)malloc(n * sizeof(School));
    if (!x)
    return NULL;
    memcpy(x, a, n * sizeof(School));
    return x;
}

// по возрастанию
int compare_up(const void* p1, const void* p2){
    const School* x1 = (const School*)p1;
    const School* x2 = (const School*)p2;
    int cmp1 = strcmp(x1->full_name, x2->full_name);
    if (cmp1 != 0) {
        return cmp1;
    }
    int cmp2 = strcmp(x1->qualification, x2->qualification);
    if (cmp2 != 0) {
        return cmp2;
    }
    int cmp3 = strcmp(x1->home_address, x2->home_address);
    if (cmp3 != 0) {
        return cmp3;
    }
    int cmp4 = strcmp(x1->date_birth, x2->date_birth);
    if (cmp4 != 0) {
        return cmp4;
    }
    int cmp5 = strcmp(x1->phone_number, x2->phone_number);
    if (cmp5 != 0) {
        return cmp5;
    }
    int cmp6 = strcmp(x1->employment_date, x2->employment_date);
    if (cmp6 != 0) {
        return cmp6;
    }
    return x1->employment_date - x2->employment_date;
}
// по убыванию (инверсия возрастания)
int compare_down(const void* p1, const void* p2){
    const School* x1 = (const School*)p1;
    const School* x2 = (const School*)p2;
    int cmp1 = strcmp(x1->full_name, x2->full_name);
    if (cmp1 != 0) {
        return -cmp1;
    }
    int cmp2 = strcmp(x1->qualification, x2->qualification);
    if (cmp2 != 0) {
        return -cmp2;
    }
    int cmp3 = strcmp(x1->home_address, x2->home_address);
    if (cmp3 != 0) {
        return -cmp3;
    }
    int cmp4 = strcmp(x1->date_birth, x2->date_birth);
    if (cmp4 != 0) {
        return -cmp4;
    }
    int cmp5 = strcmp(x1->phone_number, x2->phone_number);
    if (cmp5 != 0) {
        return -cmp5;
    }
    int cmp6 = strcmp(x1->employment_date, x2->employment_date);
    if (cmp6 != 0) {
        return -cmp6;
    }
    return x2->employment_date - x1->employment_date;
}

// Функции-обёртки для приведения типов
int compare_up_wrapper(const School* a, const School* b) {
    return compare_up((const void*)a, (const void*)b);
}

int compare_down_wrapper(const School* a, const School* b) {
    return compare_down((const void*)a, (const void*)b);
}

void checkSort(const char *algName, void (*sort)(School*, long, int (*compare)(const School*, const School*)), School *a, long n, int (*compare)(const School*, const School*)) {
    clock_t t1 = clock(); // засекли старт
    sort(a, n, compare); // вызов переданной функции сортировки
    clock_t t2 = clock(); // засекли конец
    double sortTime = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("%s sort time for array of %li elements in seconds: %.6lf\n", algName, n, sortTime);
}

void shaker_sort(School* a, long n, int (*compare)(const School*, const School*)) {
    long left = 0;
    long right = n - 1;
    School tmp;

    do {

        // Проход справа налево (движение "вверх")
        for (long j = right; j > left; j--) {
            if (compare(&a[j - 1], &a[j]) > 0) {
                tmp = a[j - 1];
                a[j - 1] = a[j];
                a[j] = tmp;
            }
        }
        left++;

        // Проход слева направо (движение "вниз")
        for (long j = left; j < right; j++) {
            if (compare(&a[j], &a[j + 1]) > 0) {
                tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
        right--;

    } while (left <= right);
}
void merge(School* a, long low, long mid, long high, int (*compare)(const School*, const School*)) {
    School* b = (School*)malloc((high + 1 - low) * sizeof(School));
    long h, i, j, k;
    h = low;
    i = 0;
    j = mid + 1;
    while ((h <= mid) && (j <= high)) {
        if (compare(&a[h], &a[j]) <= 0) {
            b[i] = a[h];
            h++;
        }
        else {
            b[i] = a[j];
            j++;
        }
        i++;
    }
    if (h > mid) { // если все элементы из левой части уже расставлены
        for (k = j; k <= high; k++) {
            b[i] = a[k];
            i++;
        }
    }
    else { // если все элементы из правой части уже расставлены
        for (k = h; k <= mid; k++) {
            b[i] = a[k];
            i++;
        }
    }
    // копируем обратно из временного массива в исходный, временный сносим
    for (k = 0; k <= high - low; k++) {
        a[k + low] = b[k];
    }
    free(b);
}

School* merge_sort(School* a, long low, long high, int (*compare)(const School*, const School*)) {
    long mid;
    if (low < high) {
        mid = (low + high) / 2;
        merge_sort(a, low, mid, compare);
        merge_sort(a, mid + 1, high, compare);
        merge(a, low, mid, high, compare);
    }
    return a;
}

// по сути, это костыль для нормального вызова функции merge_sort, т.к. в ней требуется 4 элемента, а не 3, как у всех остальных сортировок
void merge_sort1(School* a, long n, int (*compare)(const School*, const School*)) {
    merge_sort(a, 0, n - 1, compare);
}

void qSort(School* a, int first, int last, int (*compare)(const School*, const School*)) {
    if (first < last) {
        int left = first, right = last;
        int middle_index = left + (right - left) / 2;
        School* middle = &a[middle_index]; // Указатель на опорный элемент
        do {
            while (compare(&a[left], middle) < 0) left++;
            while (compare(&a[right], middle) > 0) right--;
            if (left <= right) {
                School tmp = a[left];
                a[left] = a[right];
                a[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);

        qSort(a, first, right, compare);
        qSort(a, left, last, compare);
    }
}

void quick_sort(School* a, long n, int (*compare)(const School*, const School*)) {
    qSort(a, 0, n-1, compare);
}

void printSchoolArray(const School* arr, long n, const char* title) {
    printf("\n=== %s ===\n", title);
    for (int i = 0; i < n; i++) {
        printf("Element %d:\n", i + 1);
        printf("  Name: %s\n", arr[i].full_name);
        printf("  Qualification: %s\n", arr[i].qualification);
        printf("  Address: %s\n", arr[i].home_address);
        printf("  Birth Date: %s\n", arr[i].date_birth);
        printf("  Phone: %s\n", arr[i].phone_number);
        printf("  Employment: %s\n", arr[i].employment_date);
        printf("----------------------------\n");
    }
    printf("\n");
}