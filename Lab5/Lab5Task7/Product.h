#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <map>

using namespace std;

class Product {
private:
    string name;
    int id;
    double weight;
    double price;
    int shelfLife;

public:
    Product(const string& name, int id, double weight, double price, int shelfLife)
        : name(name), id(id), weight(weight), price(price), shelfLife(shelfLife) {}

    Product(const Product& other)
        : name(other.name), id(other.id), weight(other.weight), price(other.price), shelfLife(other.shelfLife) {}

    virtual ~Product() = default;

    Product& operator=(const Product& other) {
        if (this != &other) {
            name = other.name;
            id = other.id;
            weight = other.weight;
            price = other.price;
            shelfLife = other.shelfLife;
        }
        return *this;
    }

    virtual void displayInfo() const {
        cout << "Name: " << name
             << ", ID: " << id
             << ", Weight: " << weight << "kg"
             << ", Price: $" << price
             << ", Shelf Life: " << shelfLife << " days" << endl;
    }

    virtual double calculateStorageFee() const {
        return weight * 0.1;
    }

    int getId() const {
        return id; 
    }
    string getName() const {
        return name;
    }
    double getWeight() const {
        return weight;
    }
    double getPrice() const {
        return price;
    }
    int getShelLife() const {
        return shelfLife;
    }

//protected:
//    virtual double calculateStorageFee() const {
//        return weight * 0.1;
//    }
};