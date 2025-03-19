#ifndef BINARYSEARCHTREEADT_H
#define BINARYSEARCHTREEADT_H

template <typename K, typename V>
class BinarySearchTreeADT {
public:
    virtual ~BinarySearchTreeADT() = 0;

    virtual void clear() = 0;

    virtual bool isEmpty() const = 0;

    virtual V search(const K& key) const = 0;

    virtual void insert(const K& key, const V& value) = 0;

    virtual bool deleteNode(const K& key) = 0;

    virtual void preOrder() const = 0;

    virtual void inOrder() const = 0;

    virtual void postOrder() const = 0;

    virtual void levelOrder() const = 0;
};

template <typename K, typename V>
BinarySearchTreeADT<K, V>::~BinarySearchTreeADT() {} // Provide an empty implementation
                                                    // for the pure virtual destructor
#endif
