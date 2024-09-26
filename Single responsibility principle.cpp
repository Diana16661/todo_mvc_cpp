#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


class Task {
public:
    Task(int id, const std::string& title) : id(id), title(title) {}
    int getId() const { return id; }
    std::string getTitle() const { return title; }

private:
    int id;
    std::string title;
};


class TaskManager {
public:
    void addTask(const Task& task) { tasks.push_back(task); }
    void removeTask(int id) {
        tasks.erase(std::remove_if(tasks.begin(), tasks.end(), [id](const Task& task) {
            return task.getId() == id;
            }), tasks.end());
    }
    std::vector<Task> getTasks() const { return tasks; }

private:
    std::vector<Task> tasks;
};

// Функція для виведення меню
void showMenu() {
    std::cout << "1. Add Task\n";
    std::cout << "2. Remove Task\n";
    std::cout << "3. Show Tasks\n";
    std::cout << "0. Exit\n";
}

int main() {
    TaskManager taskManager;
    int choice;

    do {
        showMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            int id;
            std::string title;
            std::cout << "Enter task ID: ";
            std::cin >> id;
            std::cin.ignore();
            std::cout << "Enter task title: ";
            std::getline(std::cin, title);
            taskManager.addTask(Task(id, title));
        }
        else if (choice == 2) {
            int id;
            std::cout << "Enter task ID to remove: ";
            std::cin >> id;
            taskManager.removeTask(id);
        }
        else if (choice == 3) {
            auto tasks = taskManager.getTasks();
            for (const auto& task : tasks) {
                std::cout << task.getId() << ": " << task.getTitle() << "\n";
            }
        }

    } while (choice != 0);

    return 0;
}
