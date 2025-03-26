#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <sstream> // for std::ostringstream

template <typename K, typename V>
class Node {
private:
    K key;
    V value;
    int height;
    Node<K, V>* left;
    Node<K, V>* right;

public:
    Node(K key, V value);  // Constructor declaration

    Node<K, V>* next(K other);

    bool isLeaf() const;

    std::string toString() const;

    K getKey() const;
    V getValue() const;
    int getHeight() const;
    Node<K, V>* getLeft() const;
    Node<K, V>* getRight() const;

    void setKey(K key);
    void setValue(V value);
    void setHeight(int height);
    void setLeft(Node<K, V>* left);
    void setRight(Node<K, V>* right);
};

template <typename K, typename V>
Node<K, V>::Node(K key, V value) : key(key), value(value), height(1), left(nullptr), right(nullptr) {}

template <typename K, typename V>
Node<K, V>* Node<K, V>::next(K other) {
    return other < key ? left : right;
}

template <typename K, typename V>
bool Node<K, V>::isLeaf() const {
    return left == nullptr && right == nullptr;
}

template <typename K, typename V>
std::string Node<K, V>::toString() const {
    std::ostringstream oss;
    oss << key;
    return oss.str();
}

template <typename K, typename V>
K Node<K, V>::getKey() const {
    return key;
}

template <typename K, typename V>
V Node<K, V>::getValue() const {
    return value;
}

template <typename K, typename V>
int Node<K, V>::getHeight() const {
    return height;
}

template <typename K, typename V>
Node<K, V>* Node<K, V>::getLeft() const {
    return left;
}

template <typename K, typename V>
Node<K, V>* Node<K, V>::getRight() const {
    return right;
}

template <typename K, typename V>
void Node<K, V>::setKey(K key) {
    this->key = key;
}

template <typename K, typename V>
void Node<K, V>::setValue(V value) {
    this->value = value;
}

template <typename K, typename V>
void Node<K, V>::setHeight(int height) {
    this->height = height;
}

template <typename K, typename V>
void Node<K, V>::setLeft(Node<K, V>* left) {
    this->left = left;
}

template <typename K, typename V>
void Node<K, V>::setRight(Node<K, V>* right) {
    this->right = right;
}
#endif