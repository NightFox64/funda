#include "Product.h"

class PerishableProduct : public Product {
private:
    time_t expirationDate;

public:
    PerishableProduct(const string& name, int id, double weight, double price, int shelfLife, time_t expirationDate)
        : Product(name, id, weight, price, shelfLife), expirationDate(expirationDate) {}

    double calculateStorageFee() const override {
        time_t now = time(0);
        double daysToExpire = difftime(expirationDate, now) / (60 * 60 * 24);
        if (daysToExpire < 0) daysToExpire = 0;
        return getWeight() * (0.2 + (1.0 / (daysToExpire + 1)));
    }

    void displayInfo() const override {
        Product::displayInfo();
        cout << "Expiration Date: " << ctime(&expirationDate);
    }

    time_t getExpirationDate() const {
        return expirationDate;
    }
};