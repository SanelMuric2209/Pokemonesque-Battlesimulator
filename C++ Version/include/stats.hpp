#pragma once
#include <string>
#include <iostream>
using std::string, std::min, std::max, std::to_string;

class Stat {
    int base;
    int _current;
    bool limitToBase;
public:
    const int& current;
    Stat(): limitToBase(false), current(_current) {}
    Stat(bool limitToBase): limitToBase(limitToBase), current(_current) {}

    void setBase(int value) {
        base = value;
        _current = value;
    };
    void operator++() {
        base += 2;
    }
    void operator++(int) {
        operator++();
    }
    void reset() {
        _current = base;
    }
    void modify(int delta) {
        _current = max(0, min(limitToBase ? base : 100, _current + delta));
    }
    string toString() const {
        return to_string(_current) + "/" + to_string(base);
    }
};
