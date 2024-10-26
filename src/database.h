/**
 *
 * @file databse.cpp
 *
 * @brief a wrapper around sqlite, for interfacing with the local database.
 *
 * @ingroup image-store
 *
 * @author Euan williams
 *
 */
#pragma once

#include <iostream>
#include <string>
#include <sqlite3.h>

class DatabaseInterface {
  public:
    std::string database_file;
    sqlite3* database;

    DatabaseInterface(std::string database_file) {
      this->database_file = database_file;
    }
  
    bool connect_to_database() {
        int error = sqlite3_open(database_file.c_str(), &database);
        if (error) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(database) << std::endl;
            return false;
        } else {
            std::cout << "Opened database " << database_file << " successfully" << std::endl;
            return true;
        }
    }

    // query execution method
    void execute_query(const std::string &query) {
        char* error_message = nullptr;
        
        int result = sqlite3_exec(database, query.c_str(), callback, nullptr, &error_message);
        
        if (result != SQLITE_OK) {
            std::cerr << "error executing query: " << error_message << std::endl;
            sqlite3_free(error_message);
        } else {
            std::cout << "query executed successfully" << std::endl;
        }
    };

    // Method to disconnect from the database
    void disconnect() {
        if (database) {
            sqlite3_close(database);
            std::cout << "Database closed successfully." << std::endl;
        }
    }

    ~DatabaseInterface() {
        disconnect();
    }

  private:
    // Callback function for query results
    static int callback(void* not_used, int argc, char** argv, char** azColName) {
        for (int i = 0; i < argc; i++) {
            std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
        }
        std::cout << std::endl;
        return 0;
    }
};

