// Copyright 2021 Alexander 'Lucifer' Orletskiy

/*
    4_1. Солдаты. В одной военной части решили построить в одну шеренгу по росту.
    Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя,
    а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги.
    Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены
    по росту – сначала самые высокие, а в конце – самые низкие.
    За расстановку солдат отвечал прапорщик, который заметил интересную
    особенность – все солдаты в части разного роста.
    Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат,
    а именно для каждого приходящего солдата указывать,
    перед каким солдатом в строе он должен становится. 

    Требования: скорость выполнения команды - O(log n).
*/

#include <iostream>
#include <memory>   // easier but not such effective

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

template<typename T>
struct Compare {
    constexpr bool operator()(const T & left, const T & right) const {
        return less(left, right);
    }
 private:
    constexpr bool less(const T & left, const T & right) const {
        return left < right;
    }
};

template<typename T, typename Comparator = Compare<T>()>
class AVLTree {
 private:
    const Comparator cmp;
    struct Node {
        explicit Node(const T & data) : data(data), height(1), nodes(1), left(nullptr), right(nullptr) {}
        
        size_t CalculateHeight() {
            height = 1 + std::max(((left != nullptr) ? left->height : 0), ((right != nullptr) ? right->height : 0));
            return height;
        }

        size_t CalculateNodes() {
            nodes = 1 + ((left != nullptr) ? left->nodes : 0) + ((right != nullptr) ? right->nodes : 0);
            return nodes;
        }

        short CalculateBalance() const {
            return -((left != nullptr) ? left->height : 0) + ((right != nullptr) ? right->height : 0);
        }

        T data;
        size_t height;
        size_t nodes;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
    };

 public:
    explicit AVLTree(const Comparator cmp = Compare<T>()) : cmp(cmp), root(nullptr) {}

    size_t Add(const T & key) {
        size_t index = 0;
        root = InsertInternal(root, key, index);

        return index;
    }

    void DeleteByIndex(const size_t index) {
        std::shared_ptr<Node> node = GetNodeByIndex(root, index);

        if (node != nullptr) {
            root = DeleteInternal(root, node->data);
        }
    }

 private:
    std::shared_ptr<Node> InsertInternal(std::shared_ptr<Node> node, const T & key, size_t & index) {
        if (node == nullptr) {
            return std::make_shared<Node>(key);
        }

        if (cmp(node->data, key)) {
            node->right = InsertInternal(node->right, key, index);
        } else {
            index += 1;
            if (node->right != nullptr) {
                index += node->right->nodes;
            }

            node->left = InsertInternal(node->left, key, index);
        }

        return Balance(node);
    }

    std::shared_ptr<Node> DeleteInternal(std::shared_ptr<Node> node, const T & key) {
        if (node == nullptr) {
            return nullptr;
        }

        if (cmp(node->data, key)) {
            node->right = DeleteInternal(node->right, key);
        } else if (cmp(key, node->data)) {
            node->left  = DeleteInternal(node->left,  key);
        } else {
            std::shared_ptr<Node> left  = node->left;
            std::shared_ptr<Node> right = node->right;

            if (right == nullptr) {
                return left;
            }

            std::shared_ptr<Node> min;
            min->right = FindAndRemoveMin(right, min);
            min->left = left;

            return Balance(min);
        }

        return Balance(node);
    }

    std::shared_ptr<Node> FindAndRemoveMin(std::shared_ptr<Node> node, std::shared_ptr<Node> & min) {   // reference!
        if (node->left == nullptr) {
            min = node; return node->right;
        }
        node->left = FindAndRemoveMin(node->left, min);

        return Balance(node);
    }

    std::shared_ptr<Node> GetNodeByIndex(std::shared_ptr<Node> node, size_t index) const {
        if (index >= node->nodes) {
            return nullptr;
        }

        while (node != nullptr) {
            const size_t right_index = (node->right != nullptr) ? node->right->nodes : 0;
            if (index == right_index) {
                return node;
            }

            if (index > right_index) {
                node = node->left;
                index = index - right_index - 1;
            } else {
                node = node->right;
            }
        }

        return nullptr;
    }

    std::shared_ptr<Node> Balance(std::shared_ptr<Node> node) {
        if (node != nullptr) {
            node->CalculateHeight(); node->CalculateNodes();
        }

        const short balance = (node != nullptr) ? node->CalculateBalance() : 0;

        if (balance < 0) {
            const short left_balance = (node->left != nullptr) ? node->left->CalculateBalance() : 0;
            if (left_balance > 0) {
                node->left  = LRotate(node->left);
            }
            return RRotate(node);
        }

        if (balance > 0) {
            const short right_balance = (node->right != nullptr) ? node->right->CalculateBalance() : 0;
            if (right_balance < 0) {
                node->right = RRotate(node->right);
            }
            return LRotate(node);
        }
        return node;
    }

    std::shared_ptr<Node> LRotate(std::shared_ptr<Node> node) {
        std::shared_ptr<Node> temp;
        temp = node->right;
        node->right = temp->left;
        temp->left = node;

        if (node != nullptr) {
            node->CalculateHeight();
            node->CalculateNodes();
        }

        if (temp != nullptr) {
            temp->CalculateHeight(); temp->CalculateNodes();
        }
        return temp;
    }

    std::shared_ptr<Node> RRotate(std::shared_ptr<Node> node) {
        std::shared_ptr<Node> temp;
        temp = node->left;
        node->left = temp->right;
        temp->right = node;

        if (node != nullptr) {
            node->CalculateHeight(); node->CalculateNodes();
        }

        if (temp != nullptr) {
            temp->CalculateHeight(); temp->CalculateNodes();
        }
        return temp;
    }

 private:
    std::shared_ptr<Node> root;
};


int main() {
    AVLTree<int, Compare<int>> Tree;

    size_t N = 0;
    cin >> N;

    for (size_t i = 0; i < N; ++i) {
        size_t cmd = 0; cin >> cmd;
        size_t value = 0; cin >> value;

        switch (cmd) {
        case 1:
            cout << Tree.Add(value) << endl;
            break;
        case 2:
            Tree.DeleteByIndex(value);
            break;
        default:
            cerr << "WRONG COMMAND " << cmd << endl;
        }
    }

    return 0;
}
