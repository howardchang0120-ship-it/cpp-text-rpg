#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// ================= 3. Item Class =================
class Item {
private:
    string name;
    string type; 
    int effectValue;
    int quantity;

public:
    Item(string n, string t, int effect, int q) : name(n), type(t), effectValue(effect), quantity(q) {}

    string getName() const { return name; }
    string getType() const { return type; }
    int getQuantity() const { return quantity; }

    void use() {
        if (isAvailable()) {
            quantity--;
        }
    }

    void showInfo() const {
        cout << "Item: " << name << " | Effect: +" << effectValue << " " << type << " | Left: " << quantity << endl;
    }

    bool isAvailable() const {
        return quantity > 0;
    }

    int getEffectValue() const { return effectValue; }
};

// ================= 2. Skill Class =================
class Skill {
private:
    string name;
    int damage;
    int mpCost;

public:
    Skill(string n, int dmg, int cost) : name(n), damage(dmg), mpCost(cost) {}

    string getName() const { return name; }
    int getMpCost() const { return mpCost; }

    void use() const {
        cout << "Cast skill: [" << name << "]!" << endl;
    }

    void showInfo() const {
        cout << "Skill: " << name << " | DMG: " << damage << " | MP Cost: " << mpCost << endl;
    }

    int getDamage() const {
        return damage;
    }
};

// ================= 4. Monster Class =================
class Monster {
private:
    string name;
    int hp;
    int attackPower;
    int rewardGold;

public:
    Monster(string n, int h, int atk, int gold) : name(n), hp(h), attackPower(atk), rewardGold(gold) {}

    string getName() const { return name; }
    int getRewardGold() const { return rewardGold; }

    int attack() const {
        return attackPower;
    }

    void takeDamage(int damage) {
        hp -= damage;
        if (hp < 0) hp = 0;
        cout << name << " took " << damage << " damage! (HP left: " << hp << ")" << endl;
    }

    bool isAlive() const {
        return hp > 0;
    }

    void showInfo() const {
        cout << "Monster: " << name << " | HP: " << hp << " | ATK: " << attackPower << " | Gold Drop: " << rewardGold << endl;
    }
};

// ================= 1. Player Class =================
class Player {
private:
    string name;
    int hp;
    int maxHp;
    int mp;
    int maxMp;
    int attackPower;
    int gold;
    vector<Item> items;
    vector<Skill> skills;

public:
    Player(string n, int h, int m, int atk) : name(n), hp(h), maxHp(h), mp(m), maxMp(m), attackPower(atk), gold(0) {}

    string getName() const { return name; }
    
    void addItem(Item item) { items.push_back(item); }
    void addSkill(Skill skill) { skills.push_back(skill); }
    void addGold(int amount) { gold += amount; }

    int attack() const {
        return attackPower;
    }

    void takeDamage(int damage) {
        hp -= damage;
        if (hp < 0) hp = 0;
        cout << name << " took " << damage << " damage! (HP left: " << hp << ")" << endl;
    }

    void useItem(int index) {
        if (index >= 0 && index < items.size()) {
            if (items[index].isAvailable()) {
                items[index].use();
                cout << name << " used " << items[index].getName() << "!" << endl;
                
                if (items[index].getType() == "HP") {
                    hp += items[index].getEffectValue();
                    if (hp > maxHp) hp = maxHp;
                    cout << "Recovered " << items[index].getEffectValue() << " HP! (Current HP: " << hp << ")" << endl;
                } else if (items[index].getType() == "MP") {
                    mp += items[index].getEffectValue();
                    if (mp > maxMp) mp = maxMp;
                    cout << "Recovered " << items[index].getEffectValue() << " MP! (Current MP: " << mp << ")" << endl;
                }
            } else {
                cout << "Item runs out!" << endl;
            }
        } else {
            cout << "Invalid item selection!" << endl;
        }
    }

    void showItems() const {
        cout << "\n--- Inventory ---" << endl;
        for (size_t i = 0; i < items.size(); i++) {
            cout << "[" << i + 1 << "] ";
            items[i].showInfo();
        }
    }

    int useSkill(int index) {
        if (index >= 0 && index < skills.size()) {
            if (mp >= skills[index].getMpCost()) {
                mp -= skills[index].getMpCost();
                skills[index].use();
                return skills[index].getDamage();
            } else {
                cout << "Not enough MP!" << endl;
                return -1; 
            }
        }
        cout << "Invalid skill selection!" << endl;
        return -1;
    }

    void showSkills() const {
        cout << "\n--- Skill List ---" << endl;
        for (size_t i = 0; i < skills.size(); i++) {
            cout << "[" << i + 1 << "] ";
            skills[i].showInfo();
        }
    }

    bool isAlive() const {
        return hp > 0;
    }

    void showStatus() const {
        cout << "=============================" << endl;
        cout << "Player: " << name << " | HP: " << hp << "/" << maxHp << " | MP: " << mp << "/" << maxMp << " | Gold: " << gold << endl;
        cout << "=============================" << endl;
    }
};

// ================= Main Loop =================
int main() {
    srand(time(0));

    // Initialize Player
    Player player("Hero", 100, 50, 15);
    player.addItem(Item("Small HP Potion", "HP", 30, 3));
    player.addItem(Item("MP Potion", "MP", 20, 2));
    player.addSkill(Skill("Fireball", 35, 15));
    player.addSkill(Skill("Smash", 25, 10));

    // Initialize Monster
    Monster monster("Goblin King", 80, 12, 50);

    cout << "Game Start! A wild monster appeared!" << endl;
    monster.showInfo();

    // Battle Loop
    while (player.isAlive() && monster.isAlive()) {
        player.showStatus();
        cout << "\nChoose action:" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Skill" << endl;
        cout << "3. Item" << endl;
        cout << "Enter number (1-3): ";
        
        int choice;
        cin >> choice;
        cout << endl;

        bool actionTaken = false; 

        if (choice == 1) {
            cout << player.getName() << " attacks!" << endl;
            monster.takeDamage(player.attack());
            actionTaken = true;
        } 
        else if (choice == 2) {
            player.showSkills();
            cout << "Choose a skill to use (0 to cancel): ";
            int skillChoice;
            cin >> skillChoice;
            if (skillChoice > 0) {
                int dmg = player.useSkill(skillChoice - 1);
                if (dmg != -1) {
                    monster.takeDamage(dmg);
                    actionTaken = true;
                }
            }
        } 
        else if (choice == 3) {
            player.showItems();
            cout << "Choose an item to use (0 to cancel): ";
            int itemChoice;
            cin >> itemChoice;
            if (itemChoice > 0) {
                player.useItem(itemChoice - 1);
                actionTaken = true;
            }
        } 
        else {
            cout << "Invalid input, please try again!" << endl;
        }

        // Monster Turn
        if (actionTaken && monster.isAlive()) {
            cout << "\n--- Monster Turn ---" << endl;
            cout << monster.getName() << " attacks!" << endl;
            player.takeDamage(monster.attack());
            cout << "----------------\n" << endl;
        }
    }

    // Result
    if (player.isAlive()) {
        cout << "\nBattle End! You defeated " << monster.getName() << "!" << endl;
        cout << "Obtained " << monster.getRewardGold() << " Gold!" << endl;
        player.addGold(monster.getRewardGold());
    } else {
        cout << "\nYou were defeated by " << monster.getName() << "... Game Over." << endl;
    }

    return 0;
}