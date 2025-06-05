#pragma once
#include "Node.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>

template <typename T>
class BinaryTree {
private:
    Node<T>* root;

    void clear(Node<T>* node);
    Node<T>* copy(Node<T>* node) const;
    void NLR(Node<T>* node, std::ostream& os) const;
    void NRL(Node<T>* node, std::ostream& os) const;
    void LNR(Node<T>* node, std::ostream& os) const;
    void LRN(Node<T>* node, std::ostream& os) const;
    void RNL(Node<T>* node, std::ostream& os) const;
    void RLN(Node<T>* node, std::ostream& os) const;
    template <typename U>
    Node<U>* mapNode(Node<T>* node, std::function<U(const T&)> func) const;
    Node<T>* whereNode(Node<T>* node, std::function<bool(const T&)> pred) const;
    void mergeNodes(BinaryTree<T>& result, Node<T>* node) const;
    Node<T>* findNode(Node<T>* node, const T& value) const;
    bool isSubtree(Node<T>* main, Node<T>* sub) const;
    bool isSameTree(Node<T>* a, Node<T>* b) const;
    void toString(Node<T>* node, std::stringstream& ss) const;
    Node<T>* fromString(std::istream& is);

public:
    BinaryTree();
    BinaryTree(const BinaryTree& other);
    ~BinaryTree();
    void insert(const T& value);
    bool isEmpty() const;
    void preOrder(std::ostream& os = std::cout) const;
    void reversePreOrder(std::ostream& os = std::cout) const;
    void inOrder(std::ostream& os = std::cout) const;
    void postOrder(std::ostream& os = std::cout) const;
    void rightNodeLeft(std::ostream& os = std::cout) const;
    void rightLeftNode(std::ostream& os = std::cout) const;
    template <typename U>
    BinaryTree<U> map(std::function<U(const T&)> func) const;
    BinaryTree<T> where(std::function<bool(const T&)> pred) const;
    BinaryTree<T> merge(const BinaryTree<T>& other) const;
    BinaryTree<T> getSubtree(const T& value) const;
    bool contains(const T& value) const;
    bool containsSubtree(const BinaryTree<T>& sub) const;
    std::string serialize() const;
    void deserialize(const std::string& data);
    T findByPath(const std::string& path) const;
};

template <typename T>
void BinaryTree<T>::clear(Node<T>* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

template <typename T>
Node<T>* BinaryTree<T>::copy(Node<T>* node) const {
    if (!node) return nullptr;
    Node<T>* newNode = new Node<T>(node->data);
    newNode->left = copy(node->left);
    newNode->right = copy(node->right);
    return newNode;
}

template <typename T>
void BinaryTree<T>::NLR(Node<T>* node, std::ostream& os) const {
    if (!node) return;
    os << node->data << " ";
    NLR(node->left, os);
    NLR(node->right, os);
}

template <typename T>
void BinaryTree<T>::NRL(Node<T>* node, std::ostream& os) const {
    if (!node) return;
    os << node->data << " ";
    NRL(node->right, os);
    NRL(node->left, os);
}

template <typename T>
void BinaryTree<T>::LNR(Node<T>* node, std::ostream& os) const {
    if (!node) return;
    LNR(node->left, os);
    os << node->data << " ";
    LNR(node->right, os);
}

template <typename T>
void BinaryTree<T>::LRN(Node<T>* node, std::ostream& os) const {
    if (!node) return;
    LRN(node->left, os);
    LRN(node->right, os);
    os << node->data << " ";
}

template <typename T>
void BinaryTree<T>::RNL(Node<T>* node, std::ostream& os) const {
    if (!node) return;
    RNL(node->right, os);
    os << node->data << " ";
    RNL(node->left, os);
}

template <typename T>
void BinaryTree<T>::RLN(Node<T>* node, std::ostream& os) const {
    if (!node) return;
    RLN(node->right, os);
    RLN(node->left, os);
    os << node->data << " ";
}

template <typename T>
template <typename U>
Node<U>* BinaryTree<T>::mapNode(Node<T>* node, std::function<U(const T&)> func) const {
    if (!node) return nullptr;
    Node<U>* newNode = new Node<U>(func(node->data));
    newNode->left = mapNode(node->left, func);
    newNode->right = mapNode(node->right, func);
    return newNode;
}

template <typename T>
Node<T>* BinaryTree<T>::whereNode(Node<T>* node, std::function<bool(const T&)> pred) const {
    if (!node) return nullptr;
    if (!pred(node->data)) return nullptr;
    Node<T>* newNode = new Node<T>(node->data);
    newNode->left = whereNode(node->left, pred);
    newNode->right = whereNode(node->right, pred);
    return newNode;
}

template <typename T>
void BinaryTree<T>::mergeNodes(BinaryTree<T>& result, Node<T>* node) const {
    if (!node) return;
    result.insert(node->data);
    mergeNodes(result, node->left);
    mergeNodes(result, node->right);
}

template <typename T>
Node<T>* BinaryTree<T>::findNode(Node<T>* node, const T& value) const {
    if (!node) return nullptr;
    if (node->data == value) return node;
    Node<T>* leftResult = findNode(node->left, value);
    if (leftResult) return leftResult;
    return findNode(node->right, value);
}

template <typename T>
bool BinaryTree<T>::isSubtree(Node<T>* main, Node<T>* sub) const {
    if (!sub) return true;
    if (!main) return false;
    if (isSameTree(main, sub)) return true;
    return isSubtree(main->left, sub) || isSubtree(main->right, sub);
}

template <typename T>
bool BinaryTree<T>::isSameTree(Node<T>* a, Node<T>* b) const {
    if (!a && !b) return true;
    if (!a || !b) return false;
    return a->data == b->data && isSameTree(a->left, b->left) && isSameTree(a->right, b->right);
}

template <typename T>
void BinaryTree<T>::toString(Node<T>* node, std::stringstream& ss) const {
    if (!node) {
        ss << "# ";
        return;
    }
    ss << node->data << " ";
    toString(node->left, ss);
    toString(node->right, ss);
}

template <typename T>
Node<T>* BinaryTree<T>::fromString(std::istream& is) {
    std::string token;
    is >> token;
    if (token == "#") return nullptr;
    std::stringstream ss(token);
    T value;
    ss >> value;
    Node<T>* node = new Node<T>(value);
    node->left = fromString(is);
    node->right = fromString(is);
    return node;
}

template <typename T>
BinaryTree<T>::BinaryTree() : root(nullptr) {}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& other) : root(copy(other.root)) {}

