#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

class Car {
public:
    std::string model;
    int year;
    double pricePerDay;
    bool isAvailable;

    // Constructor
    Car(std::string m, int y, double p) 
        : model(m), year(y), pricePerDay(p), isAvailable(true) {}

    // Display car details
    void display() {
        std::cout << "Model: " << model << " | Year: " << year 
                  << " | Price/Day: $" << pricePerDay 
                  << " | Available: " << (isAvailable ? "Yes" : "No") << std::endl;
    }
};

class CarRental {
private:
    std::vector<Car*> cars;  // Dynamic memory allocation for cars

public:
    // Add a car
    void addCar(std::string model, int year, double price) {
        try {
            Car* newCar = new Car(model, year, price);
            cars.push_back(newCar);
        }
        catch (const std::bad_alloc& e) {
            std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        }
    }

    // Rent a car
    void rentCar(std::string model) {
        for (auto car : cars) {
            if (car->model == model && car->isAvailable) {
                car->isAvailable = false;
                std::cout << "Car " << model << " rented successfully!\n";
                return;
            }
        }
        throw std::runtime_error("Car not available!");
    }

    // Return a car
    void returnCar(std::string model) {
        for (auto car : cars) {
            if (car->model == model && !car->isAvailable) {
                car->isAvailable = true;
                std::cout << "Car " << model << " returned successfully!\n";
                return;
            }
        }
        throw std::runtime_error("Car not found in rental records!");
    }

    // Display available cars
    void displayCars() {
        std::cout << "\nAvailable Cars:\n";
        for (auto car : cars) {
            car->display();
        }
    }

    // Destructor to free memory
    ~CarRental() {
        for (auto car : cars) {
            delete car;
        }
    }
};

int main() {
    CarRental rentalSystem;

    // Adding some cars
    rentalSystem.addCar("Toyota Corolla", 2020, 50);
    rentalSystem.addCar("Honda Civic", 2021, 55);
    rentalSystem.addCar("BMW X5", 2022, 120);

    int choice;
    std::string model;

    while (true) {
        std::cout << "\nCar Rental System Menu:\n";
        std::cout << "1. Display Available Cars\n";
        std::cout << "2. Rent a Car\n";
        std::cout << "3. Return a Car\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        try {
            switch (choice) {
                case 1:
                    rentalSystem.displayCars();
                    break;
                case 2:
                    std::cout << "Enter car model to rent: ";
                    std::cin.ignore();
                    std::getline(std::cin, model);
                    rentalSystem.rentCar(model);
                    break;
                case 3:
                    std::cout << "Enter car model to return: ";
                    std::cin.ignore();
                    std::getline(std::cin, model);
                    rentalSystem.returnCar(model);
                    break;
                case 4:
                    std::cout << "Exiting the system...\n";
                    return 0;
                default:
                    std::cout << "Invalid choice! Try again.\n";
            }
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}