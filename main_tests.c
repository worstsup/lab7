#include <stdio.h>
#include <stdlib.h>

int main() {
    const long sizes[] = {100, 1000, 10000, 50000, 100000, 200000, 300000};
    const int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    FILE* data_file = fopen("sorting_data.csv", "w");
    if (!data_file) {
        perror("Failed to open file");
        return 1;
    }

    // CSV
    fprintf(data_file, "Size,Shaker,Merge,Quick\n");

    for (int i = 0; i < num_sizes; i++) {
        long sz = sizes[i];
        printf("\nTesting size: %ld\n", sz);

        School* original = genArray(sz);
        if (!original) {
            printf("Failed to generate array of size %ld\n", sz);
            continue;
        }

        // для хранения времени сортировки
        double times[3] = {0};

        for (int algo = 0; algo < 3; algo++) {
            School* arr = copyArray(original, sz);
            if (!arr) {
                printf("Failed to copy array for algo %d\n", algo);
                continue;
            }

            // Выбираем функцию сортировки
            void (*sort_func)(School*, long, int (*)(const School*, const School*)) = NULL;
            switch (algo) {
                case 0: sort_func = shaker_sort; break;
                case 1: sort_func = merge_sort1; break;
                case 2: sort_func = quick_sort; break;
            }

            // Замер времени
            clock_t start = clock();
            sort_func(arr, sz, compare_up_wrapper);
            clock_t end = clock();
            times[algo] = (double)(end - start) / CLOCKS_PER_SEC;

            free(arr);
        }

        // Запись данных в CSV
        fprintf(data_file, "%ld,%.6f,%.6f,%.6f\n", sz, times[0], times[1], times[2]);
        free(original);
    }

    fclose(data_file);
    printf("\nData saved to sorting_data.csv\n");

    // Запуск gnuplot для построения графиков
    system("gnuplot plot_sorting.gnuplot");

    return 0;
}