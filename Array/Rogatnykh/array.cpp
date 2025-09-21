﻿#include <iostream>
#include <cstdint>

using namespace std;

template <typename T>
struct Array {
    T* data;
    uint32_t capacity;
    uint32_t size;

    Array(const uint32_t cap) { //Конструктор (инициализация и создание)
        capacity = cap;
        size = 0;
        data = new T[cap];
    }

    ~Array() { //Деструктор (очищает помять когда выходим из области видимости с массивом !!!ОЧЕНЬ ВАЖНО!!!)
        delete[] data;
    }

    Array(const Array<T>& other) { //Копирующий конструктор (Если создаём новый массив на основе предыдущего)
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        for (uint32_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    Array<T>& operator=(const Array<T>& other) { //Копирующий оператор присваивания (Если имеем два массива с данными и присваиваем один другому)
        if (this == &other) { //Защита от a = a
            return *this;
        }
        delete[] data;

        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        for (uint32_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        return *this;
    }
};

template <typename T>
void doubleArray(Array<T>& ar) { //Удвоение массива при достижении лимита capacity
    uint32_t cap = ar.capacity;
    T* newData = new T[cap * 2];
    ar.capacity = cap * 2;
    for (uint32_t i = 0; i < ar.size; i++) {
        newData[i] = ar.data[i];
    }
    delete[] ar.data;
    ar.data = newData;
}

template <typename T>
void pushBack(Array<T>& ar, T value) { //Добавление элемента в конец массива
    if (ar.size >= ar.capacity) {
        doubleArray(ar);
    }
    ar.data[ar.size++] = value;
}

template <typename T>
void pushByIndex(Array<T>& ar, uint32_t index, T value) { //Добавление элемента по индексу
    if (ar.size >= ar.capacity) {
        doubleArray(ar);
    }
    if (index >= 0 && index < ar.size) {
        for (uint32_t j = ar.size - 1; j >= index; j--) {
            ar.data[j + 1] = ar.data[j];
        }
        ar.data[index] = value;
        ar.size++;
    }
}

template <typename T>
T getByIndex(Array<T>& ar, uint32_t index) { //Получение элемента по индексу
    if (index >= 0 && index < ar.size)
        return ar.data[index];
}

template <typename T>
void deleteByIndex(Array<T>& ar, uint32_t index) {
    if (index >= 0 && index < ar.size) {
        for (uint32_t i = index; i < ar.size; i++) {
            ar.data[i] = ar.data[i + 1];
        }
        ar.size--;
    }
}

template <typename T>
void swapByIndex(Array<T>& ar, uint32_t index, T value) {
    if (index >= 0 && index < ar.size) {
        ar.data[index] = value;
    }
}


template <typename T>
void readArray(Array<T>& ar) {
    for (uint32_t i = 0; i < ar.size; i++) {
        cout << ar.data[i] << " ";
    }
    cout << endl;
}

int main()
{
    Array<int> hi(2);
    pushBack(hi, 10);
    pushBack(hi, 11);
    pushBack(hi, 12);
    pushBack(hi, 13);
    readArray(hi);
    pushByIndex(hi, 1, 404);
    readArray(hi);
    deleteByIndex(hi, 1);
    readArray(hi);
    swapByIndex(hi, 3, 505);
    readArray(hi);

    return 0;
}

