// Copyright 2021 Alexander 'Lucifer' Orletskiy

/* 
 2_2. Дан массив целых чисел А[0..n-1].
 Известно, что на интервале [0, m] значения массива строго возрастают, а на интервале [m, n-1] строго убывают.
 Найти m за O(log m).
 Требования:  Время работы O(log m).
 Внимание! В этой задаче сначала нужно определить диапазон для бинарного поиска размером порядка m с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.
*/

#include <iostream>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::min;

void input(int * A, const size_t & n);
int exp_search(const int * A, const size_t & n);
int bin_search(const int * A, size_t l, size_t r);

int main() {
    size_t n; cin >> n;
    int * A = new int[n]();

    input(A, n);

    cout << exp_search(A, n) << endl;

    delete[] A;
    return 0;
}

void input(int * A, const size_t & n) {
    for (size_t i = 0; i < n; ++i) {
        cin >> A[i];
    }
}

int exp_search(const int * A, const size_t & n) {
    if (A[0] > A[1]) {
        return 0;
    }

    size_t i = 1;
    while ((i < n) && (A[i-1] < A[i])) {
        i *= 2;
    }
    return bin_search(A, i/2, min(i, n-1));
}


int bin_search(const int * A, size_t l, size_t r) {
    while (l <= r) {
        size_t m = l + (r-l)/2;
        if ((m==r) || ((A[m] > A[m-1]) && (A[m] > A[m+1]))) {
            return m;
        }

        if (A[m] > A[m+1]) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return -1;
}
