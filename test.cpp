#include "tree.hpp"
#include <gtest/gtest.h>

// Define tests for Tree class
class TreeTests : public ::testing::Test {
protected:
    Tree<int> tree;

    void SetUp() override {
        // Set up the tree with initial nodes for testing
        tree.add_root(1);
        tree.add_sub_node(1, 2);
        tree.add_sub_node(1, 3);
        tree.add_sub_node(2, 4);
        tree.add_sub_node(2, 5);
    }
};

// Test adding nodes and traversal
TEST_F(TreeTests, AddNodeAndTraversalTest) {
    // Test pre-order traversal
    std::vector<int> expected_pre_order = {1, 2, 4, 5, 3};
    std::vector<int> actual_pre_order;
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        actual_pre_order.push_back(*it);
    }
    ASSERT_EQ(actual_pre_order, expected_pre_order);

    // Test post-order traversal
    std::vector<int> expected_post_order = {4, 5, 2, 3, 1};
    std::vector<int> actual_post_order;
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        actual_post_order.push_back(*it);
    }
    ASSERT_EQ(actual_post_order, expected_post_order);

    // Test in-order traversal
    std::vector<int> expected_in_order = {4, 2, 5, 1, 3};
    std::vector<int> actual_in_order;
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
        actual_in_order.push_back(*it);
    }
    ASSERT_EQ(actual_in_order, expected_in_order);

    // Test BFS traversal
    std::vector<int> expected_bfs = {1, 2, 3, 4, 5};
    std::vector<int> actual_bfs;
    for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
        actual_bfs.push_back(*it);
    }
    ASSERT_EQ(actual_bfs, expected_bfs);

    // Test DFS traversal
    std::vector<int> expected_dfs = {1, 3, 2, 5, 4};
    std::vector<int> actual_dfs;
    for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
        actual_dfs.push_back(*it);
    }
    ASSERT_EQ(actual_dfs, expected_dfs);
}

// Test heap conversion
TEST_F(TreeTests, HeapConversionTest) {
    tree.myHeap();
    // Assert statements to verify the tree is now a valid binary min heap
    ASSERT_EQ(*tree.begin_pre_order(), 1);
    ASSERT_EQ(*tree.begin_bfs_scan(), 1);
    // Add more assertions as needed
}

// Test with empty tree
TEST_F(TreeTests, EmptyTreeTest) {
    Tree<int> empty_tree;
    ASSERT_EQ(empty_tree.begin_pre_order(), empty_tree.end_pre_order());
    ASSERT_EQ(empty_tree.begin_post_order(), empty_tree.end_post_order());
    ASSERT_EQ(empty_tree.begin_in_order(), empty_tree.end_in_order());
    ASSERT_EQ(empty_tree.begin_bfs_scan(), empty_tree.end_bfs_scan());
    ASSERT_EQ(empty_tree.begin_dfs_scan(), empty_tree.end_dfs_scan());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
