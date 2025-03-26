#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "Node.h"
#include "BinarySearchTreeADT.h"
#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <queue>

template <typename K, typename V>
class BinarySearchTree : public BinarySearchTreeADT<K, V> {
protected:
    Node<K, V>* root;

public:
    BinarySearchTree();
    virtual ~BinarySearchTree() override;

    void clear() override;
    bool isEmpty() const override;
    V search(const K& key) const override;
    void insert(const K& key, const V& value) override;
    bool deleteNode(const K& key) override;
    bool deleteByMerging(const K& key);
    bool deleteByCopying(const K& key);
    void preOrder() const override;
    void inOrder() const override;
    void postOrder() const override;
    void levelOrder() const override;

    //std::string toString() const override;  // Added toString() declaration

private:
    V search(Node<K, V>* node, const K& key) const;
    Node<K, V>* insert(Node<K, V>* node, const K& key, const V& value);
    std::string printTree(std::ostringstream& sb) const;
    void printTree(Node<K, V>* node, bool isRight, std::ostringstream& sb, const std::string& indent) const;
    void preOrder(Node<K, V>* node) const;
    void inOrder(Node<K, V>* node) const;
    void postOrder(Node<K, V>* node) const;
    void levelOrder(Node<K, V>* node) const;
};

template <typename K, typename V>
BinarySearchTree<K, V>::BinarySearchTree() : root(nullptr) {
    
}

template <typename K, typename V>
BinarySearchTree<K, V>::~BinarySearchTree()  {
    clear();
}

template <typename K, typename V>
void BinarySearchTree<K, V>::clear() {
    std::function<void(Node<K, V>*)> clearNodes = [&](Node<K, V>* node) {
        if (node) {
            clearNodes(node->getLeft());
            clearNodes(node->getRight());
            delete node;
        }
    };
    clearNodes(root);
    root = nullptr;
}

template <typename K, typename V>
bool BinarySearchTree<K, V>::isEmpty() const {
    return root == nullptr;
}

template <typename K, typename V>
V BinarySearchTree<K, V>::search(const K& key) const {
    return search(root, key);
}

template <typename K, typename V>
V BinarySearchTree<K, V>::search(Node<K, V>* node, const K& key) const {
    if (node == nullptr) {
        return V();
    } else if (key == node->getKey()) {
        return node->getValue();
    }
    return search(node->next(key), key);
}

template <typename K, typename V>
void BinarySearchTree<K, V>::insert(const K& key, const V& value) {
    root = insert(root, key, value);
}

template <typename K, typename V>
Node<K, V>* BinarySearchTree<K, V>::insert(Node<K, V>* node, const K& key, const V& value) {
    if (node == nullptr) {
        return new Node<K, V>(key, value);
    } else if (key > node->getKey()) {
        node->setRight(insert(node->getRight(), key, value));
    } else if (key < node->getKey()) {
        node->setLeft(insert(node->getLeft(), key, value));
    }
    return node;
}

/*template <typename K, typename V>
std::string BinarySearchTree<K, V>::toString() const {
    if (root == nullptr) {
        return "[empty]";
    } else {
        std::ostringstream sb;
        printTree(sb);
        return sb.str();
    }
}
*/
template <typename K, typename V>
std::string BinarySearchTree<K, V>::printTree(std::ostringstream& sb) const {
    if (root->getRight() != nullptr) {
        printTree(root->getRight(), true, sb, "");
    }
    sb << root->toString() << "\n";
    if (root->getLeft() != nullptr) {
        printTree(root->getLeft(), false, sb, "");
    }
    return sb.str();
}

template <typename K, typename V>
void BinarySearchTree<K, V>::printTree(Node<K, V>* node, bool isRight, std::ostringstream& sb, const std::string& indent) const {
    if (node->getRight() != nullptr) {
        printTree(node->getRight(), true, sb, indent + (isRight ? " " : " | "));
    }
    sb << indent << (isRight ? " /" : " \\") << "-----" << node->toString() << "\n";
    if (node->getLeft() != nullptr) {
        printTree(node->getLeft(), false, sb, indent + (isRight ? " | " : " "));
    }
}

template <typename K, typename V>
bool BinarySearchTree<K, V>::deleteNode(const K& key) {
    return deleteByCopying(key);
}

