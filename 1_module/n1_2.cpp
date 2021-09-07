// Copyright 2021 Alexander 'Lucifer' Orletskiy

/*
    1_2. Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин.
    Вначале вводится количество вершин, затем последовательно целочисленные координаты всех вершин в порядке обхода по/против часовой стрелки.
    n < 1000, координаты < 10000.
    Указание. Для вычисления площади n-угольника можно посчитать сумму ориентированных площадей трапеций под каждой стороной многоугольника.
    Требования: Координата должна быть реализована в виде структуры.
*/

#include <iostream>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;

struct point {
    int x;
    int y;
    point(int x_, int y_) : x(x_), y(y_) {}
    point() : point(0, 0) {}
    static double len(point, point);
};

double square(size_t n, const point * points);
double tr_square(point a_p, point b_p, point c_p);
void input(point * points, const size_t n);

int main() {
    size_t n; cin >> n;
    point * points = new point[n];
    input(points, n);
    cout << square(n, points) << endl;

    delete[] points;
    return 0;
}

void input(point * points, const size_t n) {
    for (size_t i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }
}

double point::len(point a, point b) {
    return sqrt(pow(a.x-b.x, 2) + pow(a.y-b.y, 2));
}

double tr_square(point a_p, point b_p, point c_p) {  // s = sqrt(p*(p-a)*(p-b)*(p-c))
    double a = point::len(a_p, b_p), b = point::len(b_p, c_p), c = point::len(c_p, a_p);
    double p = (a + b + c)/2.0;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}

double square(size_t n, const point * points) {
    double s = 0;
    for (size_t i = 1; i < n-1; ++i) {
        s += tr_square(points[0], points[i], points[i+1]);
    }
    return s;
}
