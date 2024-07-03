
#include <vector>
#include <memory>
#include <queue>
#include <stack>
#include <algorithm>
#include <iterator>
#include <functional> // for std::greater
#include <stdexcept> // for std::out_of_range

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

// Iterator implementations

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

// Template class function implementations

template <typename T>
void Tree<T>::add_root(const T& value) {
    root = std::make_shared<Node>(value, k);
}

template <typename T>
void Tree<T>::add_sub_node(const T& parent_value, const T& child_value) {
    auto parent = find(root, parent_value);
    if (parent) {
        for (auto& child : parent->children) {
            if (!child) {
                child = std::make_shared<Node>(child_value, k);
                return;
            }
        }
        throw std::out_of_range("Max children exceeded");
    }
}

template <typename T>
std::shared_ptr<typename Tree<T>::Node> Tree<T>::find(std::shared_ptr<Node> node, const T& value) {
    if (!node) return nullptr;
    if (node->value == value) return node;
    for (const auto& child : node->children) {
        auto found = find(child, value);
        if (found) return found;
    }
    return nullptr;
}

template <typename T>
typename Tree<T>::PreOrderIterator Tree<T>::begin_pre_order() { return PreOrderIterator(root); }

template <typename T>
typename Tree<T>::PreOrderIterator Tree<T>::end_pre_order() { return PreOrderIterator(nullptr); }

template <typename T>
typename Tree<T>::PostOrderIterator Tree<T>::begin_post_order() { return PostOrderIterator(root); }

template <typename T>
typename Tree<T>::PostOrderIterator Tree<T>::end_post_order() { return PostOrderIterator(nullptr); }

template <typename T>
typename Tree<T>::InOrderIterator Tree<T>::begin_in_order() { return InOrderIterator(root); }

template <typename T>
typename Tree<T>::InOrderIterator Tree<T>::end_in_order() { return InOrderIterator(nullptr); }

template <typename T>
typename Tree<T>::BFSIterator Tree<T>::begin_bfs_scan() { return BFSIterator(root); }

template <typename T>
typename Tree<T>::BFSIterator Tree<T>::end_bfs_scan() { return BFSIterator(nullptr); }

template <typename T>
typename Tree<T>::DFSIterator Tree<T>::begin_dfs_scan() { return DFSIterator(root); }

template <typename T>
typename Tree<T>::DFSIterator Tree<T>::end_dfs_scan() { return DFSIterator(nullptr); }

template <typename T>
typename Tree<T>::HeapIterator Tree<T>::begin_heap() {
    myHeap(); // Ensure the tree is converted to a heap before iterating
    std::vector<T> elements;
    for (auto it = begin_pre_order(); it != end_pre_order(); ++it) {
        elements.push_back(*it);
    }
    return HeapIterator(elements, 0);
}

template <typename T>
typename Tree<T>::HeapIterator Tree<T>::end_heap() {
    return HeapIterator({}, 0);
}

template <typename T>
void Tree<T>::myHeap() {
    std::vector<T> values;
    for (auto it = begin_in_order(); it != end_in_order(); ++it) {
        values.push_back(*it);
    }
    std::make_heap(values.begin(), values.end(), std::greater<T>());
    int i = 0;
    for (auto it = begin_in_order(); it != end_in_order(); ++it) {
        *it = values[i];
        ++i;
    }
}

template <typename T>
Tree<T>::~Tree() {
    std::stack<std::shared_ptr<Node>> stack;
    if (root) {
        stack.push(root);
    }
    while (!stack.empty()) {
        auto node = stack.top();
        stack.pop();
        for (auto& child : node->children) {
            if (child) {
                stack.push(child);
            }
        }
    }
    root.reset();
}

// Iterator method implementations

template <typename T>
Tree<T>::PreOrderIterator::PreOrderIterator(std::shared_ptr<Node> root) {
    if (root) stack.push(root);
}

template <typename T>
typename Tree<T>::PreOrderIterator& Tree<T>::PreOrderIterator::operator++() {
    if (!stack.empty()) {
        auto node = stack.top();
        stack.pop();
        for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
            if (*it) stack.push(*it);
        }
    }
    return *this;
}

template <typename T>
bool Tree<T>::PreOrderIterator::operator!=(const PreOrderIterator& other) const {
    return !(*this == other);
}

template <typename T>
bool Tree<T>::PreOrderIterator::operator==(const PreOrderIterator& other) const {
    if (stack.empty() && other.stack.empty()) return true;
    if (stack.empty() || other.stack.empty()) return false;
    return stack.top() == other.stack.top();
}

template <typename T>
T& Tree<T>::PreOrderIterator::operator*() {
    return stack.top()->value;
}

