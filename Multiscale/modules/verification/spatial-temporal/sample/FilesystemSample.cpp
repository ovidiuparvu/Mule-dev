#include <iostream>
#include <boost/filesystem.hpp>

using namespace boost::filesystem;

// TODO: Remove


// Main function
int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Usage: Filesystem path" << std::endl;

    return 1;
  }

  path folderPath(argv[1]);

  if (exists(folderPath)) {
      if (is_directory(folderPath)) {
          std::cout << "The provided path points to a folder and this folder contains the following xml files: " << std::endl;

          std::vector<path> files;

          copy(directory_iterator(folderPath), directory_iterator(), std::back_inserter(files));

          for (const path &filePath : files) {
              if (filePath.extension() == ".xml") {
                  std::cout << filePath.string() << std::endl;
              }
          }
      } else {
          std::cout << "The provided path does not point to a folder." << std::endl;
      }
  } else {
      std::cout << "The provided path does not exist." << std::endl;
  }

  return 0;
}
