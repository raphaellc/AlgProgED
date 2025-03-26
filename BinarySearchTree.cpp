#include "BinarySearchTree.h"
#include <sstream>
#include <functional>

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
