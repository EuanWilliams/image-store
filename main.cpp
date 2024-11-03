//
// Euan Williams: 03/11/2024
//
// For importing, storing and managing images and their respective metadata.
//
#include <iostream>

#include "src/argument_parser.h"
#include "src/database.h"
#include "src/import.h"

const std::string MODE_IMPORT = "import";

const std::string DATA_DIR = "dataset/";
const std::string DATABASE_FILE = DATA_DIR  + "database.db";


void import_images(Arguments opt) {
  ImageImporter image_importer = ImageImporter(DATABASE_FILE);
  std::string image_path_to_import = DATA_DIR + "fishing.jpeg";

  ImageToImport image_to_import = ImageToImport(image_path_to_import, "test");
  std::vector images_to_import = {image_to_import};
  image_importer.import_images(images_to_import);
};


int main(int argc, char* argv[]) {
  Arguments opt = parse_args(argc, argv);
  if (opt.mode == MODE_IMPORT) {
    import_images(opt);
  } 
  // else {
  //   throw std::invalid_argument("Unhandled mode: " + opt.mode);
  // }
  
  return 0;
}
