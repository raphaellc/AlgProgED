#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
void troca(std::vector<T>& a, int i, int j) {
    T temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

template <typename T>
void bubbleSort(std::vector<T>& a) {
    bool trocaOcorreu;
    do {
        trocaOcorreu = false;
        for (int i = 0; i < a.size() - 1; i++) {
            if (a[i] > a[i + 1]) {
                troca(a, i, i + 1);
                trocaOcorreu = true;
            }
        }
    } while (trocaOcorreu);
}

int main() {
    std::vector<int> numeros = {7, 2, 8, 5, 4};
    bubbleSort(numeros);

    std::cout << "Números ordenados: ";
    for (int num : numeros) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::vector<std::string> palavras = {"zebra", "maçã", "gato", "bola"};
    bubbleSort(palavras);

    std::cout << "Palavras ordenadas: ";
    for (const std::string& palavra : palavras) {
        std::cout << palavra << " ";
    }
    std::cout << std::endl;

    return 0;
}
