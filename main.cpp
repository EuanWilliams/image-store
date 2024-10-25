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
  return 0;
}
