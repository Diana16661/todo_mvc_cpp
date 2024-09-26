#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Task {
public:
    Task(int id, const std::string& title) : id(id), title(title) {}
    virtual ~Task() = default;
    virtual void display() const {
        std::cout << id << ": " << title;
    }
    int getId() const { return id; }

private:
    int id;
    std::string title;
};

class TaskWithDeadline : public Task {
public:
    TaskWithDeadline(int id, const std::string& title, const std::string& deadline)
        : Task(id, title), deadline(deadline) {}
    void display() const override {
        Task::display();
        std::cout << " [Deadline: " << deadline << "]";
    }

private:
    std::string deadline;
};

class TaskManager {
public:
    void addTask(std::shared_ptr<Task> task) {
        tasks.push_back(task);
    }
    void removeTask(int id) {
        tasks.erase(std::remove_if(tasks.begin(), tasks.end(), [id](const std::shared_ptr<Task>& task) {
            return task->getId() == id;
            }), tasks.end());
    }
    void showTasks() const {
        for (const auto& task : tasks) {
            task->display();
            std::cout << "\n";
        }
    }

private:
    std::vector<std::shared_ptr<Task>> tasks;
};

// Функція для виведення меню
void showMenu() {
    std::cout << "1. Add Task\n";
    std::cout << "2. Add Task with Deadline\n";
    std::cout << "3. Remove Task\n";
    std::cout << "4. Show Tasks\n";
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
            taskManager.addTask(std::make_shared<Task>(id, title));
        }
        else if (choice == 2) {
            int id;
            std::string title, deadline;
            std::cout << "Enter task ID: ";
            std::cin >> id;
            std::cin.ignore();
            std::cout << "Enter task title: ";
            std::getline(std::cin, title);
            std::cout << "Enter task deadline: ";
            std::getline(std::cin, deadline);
            taskManager.addTask(std::make_shared<TaskWithDeadline>(id, title, deadline));
        }
        else if (choice == 3) {
            int id;
            std::cout << "Enter task ID to remove: ";
            std::cin >> id;
            taskManager.removeTask(id);
        }
        else if (choice == 4) {
            taskManager.showTasks();
        }

    } while (choice != 0);

    return 0;
}
