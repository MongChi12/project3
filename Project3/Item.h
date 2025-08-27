#pragma once
#include <iostream>
#include <string>
using namespace std;

class Item {
    string name_;
    int price_;
public:
    Item(string name = "무명", int price = 0) : name_(std::move(name)), price_(price) {}
    int  GetPrice() const { return price_; }
    void PrintInfo() const {
        cout << "[이름: " << name_ << ", 가격: " << price_ << "G]\n";
    }
};
