#include "multiscale/exception/InvalidInputException.hpp"
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

    return isValidFilePath(filePath);
}

bool Filesystem::isValidFilePath(const std::string &path, const std::string &extension) {
    fs::path filePath(path);

    if (isValidFilePath(filePath)) {
        return (filePath.extension().compare(extension) == 0);
    }

    return false;
}

std::string Filesystem::nativeFormatFilePath(const std::string &path) {
    fs::path filePath(path);

    if (!fs::exists(filePath)) {
        MS_throw(
            InvalidInputException,
            (ERR_INVALID_PATH_BEGIN + path + ERR_INVALID_PATH_END)
        );
    }

    return fs::canonical(filePath).string();
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

bool Filesystem::isValidFilePath(const fs::path &path) {
    if (fs::exists(path)) {
        return (fs::is_regular_file(path));
    }

    return false;
}


// Constants
const std::string Filesystem::ERR_INVALID_PATH_BEGIN = "The given input file path (";
const std::string Filesystem::ERR_INVALID_PATH_END   = ") does not exist or does not point to a regular file. Please change.";
