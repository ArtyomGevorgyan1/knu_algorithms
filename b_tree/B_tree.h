//
// Created by artyom on 17.03.19.
//

#ifndef B_TREE_B_TREE_H
#define B_TREE_B_TREE_H

#define num_limit long long

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;
using std::vector;

class Book {
public:
    Book() = default;

    explicit Book(int key) : m_key(key) {}

    int getKey() {
        return m_key;
    }

private:
    int m_key;
};

template <typename T>
struct Node {
    explicit Node(T init) : data(init), m_is_leaf(false), m_ancestors_count(0)
    {
        m_ancestors.resize(0);
    };

    T data;
    shared_ptr<Node<T>> m_parent, m_left, m_right;
    vector <shared_ptr<Node<T>>> m_ancestors;
    vector <num_limit> m_keys;
    int m_ancestors_count;
    bool m_is_leaf;
};

template <typename T>
class B_tree {
public:

    //----constructors
    explicit B_tree(int balance_factor) : m_root(nullptr), m_counter(0), m_balance_factor(balance_factor)
    {
        m_root = m_root = make_shared<Node<T>>;
        create_empty();
    }

    explicit B_tree(shared_ptr <Node<T>> root, int balance_factor) : m_root(root), m_counter(0),
                                                                     m_balance_factor(balance_factor)
    {
        m_root = make_shared<Node<T>>;
        create_empty();
    }

    //--- access operations

    shared_ptr<Node <T>> search(T item) {

        shared_ptr <Node <T>> ret = find_leaf(m_root, item);
        for (auto i : ret -> m_ancestors) {
            if (i -> data.getKey() == item.getKey()) {
                return i;
            }
        }
        return nullptr;
    }



    bool insert(shared_ptr<Node <T>> item_node) {
        shared_ptr <Node<T>> leaf = find_key(item_node);
        if (item_node -> m_is_leaf) {
            return false;
        }

    }

    // modification operations

private:
    shared_ptr <Node<T>> m_root;
    int m_counter;
    int m_balance_factor;

    // --- b-tree specific helping operations
    void create_empty() {
        m_root -> m_is_leaf = true;
        m_root -> m_ancestors_count = 0;
        m_root -> m_keys.resize(0);
        m_root -> m_ancestors.resize(0);
        m_root -> m_parent = nullptr;
        m_root -> m_left = nullptr;
        m_root -> m_right = nullptr;
    }

    shared_ptr <Node <T>> find_leaf(shared_ptr <Node <T>> source, T item) {
        shared_ptr <Node <T>> cur = m_root;
        while (!(cur -> m_is_leaf)) {
            for (int i = 0; i <= cur -> m_ancestors_count; i++) {
                if (i == cur -> m_ancestors_count || item -> getKey() < cur -> m_keys[i]) {
                    cur = cur -> m_ancestors[i];
                    break;
                }
            }
        }
        return  cur;
    }
};

#endif //B_TREE_B_TREE_H