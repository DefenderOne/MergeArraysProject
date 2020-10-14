#include <iostream>
#include <fstream>


// Дано k упорядоченных по возрастанию массивов по n элементов в каждом. 
// Получить из этих массив один, так же отсортированный по возрастанию

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}

int* mergeArrays(int* arrA, int* arrB, int sizeA, int sizeB) {
    int* result = new int[sizeA + sizeB];
    int indexA = 0, indexB = 0;
    while (indexA < sizeA && indexB < sizeB) {
        if (arrA[indexA] < arrB[indexB]) {
            result[indexA + indexB] = arrA[indexA];
            indexA++;
        }
        else {
            result[indexA + indexB] = arrB[indexB];
            indexB++;
        }
    }
    if (indexA == sizeA) {
        for (int i = indexB; i < sizeB; i++) {
            result[indexA + indexB] = arrB[indexB];
            indexB++;
        }
    }
    else {
        for (int i = indexA; i < sizeA; i++) {
            result[indexA + indexB] = arrA[indexA];
            indexA++;
        }
    }
    return result;
}

int* mergeSortArrays(int** arrays, int left, int right, int size) {
    int* result;
    if (left < right) {
        int* arrA = mergeSortArrays(arrays, left, (left + right) / 2, size);
        int sizeA = ((left + right) / 2 - left + 1) * size;
        printArray(arrA, sizeA);

        int* arrB = mergeSortArrays(arrays, (left + right) / 2 + 1, right, size);
        int sizeB = (right - (left + right) / 2) * size;
        printArray(arrB, sizeB);

        result = mergeArrays(arrA, arrB, sizeA, sizeB);
        delete[] arrA;
        delete[] arrB;
    }
    else {
        result = arrays[left];
    }
    return result;
}

int main() {
    int k, n;
    std::ifstream reader("input.txt");
    reader >> k >> n;
    int** arrays = new int*[k];
    for (int i = 0; i < k; i++) {
        arrays[i] = new int[n];
        for (int j = 0; j < n; j++) {
            reader >> arrays[i][j];
        }
    }
    reader.close();
    int* result = mergeSortArrays(arrays, 0, k - 1, n);
    printArray(result, n * k);
    delete[] result;
    system("pause");
}