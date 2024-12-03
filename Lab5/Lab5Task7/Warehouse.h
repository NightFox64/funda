#include "ElectronicProduct.h"

class Warehouse {
private:
    vector<shared_ptr<Product>> inventory;

public:
    void addProduct(shared_ptr<Product> product) {
        inventory.push_back(product);
    }

    void removeProduct(int id) {
        inventory.erase(remove_if(inventory.begin(), inventory.end(),
                                  [id](const shared_ptr<Product>& product) {
                                      return product->getId() == id;
                                  }),
                        inventory.end());
    }

    shared_ptr<Product> findProduct(int id) const {
        for (const auto& product : inventory) {
            if (product->getId() == id) return product;
        }
        return nullptr;
    }

    vector<shared_ptr<Product>> getExpiringProducts(int days) const {
        vector<shared_ptr<Product>> expiring;
        time_t now = time(0);
        for (const auto& product : inventory) {
            auto perishable = dynamic_pointer_cast<PerishableProduct>(product);
            if (perishable) {
                double remainingDays = difftime(perishable->getExpirationDate(), now) / (60 * 60 * 24);
                if (remainingDays <= days) {
                    expiring.push_back(perishable);
                }
            }
        }
        return expiring;
    }

    void displayInventory() const {
        map<string, vector<shared_ptr<Product>>> categories;
        for (const auto& product : inventory) {
            if (dynamic_pointer_cast<PerishableProduct>(product)) {
                categories["Perishable"].push_back(product);
            } else if (dynamic_pointer_cast<ElectronicProduct>(product)) {
                categories["Electronics"].push_back(product);
            } else if (dynamic_pointer_cast<BuildingMaterial>(product)) {
                categories["Building Materials"].push_back(product);
            }
        }

        for (const auto& [category, products] : categories) {
            cout << "Category: " << category << endl;
            for (const auto& product : products) {
                product->displayInfo();
            }
        }
    }

    Warehouse& operator+=(shared_ptr<Product> product) {
        addProduct(product);
        return *this;
    }

    Warehouse& operator-=(int id) {
        removeProduct(id);
        return *this;
    }

    shared_ptr<Product> operator[](int id) const {
        return findProduct(id);
    }

    friend ostream& operator<<(ostream& os, const Warehouse& warehouse) {
        os << "Warehouse Inventory:" << endl;
        warehouse.displayInventory();
        os << "Total Storage Fee: $" << warehouse.calculateTotalStorageFee() << endl;
        return os;
    }

private:
    double calculateTotalStorageFee() const {
        double total = 0;
        for (const auto& product : inventory) {
            total += product->calculateStorageFee();
        }
        return total;
    }
};