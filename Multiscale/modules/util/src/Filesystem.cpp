#include "multiscale/util/Filesystem.hpp"

using namespace multiscale;


bool Filesystem::isValidFolderPath(const std::string &path) {
    fs::path folderPath(path);

    if (fs::exists(folderPath)) {
        return (fs::is_directory(folderPath));
    }

    return false;
}

bool Filesystem::isValidFilePath(const std::string &path) {
    fs::path filePath(path);

    if (fs::exists(filePath)) {
        return (fs::is_regular_file(filePath));
    }

    return false;
}

std::vector<std::string> Filesystem::getFilesInFolder(const std::string &folderPath,
                                                      const std::string &extension) {
    std::vector<std::string> filesWithExtension;
    std::vector<fs::path> files;

    if (isValidFolderPath(folderPath)) {
        std::copy(fs::directory_iterator(folderPath), fs::directory_iterator(), std::back_inserter(files));

        for (const fs::path &filePath : files) {
            if (filePath.extension().compare(extension) == 0) {
                filesWithExtension.push_back(filePath.string());
            }
        }
    }

    return filesWithExtension;
}
