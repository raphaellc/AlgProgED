#include <iostream>
#include <vector>
#include <algorithm> // Para std::swap

// Função auxiliar para trocar elementos (equivalente ao seu 'exchange')
template <typename T>
void troca(std::vector<T>& a, int i, int j) {
    std::swap(a[i], a[j]); // Usando a função swap da biblioteca padrão
}

template <typename T>
void insertionSort(std::vector<T>& a) {
    for (int i = 1; i < a.size(); ++i) {
        for (int j = i; j > 0 && a[j - 1] > a[j]; --j) {
            troca(a, j - 1, j);
        }
    }
}

int main() {
    std::vector<int> numeros = {5, 2, 8, 1, 9, 3};
    insertionSort(numeros);

    std::cout << "Números ordenados: ";
    for (int num : numeros) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::vector<std::string> palavras = {"zebra", "apple", "cat", "ball"};
    insertionSort(palavras);

    std::cout << "Palavras ordenadas: ";
    for (const std::string& palavra : palavras) {
        std::cout << palavra << " ";
    }
    std::cout << std::endl;

    return 0;
}
