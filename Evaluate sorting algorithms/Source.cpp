#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <string>

#include <iostream>
#include "utils.cpp"

using namespace std;

void generate_numbers(int n, int start_num, int end_num, int choice, const char* file_name, const char* file_mode) {
    FILE* f = fopen(file_name, file_mode);

    if (choice == 1) {
        for (int i = 1; i <= n; ++i) fprintf(f, "%d\n", i);
        cout << "\nNum range with N = " << n << " and Ascending type has been written to " << file_name;
    } else if (choice == 2) {
        for (int i = n; i >= 1; --i) fprintf(f, "%d\n", i);
        cout << "\nNum range with N = " << n << " and Descending type has been written to " << file_name;
    } else if (choice == 3) {
        srand(time(0));
        for (int i = 1; i <= n; ++i) {
            int x = start_num + rand() % (end_num - start_num + 1);
            fprintf(f, "%d\n", x);
        }
        cout << "\nNum range with N = " << n << " and Randomize type has been written to " << file_name;
    }
    fclose(f);
}

bool read_from_file(const char* file_name, const char* file_mode, int*& arr, int n) {
    FILE* f = fopen(file_name, file_mode);

    if (f != NULL) {
        arr = new int[n];
        for (int i = 0; i < n; ++i) fscanf(f, "%d", &arr[i]);
        fclose(f);
        return true;
    }

    cout << "Cannot found " << file_name;
    return false;
}

void export_sorted_file(int* arr, int n, const char* file_name, const char* file_mode) {
    FILE* f = fopen(file_name, file_mode);
    for (int i = 0; i < n; ++i)
        fprintf(f, "%d\n", arr[i]);
    fclose(f);
}

int main() {
    FILE* f = fopen("Results\\Radix Sort.txt", "w");
    fprintf(f, "\t\t\tRadix Sort");
    fprintf(f, "\nN\tAscending\tDescending\tRandomize\tAverage");

    for (int n = 1000; n <= 21000; n += 2000) {
        fprintf(f, "\n%d\t", n);

        char buffer[6];
        _itoa(n, buffer, 10);

        char* s1 = new char[6];
        s1 = (char*)buffer;

        char* s2 = new char[6];
        s2 = (char*)".txt";

        int len1 = strlen(s1);
        int len2 = strlen(s2);
        int total_length = len1 + len2 + 1;

        // create s3 with sufficient length and character '\ 0'
        char* file_name = new char[total_length];
        strcpy(file_name, s1);

        // move the s3 pointer backward to make strcat run faster
        char* s3 = file_name + len1;
        strcat(s3, s2);

        double total_time = 0;
        for (int i = 1; i <= 3; ++i) {
            // Generate data and write to file
            // generate_numbers(n, -1000, 1000, i, file_name, "w"); 
            // => Found that Radix Sort cannot handle negative
            generate_numbers(n, 0, 1000, i, file_name, "w");

            int* arr;
            bool file_existed = read_from_file(file_name, "r", arr, n);

            if (file_existed) {
                clock_t start = clock();
                radix_sort(arr, n);
                clock_t end = clock();

                double execute_time = double(end) - double(start);  // / CLOCKS_PER_SEC;
                total_time += execute_time;

                fprintf(f, "%.4lf ms\t", execute_time);
                cout << "\nWith N = " << n << " => Radix Sort runs " << i << " times - Costs: " << (size_t)execute_time << " ms";

                export_sorted_file(arr, n, file_name, "w");
                delete[] arr;
            }
        }

        fprintf(f, "%.4lf ms", total_time / 3);
        cout << endl;
    }

    cout << "\nAlgorithm runtime result has been written to file\n";
    fclose(f);

    system("pause");
    return 0;
}