template <typename T>
BinaryTree<T>::~BinaryTree() {
    clear(root);
}

template <typename T>
void BinaryTree<T>::insert(const T& value) {
    if (!root) {
        root = new Node<T>(value);
        return;
    }
    Node<T>* current = root;
    while (true) {
        if (value < current->data) {
            if (!current->left) {
                current->left = new Node<T>(value);
                break;
            }
            current = current->left;
        } else {
            if (!current->right) {
                current->right = new Node<T>(value);
                break;
            }
            current = current->right;
        }
    }
}

template <typename T>
bool BinaryTree<T>::isEmpty() const {
    return root == nullptr;
}

template <typename T>
void BinaryTree<T>::preOrder(std::ostream& os) const {
    NLR(root, os);
}

template <typename T>
void BinaryTree<T>::reversePreOrder(std::ostream& os) const {
    NRL(root, os);
}

template <typename T>
void BinaryTree<T>::inOrder(std::ostream& os) const {
    LNR(root, os);
}

template <typename T>
void BinaryTree<T>::postOrder(std::ostream& os) const {
    LRN(root, os);
}

template <typename T>
void BinaryTree<T>::rightNodeLeft(std::ostream& os) const {
    RNL(root, os);
}

template <typename T>
void BinaryTree<T>::rightLeftNode(std::ostream& os) const {
    RLN(root, os);
}

template <typename T>
template <typename U>
BinaryTree<U> BinaryTree<T>::map(std::function<U(const T&)> func) const {
    BinaryTree<U> result;
    result.root = mapNode(root, func);
    return result;
}

template <typename T>
BinaryTree<T> BinaryTree<T>::where(std::function<bool(const T&)> pred) const {
    BinaryTree<T> result;
    result.root = whereNode(root, pred);
    return result;
}

template <typename T>
BinaryTree<T> BinaryTree<T>::merge(const BinaryTree<T>& other) const {
    BinaryTree<T> result(*this);
    mergeNodes(result, other.root);
    return result;
}

template <typename T>
BinaryTree<T> BinaryTree<T>::getSubtree(const T& value) const {
    Node<T>* node = findNode(root, value);
    if (!node) throw std::runtime_error("Element not found");
    BinaryTree<T> result;
    result.root = copy(node);
    return result;
}

template <typename T>
bool BinaryTree<T>::contains(const T& value) const {
    return findNode(root, value) != nullptr;
}

template <typename T>
bool BinaryTree<T>::containsSubtree(const BinaryTree<T>& sub) const {
    return isSubtree(root, sub.root);
}

template <typename T>
std::string BinaryTree<T>::serialize() const {
    std::stringstream ss;
    toString(root, ss);
    return ss.str();
}

template <typename T>
void BinaryTree<T>::deserialize(const std::string& data) {
    clear(root);
    std::stringstream ss(data);
    root = fromString(ss);
}

template <typename T>
T BinaryTree<T>::findByPath(const std::string& path) const {
    Node<T>* current = root;
    for (char c : path) {
        if (!current) throw std::runtime_error("Invalid path");
        if (c == 'L') current = current->left;
        else if (c == 'R') current = current->right;
        else throw std::runtime_error("Invalid path character");
    }
    if (!current) throw std::runtime_error("Path leads to null");
    return current->data;
}
