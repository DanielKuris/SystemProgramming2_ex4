#include "tree.cpp"
#include <iostream>

class Complex {
public:
    int real, imag;
    
    Complex(int r, int i) : real(r), imag(i) {}

    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    bool operator<(const Complex& other) const {
        // Compare based on magnitude for min-heap
        return (real * real + imag * imag) < (other.real * other.real + other.imag * other.imag);
    }

    bool operator>(const Complex& other) const {
        // Compare based on magnitude for max-heap
        return (real * real + imag * imag) > (other.real * other.real + other.imag * other.imag);
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << "+" << c.imag << "i";
        return os;
    }
};

int main() {
    // Create a tree of Complex numbers
    Tree<Complex> tree;
    
    // Add nodes
    tree.add_root(Complex(1, 1));
    tree.add_sub_node(Complex(1, 1), Complex(2, 2));
    tree.add_sub_node(Complex(1, 1), Complex(3, 3));
    tree.add_sub_node(Complex(2, 2), Complex(4, 4));
    tree.add_sub_node(Complex(2, 2), Complex(5, 5));

    // Original tree traversal
    std::cout << "Original Tree:" << std::endl;
    
    std::cout << "Pre-Order Traversal: ";
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Post-Order Traversal: ";
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "In-Order Traversal: ";
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "BFS Traversal: ";
    for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "DFS Traversal: ";
    for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Convert the tree into a binary max heap
    tree.myHeap();
    
    // Heapified tree traversal
    std::cout << "Heapified Tree:" << std::endl;
    
    std::cout << "Pre-Order Traversal: ";
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Post-Order Traversal: ";
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "In-Order Traversal: ";
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "BFS Traversal: ";
    for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "DFS Traversal: ";
    for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}

