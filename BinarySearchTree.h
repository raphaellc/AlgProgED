#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "Node.h"
#include "BinarySearchTreeADT.h"
#include <iostream>
#include <string>

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

    void preOrder() const override;
    void inOrder() const override;
    void postOrder() const override;
    void levelOrder() const override;

    std::string toString() const override;  // Added toString() declaration

private:
    V search(Node<K, V>* node, const K& key) const;
    Node<K, V>* insert(Node<K, V>* node, const K& key, const V& value);
    std::string printTree(std::ostringstream& sb) const;
    void printTree(Node<K, V>* node, bool isRight, std::ostringstream& sb, const std::string& indent) const;
    bool deleteByCopying(const K& key);

    void preOrder(Node<K, V>* node) const;
    void inOrder(Node<K, V>* node) const;
    void postOrder(Node<K, V>* node) const;
    void levelOrder(Node<K, V>* node) const;
};

#endif