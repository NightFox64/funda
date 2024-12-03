#include "PerishbleProduct.h"

class BuildingMaterial : public Product {
private:
    bool flammable;

public:
    BuildingMaterial(const string& name, int id, double weight, double price, int shelfLife, bool flammable)
        : Product(name, id, weight, price, shelfLife), flammable(flammable) {}

    double calculateStorageFee() const override {
        return getWeight() * (flammable ? 0.5 : 0.2);
    }

    void displayInfo() const override {
        Product::displayInfo();
        cout << "Flammable: " << (flammable ? "Yes" : "No") << endl;
    }

    bool getFlammable() {
        return flammable;
    }
};