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

#include "src/argument_parser.h"
#include "src/database.h"
#include "src/import.h"

const std::string MODE_IMPORT = "import";

const std::string DATA_DIR = "dataset/";
const std::string DATABASE_FILE = DATA_DIR  + "database.db";

void import_images() {
  
};

int main(int argc, char* argv[]) {
  Arguments opt = parse_args(argc, argv);
  if (opt.mode == MODE_IMPORT) {
    import_images();
  } 
  // else {
  //   throw std::invalid_argument("Unhandled mode: " + opt.mode);
  // }
  
  setup_db(DATABASE_FILE);
  /*myDatabase.connect_to_database();*/
  /*myDatabase.execute_query("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT, age INTEGER);");*/
  /*myDatabase.execute_query("INSERT INTO users (name, age) VALUES ('euan', 25);");*/
  /*myDatabase.execute_query("SELECT * FROM users;");*/
  return 0;
}
