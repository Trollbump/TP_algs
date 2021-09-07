// Copyright 2021 Alexander 'Lucifer' Orletskiy

/*
 Вовочка ест фрукты из бабушкиной корзины. В корзине лежат фрукты разной массы.
 Вовочка может поднять не более K грамм. Каждый фрукт весит не более K грамм.
 За раз он выбирает несколько самых тяжелых фруктов, которые может поднять одновременно,
 откусывает от каждого половину и кладет огрызки обратно в корзину.
 Если фрукт весит нечетное число грамм, он откусывает большую половину.
 Фрукт массы 1гр он съедает полностью.
 Определить за сколько подходов Вовочка съест все фрукты в корзине.

 Формат входных данных.
 Вначале вводится n - количество фруктов и n строк с массами фруктов.
 Затем K - "грузоподъемность".
 */

#include <iostream>

template <typename T>
class Less {
 public:
     bool operator() (const T & l, const T & r) {
         return l < r;
     }
};

template <typename T, typename Comparator = std::less<T>>
class MaxHeap {
 public:
     MaxHeap() = delete;
     MaxHeap(const MaxHeap &) = delete;
     MaxHeap(T * arr_, size_t arr_size_, Comparator cmp_ = Comparator()) : size(arr_size_), cmp(cmp_) {
         arr = new T[size];
         std::copy(arr_, arr_ + arr_size_, arr);
         for (int i = size/2 -1; i >= 0; --i) {
             SiftDown(i);
         }
     }

     ~MaxHeap() {
         delete[] arr;
     }

     void InsertHeap(T data) {
         arr[size++] = data;
         SiftUp(size - 1);
     }

     T ExtractMax() {
         if (size > 0) {
             T temp = arr[0];
             arr[0] = arr[size-1];
             --size;
             if (size)
                 SiftDown(0);

             return temp;
         }

         throw;
     }

     T Peek() {
         return arr[0];
     }

     size_t Size() {
         return size;
     }

 private:
     T * arr;
     size_t size;
     Comparator cmp;

     size_t Parent(const size_t index) {
         return (index-1)/2;
     }

     size_t LeftChild(const size_t index) {
         return 1 + index*2;
     }

     size_t RightChild(const size_t index) {
         return 2 + index*2;
     }

     void SiftUp(size_t index) {
         while (index > 0) {
             size_t parent = Parent(index);

             if (arr[index] <= arr[parent]) return;

             std::swap(arr[index], arr[parent]);
             index = parent;
         }
     }

     void SiftDown(const size_t index) {
         size_t left = LeftChild(index), right = RightChild(index), max_index = index;

         if ((left < size) && !cmp(arr[left], arr[max_index])) {
             max_index = left;
         }

         if ((right < size) && !cmp(arr[right], arr[max_index])) {
             max_index = right;
         }

         if (max_index != index) {
             std::swap(arr[index], arr[max_index]);
             SiftDown(max_index);
         }
     }
};

int main() {
    size_t n = 0; std::cin >> n;

    int * temp = new int[n];
    for (size_t i = 0; i < n; ++i)
        std::cin >> temp[i];
    MaxHeap<int, Less<int>> Heap(temp, n);
    delete[] temp;

    size_t k = 0; std::cin >> k;

    int res = 0;

    int * bite = new int[k];

    while (Heap.Size()) {
        ++res;

        size_t bite_i = 0, sum = 0;

        for (size_t i = Heap.Size(); i > 0; --i) {
            if (Heap.Peek() > (k-sum))
                break;
            bite[bite_i++] = Heap.ExtractMax();
            sum += bite[bite_i-1];
        }

        for ( ; bite_i > 0; --bite_i) {
            if (bite[bite_i-1] > 1) {
                Heap.InsertHeap((int)(bite[bite_i-1]/2));
            }
        }
    }
    res += Heap.Size()/k;
    if (Heap.Size()%k != 0) ++res;

    std::cout << res << "\n";

    delete[] bite;

    return 0;
}
