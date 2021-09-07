// Copyright 2021 Alexander 'Lucifer' Orletskiy

/*
    Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n.
    Требуется найти k-ю порядковую статистику, т.е. напечатать число, которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве. 

    Требования:
    К дополнительной памяти: O(n).
    Среднее время работы: O(n).
    Должна быть отдельно выделенная функция partition.
    Рекурсия запрещена.
    Решение должно поддерживать передачу функции сравнения снаружи.

    6_4. Реализуйте стратегию выбора опорного элемента “случайный элемент”.
    Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
*/

#include <iostream>
#include <random>
#include <ctime>

template <typename T, typename Comparator = std::less<T>>
size_t partition(T * arr, size_t l, size_t r, Comparator cmp = Comparator()) {
    static std::mt19937 gen(time(NULL));     // random generator
    size_t pivot_index = gen()%(r-l+1) + l;  // choosing random pivot
    const T pivot = arr[pivot_index];
    std::swap(arr[pivot_index], arr[l]);     // putting pivot to the left

    size_t i = r, j = r;  // starting 2 iterators end-to-start bypass
    while (l < j) {
        if (cmp(pivot, arr[j]) && (j > l)) {
            std::swap(arr[i], arr[j]);
            --i;
        }
        --j;
    }
    std::swap(arr[l], arr[i]);  // putting pivot to its position
    return i;
}

template <typename T, typename Comparator = std::less<T>>
T stat(T * arr, size_t k, size_t l, size_t r, Comparator cmp = Comparator()) {
    size_t pivot_index = partition(arr, l, r, cmp);
    while (pivot_index != k) {  // exec partition until pivot is on k'th place
        if (pivot_index < k) l = pivot_index + 1;
        else
            r = pivot_index - 1;
        pivot_index = partition(arr, l, r, cmp);
    }
    return arr[k];
}

using std::cin;
using std::cout;
using std::endl;

int main() {
    size_t n, k; cin >> n >> k;
    int * arr = new int[n];
    for (size_t i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    const int res = stat(arr, k, 0, n-1, std::less<int>());
    cout << res << endl;

    delete[] arr;

    return 0;
}
