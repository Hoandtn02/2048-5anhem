#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <sstream>

class Tile {
public:
    virtual ~Tile() {}
    virtual bool isEmpty() const = 0;
    virtual string getDisplayValue(bool useLetters) const = 0;
    virtual void setValue(int newValue) = 0;
    virtual int getValue() const = 0;
    virtual bool canCombine(const Tile& other) const = 0;
    virtual void combine(Tile& other) = 0;
};

class NumberTile : public Tile {
private:
    int value;

    string intToString(int value) const {
        ostringstream oss;
        oss << value;
        return oss.str();
    }

public:
    NumberTile(int val = 0) : value(val) {}

    bool isEmpty() const override {
        return value == 0;
    }

    string getDisplayValue(bool useLetters) const override {
        if (value == 0) return ".";
        if (useLetters) {
            switch (value) {
            case 2: return "A";
            case 4: return "B";
            case 8: return "C";
            case 16: return "D";
            case 32: return "E";
            case 64: return "F";
            case 128: return "G";
            case 256: return "H";
            case 512: return "I";
            case 1024: return "J";
            case 2048: return "K";
            default: return "X"; // Sử dụng 'X' thay cho '?'
            }
        }
        else {
            return intToString(value);
        }
    }

    void setValue(int newValue) override {
        value = newValue;
    }

    int getValue() const override {
        return value;
    }

    bool canCombine(const Tile& other) const override {
        return value == other.getValue() && value != 0;
    }

    void combine(Tile& other) override {
        if (canCombine(other)) {
            value *= 2;
            other.setValue(0);
        }
    }
};

#endif // TILE_H
