#pragma once

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void interchange_sort(int* arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[i] > arr[j])
                swap(arr[i], arr[j]);
        }
    }
}

void quick_sort(int* arr, int left, int right) {
    int i = left;
    int j = right;
    int middle = arr[(left + right) / 2];

    do {
        while (arr[i] < middle && i < right) i++;
        while (arr[j] > middle && j > left) j--;

        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (left < j) quick_sort(arr, left, j);
    if (i < right) quick_sort(arr, i, right);
}

void radix_sort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; ++i)
        if (arr[i] > max) max = arr[i];

    for (int exp = 1; max / exp > 0; exp *= 10) {
        int* arr_temp = new int[n];
        int i, count[10] = { 0 };

        for (i = 0; i < n; i++) 
            count[(arr[i] / exp) % 10]++;

        for (i = 1; i < 10; i++) 
            count[i] += count[i - 1];

        for (i = n - 1; i >= 0; i--) {
            int temp = (arr[i] / exp) % 10;
            arr_temp[count[temp] - 1] = arr[i];
            count[temp]--;
        }

        for (i = 0; i < n; i++) arr[i] = arr_temp[i];
        delete[] arr_temp;
    }
}