#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

const double M_PI = 3.14; 


class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
};

class Circle : public Shape {
public:
    Circle(double radius) : radius(radius) {}

    double area() const override {
        return M_PI * radius * radius;
    }

private:
    double radius;
};


class Rectangle : public Shape {
public:
    Rectangle(double width, double height) : width(width), height(height) {}

    double area() const override {
        return width * height; 
    }

private:
    double width;
    double height;
};


class ShapeManager {
public:
    void addShape(std::shared_ptr<Shape> shape) {
        shapes.push_back(shape);
    }

    void showAreas() const {
        for (const auto& shape : shapes) {
            std::cout << "Area: " << shape->area() << "\n";
        }
    }

private:
    std::vector<std::shared_ptr<Shape>> shapes;
};


void showMenu() {
    std::cout << "1. Add Circle\n";
    std::cout << "2. Add Rectangle\n";
    std::cout << "3. Show Areas\n";
    std::cout << "0. Exit\n";
}

int main() {
    ShapeManager shapeManager;
    int choice;

    do {
        showMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            double radius;
            std::cout << "Enter circle radius: ";
            std::cin >> radius;
            shapeManager.addShape(std::make_shared<Circle>(radius));
        }
        else if (choice == 2) {
            double width, height;
            std::cout << "Enter rectangle width and height: ";
            std::cin >> width >> height;
            shapeManager.addShape(std::make_shared<Rectangle>(width, height));
        }
        else if (choice == 3) {
            shapeManager.showAreas();
        }

    } while (choice != 0);

    return 0;
}
