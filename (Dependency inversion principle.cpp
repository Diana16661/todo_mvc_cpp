#include <iostream>
#include <vector>
#include <memory>

// Інтерфейс для форм
class IShape {
public:
    virtual ~IShape() = default;
    virtual double area() const = 0; // Чисто віртуальна функція для обчислення площі
};

// Клас Circle, який реалізує інтерфейс IShape
class Circle : public IShape {
public:
    Circle(double radius) : radius(radius) {}

    double area() const override {
        return 3.14159 * radius * radius; // Обчислення площі кола
    }

private:
    double radius;
};

// Клас Rectangle, який також реалізує інтерфейс IShape
class Rectangle : public IShape {
public:
    Rectangle(double width, double height) : width(width), height(height) {}

    double area() const override {
        return width * height; // Обчислення площі прямокутника
    }

private:
    double width;
    double height;
};

// Інтерфейс для менеджера форм
class IShapeManager {
public:
    virtual ~IShapeManager() = default;
    virtual void addShape(std::shared_ptr<IShape> shape) = 0; // Додавання форми
    virtual void showAreas() const = 0; // Показати площі
};

// Клас ShapeManager, який реалізує інтерфейс IShapeManager
class ShapeManager : public IShapeManager {
public:
    void addShape(std::shared_ptr<IShape> shape) override {
        shapes.push_back(shape);
    }

    void showAreas() const override {
        for (const auto& shape : shapes) {
            std::cout << "Area: " << shape->area() << "\n"; // Виведення площі кожної форми
        }
    }

private:
    std::vector<std::shared_ptr<IShape>> shapes; // Вектор форм
};

// Функція для виведення меню
void showMenu() {
    std::cout << "1. Add Circle\n";
    std::cout << "2. Add Rectangle\n";
    std::cout << "3. Show Areas\n";
    std::cout << "0. Exit\n";
}

int main() {
    std::shared_ptr<IShapeManager> shapeManager = std::make_shared<ShapeManager>(); // Використання абстракції для менеджера форм
    int choice;

    do {
        showMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            double radius;
            std::cout << "Enter circle radius: ";
            std::cin >> radius;
            shapeManager->addShape(std::make_shared<Circle>(radius)); // Додавання кола
        }
        else if (choice == 2) {
            double width, height;
            std::cout << "Enter rectangle width and height: ";
            std::cin >> width >> height;
            shapeManager->addShape(std::make_shared<Rectangle>(width, height)); // Додавання прямокутника
        }
        else if (choice == 3) {
            shapeManager->showAreas(); // Виведення площ
        }

    } while (choice != 0);

    return 0;
}
