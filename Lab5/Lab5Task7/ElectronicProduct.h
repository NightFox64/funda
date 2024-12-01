#include "BuildingMaterial.h"

class ElectronicProduct : public Product {
private:
    int warrantyPeriod;
    double powerRating;

public:
    ElectronicProduct(const string& name, int id, double weight, double price, int shelfLife, int warrantyPeriod, double powerRating)
        : Product(name, id, weight, price, shelfLife), warrantyPeriod(warrantyPeriod), powerRating(powerRating) {}

    void displayInfo() const override {
        Product::displayInfo();
        cout << "Warranty Period: " << warrantyPeriod << " months"
             << ", Power Rating: " << powerRating << "W" << endl;
    }

    int getWarrantyPeriod() const {
        return warrantyPeriod;
    }
    double getPowerRating() const {
        return powerRating;
    }
};