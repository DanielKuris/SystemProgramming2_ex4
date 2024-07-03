#pragma once

#include <vector>
#include <memory>
#include <queue>
#include <stack>
#include <algorithm>
#include <iterator>

template <typename T>
class Tree {
private:
    struct Node {
        T value;
        std::vector<std::shared_ptr<Node>> children;
        Node(T val, int k) : value(val), children(k, nullptr) {}
    };

    std::shared_ptr<Node> root;
    int k;

    std::shared_ptr<Node> find(std::shared_ptr<Node> node, const T& value);

public:
    Tree(int k = 2) : k(k) {}

    void add_root(const T& value);
    void add_sub_node(const T& parent_value, const T& child_value);

    class PreOrderIterator;
    class PostOrderIterator;
    class InOrderIterator;
    class BFSIterator;
    class DFSIterator;
    class HeapIterator;

    PreOrderIterator begin_pre_order();
    PreOrderIterator end_pre_order();

    PostOrderIterator begin_post_order();
    PostOrderIterator end_post_order();

    InOrderIterator begin_in_order();
    InOrderIterator end_in_order();

    BFSIterator begin_bfs_scan();
    BFSIterator end_bfs_scan();

    DFSIterator begin_dfs_scan();
    DFSIterator end_dfs_scan();

    HeapIterator begin_heap();
    HeapIterator end_heap();

    void myHeap();

    ~Tree();
};

template <typename T>
class Tree<T>::PreOrderIterator : public std::iterator<std::input_iterator_tag, T> {
    std::stack<std::shared_ptr<Node>> stack;

public:
    PreOrderIterator(std::shared_ptr<Node> root);

    PreOrderIterator& operator++();

    bool operator!=(const PreOrderIterator& other) const;
    bool operator==(const PreOrderIterator& other) const;

    T& operator*();
};

template <typename T>
class Tree<T>::PostOrderIterator : public std::iterator<std::input_iterator_tag, T> {
    std::stack<std::shared_ptr<Node>> stack;
    std::shared_ptr<Node> last_visited = nullptr;

public:
    PostOrderIterator(std::shared_ptr<Node> root);

    PostOrderIterator& operator++();

    bool operator!=(const PostOrderIterator& other) const;
    bool operator==(const PostOrderIterator& other) const;

    T& operator*();
};

template <typename T>
class Tree<T>::InOrderIterator : public std::iterator<std::input_iterator_tag, T> {
    std::stack<std::shared_ptr<Node>> stack;
    std::shared_ptr<Node> current;

    void push_left(std::shared_ptr<Node> node);

public:
    InOrderIterator(std::shared_ptr<Node> root);

    InOrderIterator& operator++();

    bool operator!=(const InOrderIterator& other) const;
    bool operator==(const InOrderIterator& other) const;

    T& operator*();
};

template <typename T>
class Tree<T>::BFSIterator : public std::iterator<std::input_iterator_tag, T> {
    std::queue<std::shared_ptr<Node>> queue;

public:
    BFSIterator(std::shared_ptr<Node> root);

    BFSIterator& operator++();

    bool operator!=(const BFSIterator& other) const;
    bool operator==(const BFSIterator& other) const;

    T& operator*();
};

template <typename T>
class Tree<T>::DFSIterator : public std::iterator<std::input_iterator_tag, T> {
    std::stack<std::shared_ptr<Node>> stack;

public:
    DFSIterator(std::shared_ptr<Node> root);

    DFSIterator& operator++();

    bool operator!=(const DFSIterator& other) const;
    bool operator==(const DFSIterator& other) const;

    T& operator*();
};

template <typename T>
class Tree<T>::HeapIterator : public std::iterator<std::input_iterator_tag, T> {
    std::vector<T> heap;
    size_t current;

public:
    HeapIterator(std::vector<T> heap, size_t current);

    HeapIterator& operator++();

    bool operator!=(const HeapIterator& other) const;
    bool operator==(const HeapIterator& other) const;

    T& operator*();
};

#include "tree.cpp"
