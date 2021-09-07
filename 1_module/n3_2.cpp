// Copyright 2021 Alexander 'Lucifer' Orletskiy

/*
    3_2. Реализовать дек с динамическим зацикленным буфером

    Формат входных данных:
    В первой строке количество команд n. n ≤ 1000000
    Каждая команда задаётся как 2 целых числа: a b
    a = 1 - push front
    a = 2 - pop front
    a = 3 - push back
    a = 4 - pop back
    Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b
    Если дана команда pop, то число b - ожидаемое значение
    Если команда pop вызвана для пустой структуры данных, то ожидается “-1”

    Формат выходных данных:
    Требуется напечатать YES - если все ожидаемые значения совпали
    Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO
*/

#include <iostream>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;

template <typename T>
class Deque {
 public:
    Deque(): buf(new T[4]), head(0), tail(0), capacity(4) {}
    ~Deque() {
        delete[] buf;
    }

    T pop_back();   // return && delete element to the end of the deque
    T pop_front();  // return && delete element to the start of the deque

    void push_back(const T val);   // add element to the end of the deque
    void push_front(const T val);  // add element to the start of the deque

    bool is_empty() const {  // check if there are elements in the deque
        return tail == head;
    }
    bool is_full() const {   // check if the deque is full
        return (tail+1 == head) || (tail+1 == capacity && head == 0);
    }

 private:
    T * buf;
    int head;
    int tail;
    size_t capacity;

    void mem_inc();  // 2 times increase size of the deque
};

template <typename T>
void Deque<T>::mem_inc() {
    auto * new_buf = new T[capacity*2];

    if (head > tail) {
        memcpy(new_buf+head, buf+head, (capacity-head)*sizeof(T));
        memcpy(new_buf+capacity, buf, tail*sizeof(T));
        tail += capacity;
    } else {
        memcpy(new_buf, buf, (tail-head)*sizeof(T));
    }

    delete[] buf;
    buf = new_buf;
    capacity *= 2;
}

template <typename T>
void Deque<T>::push_back(const T val) {
    if (is_full()) {
        mem_inc();
    }

    buf[tail++] = val;
    tail %= capacity;
}

template <typename T>
void Deque<T>::push_front(const T val) {
    if (is_full()) {
        mem_inc();
    }

    if (is_empty()) {
        buf[head] = val;
        ++tail;
        tail %= capacity;
    } else {
        if (head == 0) {
            head = capacity;
        }
        buf[--head] = val;
        head %= capacity;
    }
}

template <typename T>
T Deque<T>::pop_back() {
    if (is_empty()) {
        return -1;
    }
    if (tail == 0) {
        tail = capacity;
    }

    --tail;
    tail %= capacity;

    return buf[tail];
}

template <typename T>
T Deque<T>::pop_front() {
    if (is_empty()) {
        return -1;
    }

    int head_val = buf[head];
    head = (head+1) % capacity;

    return head_val;
}

int main() {
    Deque<int> xDeque;

    int n, operation, value;
    bool result = true;
    cin >> n;

    for (auto i = 0; i < n; ++i) {
        cin >> operation >> value;
        switch (operation) {
            case 1:
                xDeque.push_front(value);
                break;
            case 2:
                if (xDeque.is_empty() && value != -1) result = false;
                else if (value != xDeque.pop_front()) result = false;
                break;
            case 3:
                xDeque.push_back(value);
                break;
            case 4:
                if (xDeque.is_empty() && value != -1) result = false;
                else if (value != xDeque.pop_back()) result = false;
                break;
            default:
                break;
        }
    }

    cout << (result ? "YES" : "NO") << endl;

    return 0;
}