template <typename T>
Tree<T>::PostOrderIterator::PostOrderIterator(std::shared_ptr<Node> root) {
    if (root) stack.push(root);
}

template <typename T>
typename Tree<T>::PostOrderIterator& Tree<T>::PostOrderIterator::operator++() {
    while (!stack.empty()) {
        auto curr = stack.top();
        bool no_children = true;
        for (auto& child : curr->children) {
            if (child && last_visited != child) {
                no_children = false;
                stack.push(child);
            }
        }
        if (no_children) {
            last_visited = curr;
            stack.pop();
            return *this;
        }
    }
    return *this;
}

template <typename T>
bool Tree<T>::PostOrderIterator::operator!=(const PostOrderIterator& other) const {
    return !(*this == other);
}

template <typename T>
bool Tree<T>::PostOrderIterator::operator==(const PostOrderIterator& other) const {
    if (stack.empty() && other.stack.empty()) return true;
    if (stack.empty() || other.stack.empty()) return false;
    return stack.top() == other.stack.top();
}

template <typename T>
T& Tree<T>::PostOrderIterator::operator*() {
    return stack.top()->value;
}

template <typename T>
void Tree<T>::InOrderIterator::push_left(std::shared_ptr<Node> node) {
    while (node) {
        stack.push(node);
        node = node->children.empty() ? nullptr : node->children[0];
    }
}

template <typename T>
Tree<T>::InOrderIterator::InOrderIterator(std::shared_ptr<Node> root) : current(root) {
    push_left(root);
}

template <typename T>
typename Tree<T>::InOrderIterator& Tree<T>::InOrderIterator::operator++() {
    if (stack.empty()) return *this;

    auto node = stack.top();
    stack.pop();
    if (!node->children.empty() && node->children.size() > 1) {
        push_left(node->children[1]);
    }
    current = stack.empty() ? nullptr : stack.top();
    return *this;
}

template <typename T>
bool Tree<T>::InOrderIterator::operator!=(const InOrderIterator& other) const {
    return current != other.current;
}

template <typename T>
bool Tree<T>::InOrderIterator::operator==(const InOrderIterator& other) const {
    return current == other.current;
}

template <typename T>
T& Tree<T>::InOrderIterator::operator*() {
    return stack.top()->value;
}

template <typename T>
Tree<T>::BFSIterator::BFSIterator(std::shared_ptr<Node> root) {
    if (root) queue.push(root);
}

template <typename T>
typename Tree<T>::BFSIterator& Tree<T>::BFSIterator::operator++() {
    if (!queue.empty()) {
        auto node = queue.front();
        queue.pop();
        for (auto& child : node->children) {
            if (child) queue.push(child);
        }
    }
    return *this;
}

template <typename T>
bool Tree<T>::BFSIterator::operator!=(const BFSIterator& other) const {
    return !(*this == other);
}

template <typename T>
bool Tree<T>::BFSIterator::operator==(const BFSIterator& other) const {
    if (queue.empty() && other.queue.empty()) return true;
    if (queue.empty() || other.queue.empty()) return false;
    return queue.front() == other.queue.front();
}

template <typename T>
T& Tree<T>::BFSIterator::operator*() {
    return queue.front()->value;
}

template <typename T>
Tree<T>::DFSIterator::DFSIterator(std::shared_ptr<Node> root) {
    if (root) stack.push(root);
}

template <typename T>
typename Tree<T>::DFSIterator& Tree<T>::DFSIterator::operator++() {
    if (!stack.empty()) {
        auto node = stack.top();
        stack.pop();
        for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
            if (*it) stack.push(*it);
        }
    }
    return *this;
}

template <typename T>
bool Tree<T>::DFSIterator::operator!=(const DFSIterator& other) const {
    return !(*this == other);
}

template <typename T>
bool Tree<T>::DFSIterator::operator==(const DFSIterator& other) const {
    if (stack.empty() && other.stack.empty()) return true;
    if (stack.empty() || other.stack.empty()) return false;
    return stack.top() == other.stack.top();
}

template <typename T>
T& Tree<T>::DFSIterator::operator*() {
    return stack.top()->value;
}

template <typename T>
Tree<T>::HeapIterator::HeapIterator(std::vector<T> heap, size_t current) : heap(heap), current(current) {}

template <typename T>
typename Tree<T>::HeapIterator& Tree<T>::HeapIterator::operator++() {
    ++current;
    return *this;
}

template <typename T>
bool Tree<T>::HeapIterator::operator!=(const HeapIterator& other) const {
    return current != other.current;
}

template <typename T>
bool Tree<T>::HeapIterator::operator==(const HeapIterator& other) const {
    return current == other.current;
}

template <typename T>
T& Tree<T>::HeapIterator::operator*() {
    return heap[current];
}

// Explicit instantiation for necessary types
template class Tree<int>;
