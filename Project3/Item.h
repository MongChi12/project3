#pragma once
#include <iostream>
#include <string>
using namespace std;

class Item {
    string name_;
    int price_;
public:
    Item(string name = "����", int price = 0) : name_(std::move(name)), price_(price) {}
    int  GetPrice() const { return price_; }
    void PrintInfo() const {
        cout << "[�̸�: " << name_ << ", ����: " << price_ << "G]\n";
    }
};
