#include <iostream>
#include <vector>
#include <optional>
#include <cassert>
#include <memory> // Para ponteiros inteligentes

template <typename K>
class Interval {
public:
    K minVal, maxVal;

    Interval(K min, K max) : minVal(min), maxVal(max) {}

    K min() const { return minVal; }
    K max() const { return maxVal; }
};

template <typename K>
class Interval2D {
public:
    Interval<K> intervalX;
    Interval<K> intervalY;

    Interval2D(K x1, K x2, K y1, K y2) :
        intervalX(std::min(x1, x2), std::max(x1, x2)),
        intervalY(std::min(y1, y2), std::max(y1, y2)) {}

    bool contains(const K& x, const K& y) const {
        return x >= intervalX.min() && x <= intervalX.max() &&
               y >= intervalY.min() && y <= intervalY.max();
    }
};

template <typename K, typename V>
class QuadTreeNode {
public:
    K x;
    K y;
    V value;
    QuadTreeNode<K, V>* nw;
    QuadTreeNode<K, V>* ne;
    QuadTreeNode<K, V>* sw;
    QuadTreeNode<K, V>* se;

    QuadTreeNode(K _x, K _y, V _value) : x(_x), y(_y), value(_value), nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr) {}

    ~QuadTreeNode() {
        delete nw;
        delete ne;
        delete sw;
        delete se;
    }
};

template <typename K, typename V>
class QuadTree {

private:
    QuadTreeNode<K, V>* root;

    bool less(const K& k1, const K& k2) const {
        return k1 < k2; // Assumindo que K tem o operador< definido
    }

    QuadTreeNode<K, V>* insert(QuadTreeNode<K, V>* node, K x, K y, V value) {
        if (!node) {
            return new QuadTreeNode<K, V>(x, y, value);
        } else if (less(x, node->x) && !less(y, node->y)) {
            node->nw = insert(node->nw, x, y, value);
        } else if (less(x, node->x) && less(y, node->y)) {
            node->sw = insert(node->sw, x, y, value);
        } else if (!less(x, node->x) && !less(y, node->y)) {
            node->ne = insert(node->ne, x, y, value);
        } else if (!less(x, node->x) && less(y, node->y)) {
            node->se = insert(node->se, x, y, value);
        }
        return node;
    }

    void query2D(QuadTreeNode<K, V>* node, const Interval2D<K>& rect) {
        if (!node) {
            return;
        }
        K xMin = rect.intervalX.min();
        K yMin = rect.intervalY.min();
        K xMax = rect.intervalX.max();
        K yMax = rect.intervalY.max();

        if (rect.contains(node->x, node->y)) {
            std::cout << " (" << node->x << ", " << node->y << ") " << node->value << std::endl;
        }
        if (less(xMin, node->x) && !less(yMax, node->y)) query2D(node->nw, rect);
        if (less(xMin, node->x) && less(yMin, node->y)) query2D(node->sw, rect);
        if (!less(xMax, node->x) && !less(yMax, node->y)) query2D(node->ne, rect);
        if (!less(xMax, node->x) && less(yMin, node->y)) query2D(node->se, rect);
    }

public:
    QuadTree() : root(nullptr) {}

    ~QuadTree() {
        delete root;
    }

    void clear() {
        delete root;
        root = nullptr;
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void insert(K x, K y, V value) {
        root = insert(root, x, y, value);
    }

    void query2D(const Interval2D<K>& rect) {
        query2D(root, rect);
    }
};


// Inclua sua implementação da QuadTree aqui (como fornecido anteriormente)
// ... (QuadTree, QuadTreeNode, Interval, Interval2D)

int main() {
    // Teste 1: Inserção básica e isEmpty
    QuadTree<int, std::string> qt1;
    assert(qt1.isEmpty() == true);
    qt1.insert(1, 1, "A");
    assert(qt1.isEmpty() == false);
    qt1.clear();
    assert(qt1.isEmpty() == true);

    std::cout << "Teste 1 Passou: Inserção básica e isEmpty" << std::endl;

    // Teste 2: Inserção e Query2D
    QuadTree<int, std::string> qt2;
    qt2.insert(1, 2, "A");
    qt2.insert(5, 3, "B");
    qt2.insert(2, 8, "C");
    qt2.insert(7, 6, "D");

    Interval2D<int> rect2(0, 6, 1, 5);
    std::cout << "Saída do Teste 2: Pontos dentro do retângulo (0,6) x (1,5)" << std::endl;
    qt2.query2D(rect2);
    // Saída esperada: (1, 2) A e (5, 3) B (a ordem pode variar)

    std::cout << "Teste 2 Interativo: Verifique a saída da consulta acima" << std::endl;

    // Teste 3: Inserção com mais pontos e uma consulta maior
    QuadTree<int, int> qt3;
    qt3.insert(10, 10, 1);
    qt3.insert(20, 20, 2);
    qt3.insert(15, 15, 3);
    qt3.insert(5, 5, 4);
    qt3.insert(25, 25, 5);

    Interval2D<int> rect3(0, 30, 0, 30);
    std::cout << "Saída do Teste 3: Todos os pontos na árvore" << std::endl;
    qt3.query2D(rect3); // Espera todos os 5 pontos

    Interval2D<int> rect4(12, 18, 12, 18);
    std::cout << "Saída do Teste 3: Consulta de ponto único" << std::endl;
    qt3.query2D(rect4); // Espera apenas (15, 15)

    std::cout << "Teste 3 Interativo: Verifique as saídas da consulta" << std::endl;


    // Teste 4: Pontos na linha divisória
    QuadTree<int, char> qt4;
    qt4.insert(1, 1, 'A');
    qt4.insert(1, 5, 'B');
    qt4.insert(5, 1, 'C');
    qt4.insert(5, 5, 'D');

    Interval2D<int> rect5(1, 5, 1, 5);
    std::cout << "Saída do Teste 4: Pontos no limite" << std::endl;
    qt4.query2D(rect5); // Espera todos os pontos

    std::cout << "Teste 4 Interativo: Verifique se todos os pontos são encontrados" << std::endl;


    // Teste 5: Consulta de QuadTree vazia
    QuadTree<int, double> qt5;
    Interval2D<int> rect6(0, 10, 0, 10);
    std::cout << "Saída do Teste 5: Consulta em árvore vazia (nenhuma saída esperada)" << std::endl;
    qt5.query2D(rect6); // Deve ser sem saída

    std::cout << "Teste 5 Interativo: Verifique se não há saída" << std::endl;


    std::cout << "Todos os Testes Concluídos" << std::endl;

    return 0;
}