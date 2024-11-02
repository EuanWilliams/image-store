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
#include <filesystem>


// The version of the current schema, can be incremented when schema changes.
const int SCHEMA_VERSION = 0;


// Used for checking if the database already exists
bool file_exists(const std::filesystem::path& path, std::filesystem::file_status status = std::filesystem::file_status{}) {
    if (std::filesystem::status_known(status) ? std::filesystem::exists(status) : std::filesystem::exists(path)) {
      return true;
    }
    else {
      return false;
    }
}


class DatabaseInterface {
  public:
    std::string database_file;
    sqlite3* database;

    DatabaseInterface(std::string database_file) {
      this->database_file = database_file;
    }
  
    bool connect_to_database() {
        int error = sqlite3_open(database_file.c_str(), &database);
        std::cout << "Opening database file at " << database_file.c_str() << std::endl;
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


// Function to prepare the required tables if they dont already exist. Returns Interface to the database.
DatabaseInterface setup_db(std::string database_file) { 
  std::filesystem::path database_path = database_file;

  DatabaseInterface database = DatabaseInterface(database_file);

  // If file doesnt exist already, make it and populate tables
  if (!file_exists(database_path)) {
    std::cout << "Database file " << database_file << " doesn't already exists, making it..." << std::endl;
    database.connect_to_database();
    database.execute_query(
      "CREATE TABLE IF NOT EXISTS images ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "filepath TEXT," // Path from root directory
        "import_date INTEGER,"
        "import_source TEXT," // Location from which image was imported, EG: Euans S10
        "import_metadata TEXT DEFAULT NULL,"
        "UNIQUE (filepath)"
      ")"
    );
    std::string pragma_query = "PRAGMA user_version = " + std::to_string(SCHEMA_VERSION);
    database.execute_query(pragma_query);
  }
  else {
    std::cout << "Database file " << database_file << " found, opening" << std::endl;
    DatabaseInterface database = DatabaseInterface(database_file);
    database.connect_to_database();
    // TODO: check pragma version here. 
  }

  if (!file_exists(database_path)) {
    throw std::runtime_error("File not found.");
  }

  return database;
}

