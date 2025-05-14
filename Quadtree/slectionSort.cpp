#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
void selectionSort(std::vector<T>& a) {
    int n = a.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            std::swap(a[i], a[minIndex]);
        }
    }
}

int main() {
    std::vector<int> numeros = {5, 2, 8, 1, 9, 3};
    selectionSort(numeros);

    std::cout << "Números ordenados: ";
    for (int num : numeros) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::vector<std::string> palavras = {"zebra", "apple", "cat", "ball"};
    selectionSort(palavras);

    std::cout << "Palavras ordenadas: ";
    for (const std::string& palavra : palavras) {
        std::cout << palavra << " ";
    }
    std::cout << std::endl;

    return 0;
}
