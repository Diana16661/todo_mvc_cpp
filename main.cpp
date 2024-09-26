#include <iostream>
#include "model.h"

void show_menu() {
    std::cout << "1. Add To-Do" << std::endl;
    std::cout << "2. Delete To-Do" << std::endl;
    std::cout << "3. Show To-Dos" << std::endl;
    std::cout << "0. Exit" << std::endl;
}

int main() {
    model::TodoModel model;
    int choice;

    do {
        show_menu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::cin.ignore();
            std::string title;
            std::cout << "Enter title: ";
            std::getline(std::cin, title);
            model.add_todo(title);
        }
        else if (choice == 2) {
            int id;
            std::cout << "Enter ID to delete: ";
            std::cin >> id;
            model.delete_todo(id);
        }
        else if (choice == 3) {
            std::vector<model::Todo> todos = model.get_todos();
            for (auto& todo : todos) {
                std::cout << todo.id << ": " << todo.title << std::endl;
            }
        }

    } while (choice != 0);

    return 0;
}
