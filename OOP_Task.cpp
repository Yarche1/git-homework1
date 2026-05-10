#include <iostream>
#include <string>

using namespace std;

class Character {
protected:
    string name;
    float health;
    float max_health;
    bool is_dead;

    void UpdateIsDead() {
        is_dead = health <= 0;
        if (is_dead) cout << name << " умер!" << endl;
    }

public:
    Character(string name, float health) {
        this->name = name;
        this->health = health;
        this->max_health = health;
        this->is_dead = false;
        UpdateIsDead();
    }

    virtual void getInfo() {
        cout << "Имя: " << name << "; Здоровье: " << health << "/" << max_health << ";\n";
    }

    float getHealth() { return health; }
    string getName() { return name; }
    bool getIsDead() { return is_dead; }

    void setHealth(float health) {
        this->health = health;
        if (this->health < 0) this->health = 0;
        if (this->health > max_health) this->health = max_health;
        UpdateIsDead();
    }

    void heal(float amount) {
        if (!is_dead) setHealth(health + amount);
    }

    void takeDamage(float damage) {
        setHealth(health - damage);
    }
};

class Warrior : public Character {
protected:
    float strength;

public:
    Warrior(string name, float health, float strength)
        : Character(name, health), strength(strength) {}

    void attack(Character* victim) {
        cout << name << " атакует " << victim->getName() << "!" << endl;
        victim->takeDamage(strength);
    }
};

class Thief : public Warrior {
public:
    Thief(string name, float health, float strength) : Warrior(name, health, strength) {}
    void stealLife(Character* target) {
        cout << name << " крадет жизнь!" << endl;
        target->takeDamage(strength);
        this->heal(strength * 0.5f);
    }
};

class Zealot : public Character {
protected:
    float mana;
public:
    Zealot(string name, float health, float mana) : Character(name, health), mana(mana) {}
    void castHeal(Character* target, float amount) {
        if (mana >= amount) {
            target->heal(amount);
            mana -= amount;
        }
    }
};

class Necromancer : public Zealot {
public:
    Necromancer(string name, float health, float mana) : Zealot(name, health, mana) {}
    void revive(Character* target) {
        if (target->getIsDead() && mana >= 20) {
            target->setHealth(10);
            mana -= 20;
            cout << target->getName() << " воскрешен!" << endl;
        }
    }
};

int main() {
    Warrior w1("Varvar", 100, 20);
    Thief t1("Vor", 80, 15);
    Necromancer n1("Necro", 70, 50);
    w1.attack(&t1);
    t1.stealLife(&w1);
    n1.revive(&t1);
    w1.getInfo();
    return 0;
}
