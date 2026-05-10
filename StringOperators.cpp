#include <iostream>
using namespace std;

class String {
    char* ptr;
    int length;

    int GetStrLen(const char* s) const {
        if (!s) return 0;
        int len = 0;
        while (s[len] != '\0') len++;
        return len;
    }

public:
    String() {
        length = 0;
        ptr = new char[1];
        ptr[0] = '\0';
    }

    String(const char* s) {
        length = GetStrLen(s);
        ptr = new char[length + 1];
        for (int i = 0; i < length; i++) ptr[i] = s[i];
        ptr[length] = '\0';
    }

    String(const String& other) {
        length = other.length;
        ptr = new char[length + 1];
        for (int i = 0; i <= length; i++) ptr[i] = other.ptr[i];
    }

    ~String() { delete[] ptr; }

    // Оператор присваивания
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] ptr;
            length = other.length;
            ptr = new char[length + 1];
            for (int i = 0; i <= length; i++) ptr[i] = other.ptr[i];
        }
        return *this;
    }

    // Оператор сложения (конкатенация)
    String operator+(const String& other) {
        int newLen = length + other.length;
        char* newBuf = new char[newLen + 1];
        for (int i = 0; i < length; i++) newBuf[i] = ptr[i];
        for (int i = 0; i < other.length; i++) newBuf[length + i] = other.ptr[i];
        newBuf[newLen] = '\0';
        
        String temp;
        delete[] temp.ptr;
        temp.ptr = newBuf;
        temp.length = newLen;
        return temp;
    }

    // Операторы сравнения
    bool operator==(const String& other) const {
        if (length != other.length) return false;
        for (int i = 0; i < length; i++) {
            if (ptr[i] != other.ptr[i]) return false;
        }
        return true;
    }

    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    // Оператор индексации
    char& operator[](int index) {
        return ptr[index];
    }

    // Оператор вывода
    friend ostream& operator<<(ostream& os, const String& s) {
        os << s.ptr;
        return os;
    }
};

int main() {
    String s1 = "Hello";
    String s2 = " World";
    String s3 = s1 + s2;

    cout << "S3: " << s3 << endl;
    cout << "S1 == S2: " << (s1 == s2) << endl;
    cout << "Char at index 1: " << s1[1] << endl;

    return 0;
}
