#include "BinarySearchTree.h"
#include <iostream>
#include <string>

int main() {
    // Create a BinarySearchTree
    BinarySearchTree<int, std::string> bst;

    // Insert some nodes
    bst.insert(8, "apple");
    bst.insert(4, "banana");
    bst.insert(6, "cherry");
    bst.insert(2, "date");
    bst.insert(18, "elderberry");
    bst.insert(12, "fig");
    bst.insert(20, "grape");    
    bst.insert(10, "mamao");


    // Test search
    std::cout << "Search for key 3: " << bst.search(3) << std::endl; // Expected: banana
    std::cout << "Search for key 6: " << bst.search(6) << std::endl; // Expected: fig
    std::cout << "Search for key 9: " << bst.search(9) << std::endl; // Expected: "" (or an empty string, depending on your implementation)

    // Test toString()
    //std::cout << "Tree contents:\n" << bst.toString() << std::endl;

    // Test preOrder traversal
    std::cout << "PreOrder traversal: ";
    bst.preOrder();

    // Test inOrder traversal
    std::cout << "InOrder traversal: ";
    bst.inOrder();

    // Test postOrder traversal
    std::cout << "PostOrder traversal: ";
    bst.postOrder();

    // Test levelOrder traversal
    std::cout << "LevelOrder traversal: ";
    bst.levelOrder();

    // Test deleteNode
    //bst.deleteNode(3);
    //std::cout << "Tree after deleting key 3:\n" << bst.toString() << std::endl;

    // Test deleteByMerging
    bst.deleteByCopying(18);
    //std::cout << "Tree after deleteByCopying key 6:\n" << bst.toString() << std::endl;

    // Test isEmpty()
    std::cout << "Is the tree empty? " << (bst.isEmpty() ? "Yes" : "No") << std::endl;

    // Test clear()
    bst.clear();
    //std::cout << "Tree after clear():\n" << bst.toString() << std::endl;
    std::cout << "Is the tree empty? " << (bst.isEmpty() ? "Yes" : "No") << std::endl;

    return 0;
}