template <typename K, typename V>
bool BinarySearchTree<K, V>::deleteByCopying(const K& key) {
    std::cout << "deleteByCopying(" << key << ")" << std::endl; // Print function call

    Node<K, V>* parent = nullptr;
    Node<K, V>* current = root;
    std::cout << "chave do root: " << root->getKey() << std::endl;
    std::cout << "key: " << key << std::endl;
    std::cout << "current: " << current->getKey() << std::endl;
    std::cout << "parent: " << parent << std::endl;
    
    for (; current != nullptr && key != current->getKey(); parent = current, current = current->next(key));

    if (current == nullptr) {
        std::cout << "retorno deleteByCopying(" << key << ") - not found" << std::endl;
        return false;
    } else if (current->getLeft() != nullptr && current->getRight() != nullptr) {
        // Caso 3
        Node<K, V>* tmp = current->getLeft();
        while (tmp->getRight() != nullptr) tmp = tmp->getRight();
        deleteByCopying(tmp->getKey());
        current->setKey(tmp->getKey());
        current->setValue(tmp->getValue());
    } else {
        // Caso 1 ou Caso 2
        Node<K, V>* nextNode = current->getRight() == nullptr ? current->getLeft() : current->getRight();
        if (current == root) root = nextNode;
        else if (parent->getLeft() == current) parent->setLeft(nextNode);
        else parent->setRight(nextNode);
    }
    std::cout << "retorno deleteByCopying(" << key << ")" << std::endl;
    return true;
}
template <typename K, typename V>
bool BinarySearchTree<K, V>::deleteByMerging(const K& key) {
    Node<K, V>* parent = nullptr;
    Node<K, V>* current = root;

    for (; current != nullptr && key != current->getKey(); parent = current, current = current->next(key));

    if (current == nullptr) {
        return false;
    } else if (current->getLeft() != nullptr && current->getRight() != nullptr) {
        // Caso 3
        Node<K, V>* tmp = current->getLeft();
        while (tmp->getRight() != nullptr) {
            tmp = tmp->getRight();
        }
        tmp->setRight(current->getRight()); // tmp->right = current->right;

        if (current == root) {
            root = current->getLeft(); // root = current->left;
        } else if (parent->getLeft() == current) {
            parent->setLeft(current->getLeft()); // parent->left = current->left;
        } else {
            parent->setRight(current->getLeft()); // parent->right = current->left;
        }
    } else {
        // Caso 1 ou Caso 2
        Node<K, V>* nextNode = (current->getRight() == nullptr) ? current->getLeft() : current->getRight();
        if (current == root) {
            root = nextNode;
        } else if (parent->getLeft() == current) {
            parent->setLeft(nextNode);
        } else {
            parent->setRight(nextNode);
        }
    }
    delete current; // Important: Deallocate the node
    return true;
}

template <typename K, typename V>
void BinarySearchTree<K, V>::preOrder() const {
    preOrder(root);
    std::cout << std::endl; // Add newline for better formatting
}

template <typename K, typename V>
void BinarySearchTree<K, V>::inOrder() const {
    inOrder(root);
    std::cout << std::endl; // Add newline for better formatting
}

template <typename K, typename V>
void BinarySearchTree<K, V>::postOrder() const {
    postOrder(root);
    std::cout << std::endl; // Add newline for better formatting
}

template <typename K, typename V>
void BinarySearchTree<K, V>::levelOrder() const {
    if (root == nullptr) return;

    std::queue<Node<K, V>*> q;
    q.push(root);

    while (!q.empty()) {
        Node<K, V>* current = q.front();
        q.pop();

        std::cout << current->getKey() << " "; // Or current->toString() if you prefer

        if (current->getLeft() != nullptr) q.push(current->getLeft());
        if (current->getRight() != nullptr) q.push(current->getRight());
    }
    std::cout << std::endl; // Add newline for better formatting
}

template <typename K, typename V>
void BinarySearchTree<K, V>::preOrder(Node<K, V>* node) const {
    if (node) {
        std::cout << node->getKey() << " "; // Or node->toString()
        preOrder(node->getLeft());
        preOrder(node->getRight());
    }
}

template <typename K, typename V>
void BinarySearchTree<K, V>::inOrder(Node<K, V>* node) const {
    if (node) {
        inOrder(node->getLeft());
        std::cout << node->getKey() << " "; // Or node->toString()
        inOrder(node->getRight());
    }
}

template <typename K, typename V>
void BinarySearchTree<K, V>::postOrder(Node<K, V>* node) const {
    if (node) {
        postOrder(node->getLeft());
        postOrder(node->getRight());
        std::cout << node->getKey() << " "; // Or node->toString()
    }
}
#endif
