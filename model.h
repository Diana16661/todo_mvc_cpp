#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <sqlite3.h>

namespace model {

    struct Todo {
        int id;
        std::string title;
    };

    class TodoModel {
    public:
        TodoModel();
        ~TodoModel();
        void add_todo(const std::string& title);
        void delete_todo(int id);
        std::vector<Todo> get_todos();

    private:
        sqlite3* db;
        void open_db();
        void close_db();
    };

} // namespace model

#endif // MODEL_H
