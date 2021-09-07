// Copyright 2021 Alexander 'Lucifer' Orletskiy

/*
    Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы
    с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.

    Хеш-функция строки должна быть реализована с помощью вычисления
    значения многочлена методом Горнера.

    Начальный размер таблицы должен быть равным 8-ми.
    Перехеширование выполняйте при добавлении элементов в случае,
    когда коэффициент заполнения таблицы достигает 3/4.

    Структура данных должна поддерживать операции добавления строки в множество,
    удаления строки из множества и проверки принадлежности данной строки множеству.

    1_2. Для разрешения коллизий используйте двойное хеширование.
*/

#include <iostream>
#include <string>
#include <vector>

#define DEFAULT_SIZE 8
#define DEFAULT_ALPHA 0.75
#define HASH1 11
#define HASH2 13

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::vector;
using std::endl;

template<class T>
int hash1(const T& keys_array, int size) {
    int hash = 0;
    for (int i = keys_array.size(); i >= 0; i--) {
        hash += (HASH1 * hash + keys_array[i]) % size;
    }
    return hash % size;
}

template<class T>
int hash2(const T& keys_array, int size) {
    int hash = 0;
    for (int i = keys_array.size(); i >= 0; i--) {
        hash += (HASH2 * hash + keys_array[i]) % size;
    }
    return (hash * 2 + 1) % size;
}

template<class T>
class Hash_table_node {
 public:
    explicit Hash_table_node(const T& value) : key(value), is_deleted(false) {}

    const T& get_key() const {
        return key;
    }

    void set_key(const T& key_value) {
        key = key_value;
    }

    bool if_is_deleted() const {
        return is_deleted;
    }

    void set_deleted() {
        is_deleted = true;
    }

    void set_not_deleted() {
        is_deleted = false;
    }

 private:
    T key;
    bool is_deleted;
};

template<class T>
class Hash_table {
 public:
    Hash_table() : buffer(DEFAULT_SIZE, NULL), buffer_size(DEFAULT_SIZE), size(0) {}

    ~Hash_table() {
        for (int i = 0; i < buffer.size(); i++) {
            delete buffer[i];
        }
    }

    bool add(const T& key_value) {
        if (((double)size / (double)buffer_size) >= DEFAULT_ALPHA) {  // check if we need rehash
            rehash();
        }
        int h1 = hash1(key_value, buffer_size), h2 = hash2(key_value, buffer_size), i = 0, first_deleted_elem = -1;

        while (buffer[h1] != NULL && i < buffer_size) {
            if (buffer[h1]->get_key() == key_value && !buffer[h1]->if_is_deleted()) {  // if key in table
                return false;
            }
            if (buffer[h1]->if_is_deleted() && first_deleted_elem < 0) {
                first_deleted_elem = h1;
            }
            h1 = (h1 + h2) % buffer_size;
            i++;
        }

        if (first_deleted_elem < 0) {  // enter new key
            buffer[h1] = new Hash_table_node<T>(key_value);
        } else {  // paste to the place of first deleted elem
            buffer[first_deleted_elem]->set_key(key_value);
            buffer[first_deleted_elem]->set_not_deleted();
        }
        size++;
        return true;
    }

    bool remove(const T& key_value) {
        int h1 = hash1(key_value, buffer_size), h2 = hash2(key_value, buffer_size), i = 0;
        while (buffer[h1] != NULL && i < buffer_size) {
            if (buffer[h1]->get_key() == key_value && !buffer[h1]->if_is_deleted()) {  // if elem was found
                buffer[h1]->set_deleted();
                size--;
                return true;
            }
            h1 = (h1 + h2) % buffer_size;
            i++;
        }
        return false;  // if not found
    }

    bool has(const T& key_value) const {
        int h1 = hash1(key_value, buffer_size), h2 = hash2(key_value, buffer_size), i = 0;
        while (buffer[h1] != NULL && i < buffer_size) {
            if (buffer[h1]->get_key() == key_value && !buffer[h1]->if_is_deleted()) {  // if elem was found
                return true;
            }
            h1 = (h1 + h2) % buffer_size;
            i++;
        }
        return false;  // if not found
    }

 private:
    vector<Hash_table_node<T>*> buffer;
    int buffer_size;
    int size;  // real number of elems in table

    void rehash() {
        int new_buffer_size = buffer_size * 2;
        vector<Hash_table_node<T>*> new_buffer(new_buffer_size, NULL);
        for (int i = 0; i < buffer_size; i++) {
            if (buffer[i] != NULL && !buffer[i]->if_is_deleted()) {  // if elem in old version of table
                int h1 = hash1(buffer[i]->get_key(), new_buffer_size), h2 = hash2(buffer[i]->get_key(), new_buffer_size), k = 0;
                while (new_buffer[h1] != NULL && k < new_buffer_size) {  // searching for free space in new version table
                    h1 = (h1 + h2) % new_buffer_size;
                    k++;
                }
                new_buffer[h1] = buffer[i];
            } else {  // if no elem
                delete buffer[i];
            }
            buffer[i] = NULL;
        }
        buffer = new_buffer;
        buffer_size = new_buffer_size;
    }
};

int main() {
    Hash_table<string> hashTable;
    char cmd = 0;
    string key("");
    bool status = false;

    while (cin >> cmd >> key) {
        switch (cmd) {
            case '+':
                status = hashTable.add(key);
                break;
            case '?':
                status = hashTable.has(key);
                break;
            case '-':
                status = hashTable.remove(key);
                break;
            default:
                continue;
        }

        if (status) {
            cout << "OK" << endl;
        } else {
            cout << "FAIL" << endl;
        }
    }

    return 0;
}
