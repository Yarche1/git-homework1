#include <iostream>
#include <string>

using namespace std;

class Material {
public:
    string name;
    int amount;

    Material(string n = "None", int a = 0) : name(n), amount(a) {}
};

class MaterialContainer {
private:
    Material* materials;
    int capacity;
    int count;

public:
    MaterialContainer(int cap = 5) : capacity(cap), count(0) {
        materials = new Material[capacity];
    }


cat <<EOF > MaterialContainer.cpp
#include <iostream>
#include <string>

using namespace std;

class Material {
public:
    string name;
    int amount;

    Material(string n = "None", int a = 0) : name(n), amount(a) {}
};

class MaterialContainer {
private:
    Material* materials;
    int capacity;
    int count;

public:
    MaterialContainer(int cap = 5) : capacity(cap), count(0) {
        materials = new Material[capacity];
    }

    ~MaterialContainer() {
        delete[] materials;
    }

    bool addMaterial(string name, int amount) {
        // Если такой материал уже есть, просто добавляем количество
        for (int i = 0; i < count; i++) {
            if (materials[i].name == name) {
                materials[i].amount += amount;
                return true;
            }
        }

        // Если места нет
        if (count >= capacity) {
            cout << "Контейнер заполнен!" << endl;
            return false;
        }

        // Добавляем новый материал
        materials[count] = Material(name, amount);
        count++;
        return true;
    }

    void showContent() const {
        cout << "--- Содержимое контейнера ---" << endl;
        if (count == 0) cout << "Пусто" << endl;
        for (int i = 0; i < count; i++) {
            cout << materials[i].name << ": " << materials[i].amount << endl;
        }
    }
};

int main() {
    MaterialContainer chest(3);
    chest.addMaterial("Iron", 50);
    chest.addMaterial("Wood", 20);
    chest.addMaterial("Iron", 10); // Добавится к существующему Iron

    chest.showContent();

    return 0;
}
