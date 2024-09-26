#include <iostream>
#include <vector>
#include <memory>


class IShape {
public:
    virtual ~IShape() = default;
    virtual double area() const = 0; 
};

class IDrawable {
public:
    virtual ~IDrawable() = default;
    virtual void draw() const = 0; 
};


class Circle : public IShape, public IDrawable {
public:
    Circle(double radius) : radius(radius) {}

    double area() const override {
        return 3.14159 * radius * radius; 
    }

    void draw() const override {
        std::cout << "Drawing a Circle with radius: " << radius << "\n"; 
    }

private:
    double radius;
};


class Rectangle : public IShape, public IDrawable {
public:
    Rectangle(double width, double height) : width(width), height(height) {}

    double area() const override {
        return width * height;
    }

    void draw() const override {
        std::cout << "Drawing a Rectangle with width: " << width << " and height: " << height << "\n";
    }

private:
    double width;
    double height;
};


class ShapeManager {
public:
    void addShape(std::shared_ptr<IShape> shape) {
        shapes.push_back(shape);
    }

    void showAreas() const {
        for (const auto& shape : shapes) {
            std::cout << "Area: " << shape->area() << "\n"; 
        }
    }

    void drawShapes() const {
        for (const auto& shape : shapes) {
            auto drawable = std::dynamic_pointer_cast<IDrawable>(shape);
            if (drawable) {
                drawable->draw();
            }
        }
    }

private:
    std::vector<std::shared_ptr<IShape>> shapes;
};


void showMenu() {
    std::cout << "1. Add Circle\n";
    std::cout << "2. Add Rectangle\n";
    std::cout << "3. Show Areas\n";
    std::cout << "4. Draw Shapes\n";
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
        else if (choice == 4) {
            shapeManager.drawShapes();
        }

    } while (choice != 0);

    return 0;
}
