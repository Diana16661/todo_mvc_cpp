#include <iostream>
#include <vector>
#include <memory>

class IShape {
public:
    virtual ~IShape() = default;
    virtual double area() const = 0;
};

class Circle : public IShape {
public:
    Circle(double radius) : radius(radius) {}

    double area() const override {
        return 3.14159 * radius * radius;
    }

private:
    double radius;
};

class Rectangle : public IShape {
public:
    Rectangle(double width, double height) : width(width), height(height) {}

    double area() const override {
        return width * height; 
    }

private:
    double width;
    double height;
};


class IShapeManager {
public:
    virtual ~IShapeManager() = default;
    virtual void addShape(std::shared_ptr<IShape> shape) = 0; 
    virtual void showAreas() const = 0;
};


class ShapeManager : public IShapeManager {
public:
    void addShape(std::shared_ptr<IShape> shape) override {
        shapes.push_back(shape);
    }

    void showAreas() const override {
        for (const auto& shape : shapes) {
            std::cout << "Area: " << shape->area() << "\n";
        }
    }

private:
    std::vector<std::shared_ptr<IShape>> shapes;
};


void showMenu() {
    std::cout << "1. Add Circle\n";
    std::cout << "2. Add Rectangle\n";
    std::cout << "3. Show Areas\n";
    std::cout << "0. Exit\n";
}

int main() {
    std::shared_ptr<IShapeManager> shapeManager = std::make_shared<ShapeManager>(); 
    int choice;

    do {
        showMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            double radius;
            std::cout << "Enter circle radius: ";
            std::cin >> radius;
            shapeManager->addShape(std::make_shared<Circle>(radius));
        }
        else if (choice == 2) {
            double width, height;
            std::cout << "Enter rectangle width and height: ";
            std::cin >> width >> height;
            shapeManager->addShape(std::make_shared<Rectangle>(width, height));
        }
        else if (choice == 3) {
            shapeManager->showAreas();
        }

    } while (choice != 0);

    return 0;
}
