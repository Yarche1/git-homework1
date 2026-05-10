#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Item {
public:
    string Name;
    Item(string name = "Empty") : Name(name) {}
};

class ItemSlot {
public:
    Item* item;
    ItemSlot() : item(nullptr) {}
    bool isEmpty() { return item == nullptr; }
    void setItem(Item* newItem) { item = newItem; }
};

class Inventory {
private:
    int slots_num;
    ItemSlot* slots;
public:
    Inventory(int size = 5) : slots_num(size) {
        slots = new ItemSlot[slots_num];
    }
    ~Inventory() { delete[] slots; }
    bool addItem(Item* newItem) {
        for (int i = 0; i < slots_num; i++) {
            if (slots[i].isEmpty()) {
                slots[i].setItem(newItem);
                return true;
            }
        }
        return false;
    }
};

class Actor {
public:
    virtual string GetType() { return "Actor"; }
    virtual ~Actor() {}
};

class Character : public Actor {
public:
    Inventory inventory;
    string Name;
    Character(string name) : Name(name), inventory(10) {}
    string GetType() override { return "Character: " + Name; }
};

class DroppedItem : public Actor {
public:
    Item item;
    DroppedItem(string itemName) : item(itemName) {}
    string GetType() override { return "DroppedItem: " + item.Name; }
};

class Scene {
private:
    vector<Actor*> actors;
public:
    void AddActor(Actor* actor) {
        actors.push_back(actor);
    }
    void ShowStatus() {
        for (auto actor : actors) {
            cout << actor->GetType() << endl;
        }
    }
    ~Scene() {
        for (auto actor : actors) delete actor;
    }
};

int main() {
    Scene mainScene;
    mainScene.AddActor(new Character("Hero"));
    mainScene.AddActor(new DroppedItem("Sword"));
    mainScene.ShowStatus();
    return 0;
}
