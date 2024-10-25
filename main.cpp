/**
 *
 * @file main.cpp
 *
 * @brief main entry point for image-store
 *
 * @ingroup image-store
 *
 * @author Euan Williams
 *
*/
#include <iostream>

#include "src/database.cpp"

int main() {
  DatabaseInterface myDatabase = DatabaseInterface("test.db");
  myDatabase.connect_to_database();
  myDatabase.execute_query("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT, age INTEGER);");
  /*myDatabase.execute_query("INSERT INTO users (name, age) VALUES ('euan', 25);");*/
  myDatabase.execute_query("SELECT * FROM users;");
  return 0;
}
