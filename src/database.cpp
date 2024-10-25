/**
 *
 * @file databse.cpp
 *
 * @brief a wrapper around sqlite, for interfacing with the local database.
 *
 * @ingroup image-store
 *
 * @author Euan Williams
 *
 */
#include <iostream>
#include <string>
#include <sqlite3.h>

class DatabaseInterface {
  private:
    sqlite3* database;

  public:
    std::string database_name;
    DatabaseInterface(std::string database_name) {
      this->database_name = database_name;
    }

    void connect_to_database() {
      sqlite3* database;
      int error = sqlite3_open(database_name.c_str(), &database);
      this->database = database;

      if (error) {
          std::cerr << "Can't open database: " << sqlite3_errmsg(database) << std::endl;
      } else {
          std::cout << "Opened database " << database_name << " successfully" << std::endl;
      }
      sqlite3_close(database);
    };

    void query_database() {

    }

};


