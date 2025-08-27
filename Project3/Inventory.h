#pragma once
#include <iostream>
#include <algorithm> 
using namespace std;

template <typename T>
class Inventory {
private:
    T* pItems_;     
    int capacity_;   
    int size_;       

public:

    explicit Inventory(int capacity = 10)
        : pItems_(nullptr), capacity_(capacity), size_(0) {
        if (capacity_ <= 0) capacity_ = 1;
        pItems_ = new T[capacity_];
    }

    ~Inventory() {
        delete[] pItems_;
        pItems_ = nullptr;
        capacity_ = 0;
        size_ = 0;
    }

    Inventory(const Inventory<T>& other)
        : pItems_(nullptr), capacity_(other.capacity_), size_(other.size_) {
        pItems_ = new T[capacity_];
        for (int i = 0; i < size_; ++i) {
            pItems_[i] = other.pItems_[i];
        }
        cout << "인벤토리 복사 완료\n";
    }

    void Assign(const Inventory<T>& other) {
        if (this == &other) return;
        delete[] pItems_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        pItems_ = new T[capacity_];
        for (int i = 0; i < size_; ++i) {
            pItems_[i] = other.pItems_[i];
        }
    }

    void AddItem(const T& item) {
        if (size_ < capacity_) {
            pItems_[size_++] = item;
        }
        else {
            cout << "인벤토리가 꽉 찼습니다!\n";
        }
    }

    void RemoveLastItem() {
        if (size_ > 0) {
            --size_;
        }
        else {
            cout << "인벤토리가 비어있습니다.\n";
        }
    }

    int GetSize() const { return size_; }

    int GetCapacity() const { return capacity_; }

    void PrintAllItems() const {
        if (size_ == 0) {
            cout << "(비어있음)\n";
            return;
        }
        for (int i = 0; i < size_; ++i) {
            pItems_[i].PrintInfo();
        }
    }

    void Resize(int newCapacity) {
        if (newCapacity <= 0) newCapacity = 1;
        if (newCapacity == capacity_) return;

        T* newArr = new T[newCapacity];
        int newSize = min(size_, newCapacity);
        for (int i = 0; i < newSize; ++i) {
            newArr[i] = pItems_[i];
        }
        delete[] pItems_;
        pItems_ = newArr;
        capacity_ = newCapacity;
        size_ = newSize;
    }

    void AddItemWithAutoExpand(const T& item) {
        if (size_ >= capacity_) {
            Resize(capacity_ * 2);
        }
        AddItem(item);
    }

    void SortItems() {
        std::sort(pItems_, pItems_ + size_,
            [](const T& a, const T& b) {
                return a.GetPrice() < b.GetPrice();
            });
    }
};
