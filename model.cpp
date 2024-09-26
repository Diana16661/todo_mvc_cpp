#include "model.h"
#include <iostream>

namespace model {

    TodoModel::TodoModel() {
        open_db();
    }

    TodoModel::~TodoModel() {
        close_db();
    }

    void TodoModel::open_db() {
        if (sqlite3_open("todo.db", &db)) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            exit(1);
        }

        const char* sql = "CREATE TABLE IF NOT EXISTS todos ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "title TEXT NOT NULL"
            ");";
        char* errmsg = 0;
        if (sqlite3_exec(db, sql, 0, 0, &errmsg) != SQLITE_OK) {
            std::cerr << "SQL error: " << errmsg << std::endl;
            sqlite3_free(errmsg);
            exit(1);
        }
    }

    void TodoModel::close_db() {
        sqlite3_close(db);
    }

    void TodoModel::add_todo(const std::string& title) {
        const char* sql = "INSERT INTO todos (title) VALUES (?);";
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
        sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    void TodoModel::delete_todo(int id) {
        const char* sql = "DELETE FROM todos WHERE id = ?;";
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    std::vector<Todo> TodoModel::get_todos() {
        const char* sql = "SELECT id, title FROM todos;";
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

        std::vector<Todo> todos;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Todo todo;
            todo.id = sqlite3_column_int(stmt, 0);
            todo.title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            todos.push_back(todo);
        }
        sqlite3_finalize(stmt);
        return todos;
    }

} // namespace model
