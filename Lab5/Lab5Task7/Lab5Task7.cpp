#include "Warehouse.h"

int main() {
    Warehouse warehouse;

    time_t now = time(0);
    time_t expiration = now + 5 * 24 * 60 * 60;

    warehouse += make_shared<PerishableProduct>("Milk", 1, 2.0, 1.5, 7, expiration);
    warehouse += make_shared<ElectronicProduct>("Laptop", 2, 3.0, 1500.0, 0, 24, 65.0);
    warehouse += make_shared<BuildingMaterial>("Bricks", 3, 100.0, 500.0, 0, true);

    cout << warehouse << endl << "-----------------------------------------" << endl;

    auto expiringProducts = warehouse.getExpiringProducts(7);
    cout << "Expiring Products:" << endl;
    for (const auto& product : expiringProducts) {
        product->displayInfo();
    }

    cout << endl << "-----------------------------------------" << endl;

    warehouse -= 1;
    cout << warehouse;

    return 0;
}
