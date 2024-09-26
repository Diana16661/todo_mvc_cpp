#include <iostream>
#include <vector>
#include <string>
#include <memory>
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

class TaskModel {
public:
    void addTask(const std::string& title) {
        int id = tasks.size() + 1;
        tasks.emplace_back(std::make_shared<Task>(id, title));
    }

    void removeTask(int id) {
        tasks.erase(std::remove_if(tasks.begin(), tasks.end(),
            [id](const std::shared_ptr<Task>& task) {
                return task->getId() == id;
            }), tasks.end());
    }

    const std::vector<std::shared_ptr<Task>>& getTasks() const {
        return tasks;
    }

private:
    std::vector<std::shared_ptr<Task>> tasks;
};

class TaskView {
public:
    void showTasks(const std::vector<std::shared_ptr<Task>>& tasks) const {
        std::cout << "Tasks:\n";
        for (const auto& task : tasks) {
            std::cout << task->getId() << ": " << task->getTitle() << "\n";
        }
    }
};

class TaskController {
public:
    TaskController(TaskModel& model, TaskView& view) : model(model), view(view) {}

    void addTask(const std::string& title) {
        model.addTask(title);
        view.showTasks(model.getTasks());
    }

    void removeTask(int id) {
        model.removeTask(id);
        view.showTasks(model.getTasks());
    }

private:
    TaskModel& model;
    TaskView& view;
};

int main() {
    TaskModel model;
    TaskView view;
    TaskController controller(model, view);

    int choice;
    do {
        std::cout << "1. Add Task\n";
        std::cout << "2. Remove Task\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string title;
            std::cout << "Enter task title: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            controller.addTask(title);
        }
        else if (choice == 2) {
            int id;
            std::cout << "Enter task ID to remove: ";
            std::cin >> id;
            controller.removeTask(id);
        }
    } while (choice != 0);

    return 0;
}
