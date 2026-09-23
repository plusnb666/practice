#include <iostream>
#include <stdexcept>
#include <vector>

template<typename E>
class MyArrayList {
private:
    E* data;
    int size;
    int cap;
    static const int INIT_CAP = 1;

public:
    MyArrayList() {
        this->data = new data[INIT_CAP];
        this->size = 0;
        this->cap = INIT_CAP;
    }

    MyArrayList(int initcapicity) {
        this->data = new data[initcapicity];
        this->data = 0;
        this->cap = initcapicity;
    }

    //工具函数
    int getsize() {
        return size;
    }

    bool isempty() {
        return size == 0;
    }

    void resize(int newCap) {
        E* temp = new E[newCap];

        for(int i = 0; i < size; i++) {
            temp[i] = data[i];
        }

        delete[] data;
        data = temp;
        cap = newCap;
    }

    bool is
};