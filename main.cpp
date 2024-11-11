//
// Euan Williams: 03/11/2024
//
// For importing, storing and managing images and their respective metadata.
//
#include <iostream>
#include <filesystem>

#include "src/argument_parser.h"
#include "src/database.h"
#include "src/import.h"

const std::string MODE_IMPORT = "import";

const std::string DATA_DIR = "dataset/";
const std::string DATABASE_FILE = DATA_DIR  + "database.db";
const std::string IMAGE_DIR = DATA_DIR + "images/";


void validate_import_args (Arguments opt) {
  if (opt.directory == std::nullopt) {
    throw std::invalid_argument("--directory cannot be null for mode import.");
  };

  if (opt.source == std::nullopt) {
    throw std::invalid_argument("--source cannot be null for mode import.");
  };
};


// For importing images from a directory on the local disk.
void import_images(Arguments opt) {
  validate_import_args(opt);
  ImageImporter image_importer = ImageImporter(DATABASE_FILE);

  std::vector<ImageToImport> images_to_import = {};
  for (const auto & entry : std::filesystem::directory_iterator(opt.directory.value())) {
    std::cout << "Creating image to import from " << entry.path() << std::endl;
    images_to_import.push_back(ImageToImport(entry.path().string(), opt.source.value()));
  }

  image_importer.import_images(images_to_import);
};


int main(int argc, char* argv[]) {
  Arguments opt = parse_args(argc, argv);
  if (opt.mode == MODE_IMPORT) {
    import_images(opt);
  }
  return 0;
}
