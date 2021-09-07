// Copyright 2021 Alexander 'Lucifer' Orletskiy

/*
    Задача 2_2

    Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
    Требуется построить бинарное дерево, заданное наивным порядком вставки.
    Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
    то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
    Требования: Рекурсия запрещена. Решение должно поддерживать передачу
    функции сравнения снаружи.
    
    Выведите элементы в порядке pre-order (сверху вниз).
*/

#include <iostream>
#include <string>
#include <stack>

using std::cout;
using std::cin;
using std::endl;

template<typename T>
struct Compare {
    constexpr bool operator()(const T & left, const T & right) const {
        return left < right;
    }
};


template<typename T, typename Comparator>
struct Tree {
 private:
    struct TreeNode {
        T data;
        TreeNode *left;
        TreeNode *right;

        explicit TreeNode(const T & data) : data(data), left(nullptr), right(nullptr) {}
        ~TreeNode() { delete left; delete right; }
    };

 private:
    const Comparator cmp;

 public:
    explicit Tree(const Comparator & cmp = Compare<T>()) : cmp(cmp), root(nullptr) {}
    ~Tree() { delete root; }

    void Add(const T & data) {
        if (root == nullptr) {
            root = new TreeNode(data);
            return;
        }

        TreeNode *node = root;
        while (true) {
            if (!cmp(data, node->data)) {
                if (node->right == nullptr) {
                    node->right = new TreeNode(data);
                    return;
                }
                node = node->right;
            } else {
                if (node->left == nullptr) {
                    node->left = new TreeNode(data);
                    return;
                }
                node = node->left;
            }
        }
    }

    void Traverse() const {
        std::stack<TreeNode *> stack;
        TreeNode *node = root;
        for (;;) {
            Print(node);
            if (node->left != nullptr) {
                if (node->right != nullptr) stack.push(node->right);
                node = node->left;
            } else if (node->right != nullptr) {
                node = node->right;
            } else {
                if (!stack.size()) break;
                node = stack.top();
                stack.pop();
            }
        }
        cout << endl;
    }

 private:
    TreeNode *root;

    void Print(TreeNode *node) const {
        if (node != nullptr) {
            cout << node->data << " ";
        }
    }
};

int main() {
    size_t N = 0; cin >> N;

    Tree<int, Compare<int>> Tree;
    for (size_t i = 0; i < N; ++i) {
        int data = 0; cin >> data;
        Tree.Add(data);
    }
    Tree.Traverse();

    return 0;
}
