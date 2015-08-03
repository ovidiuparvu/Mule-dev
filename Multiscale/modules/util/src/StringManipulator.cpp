#include "multiscale/util/StringManipulator.hpp"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

using namespace multiscale;


unsigned long StringManipulator::count(char searchChar, const std::string &inputString) {
    std::size_t     nrOfCharacters  = inputString.size();
    unsigned long   nrOfOccurrences = 0;

    for (std::size_t i = 0; i < nrOfCharacters; i++) {
        if (inputString[i] == searchChar) {
            nrOfOccurrences++;
        }
    }

    return nrOfOccurrences;
}

std::string StringManipulator::escapeCarriageReturns(const std::string &initialString) {
    return (replace(initialString, "\r", "\\r"));
}

std::string StringManipulator::filenameFromPath(const std::string &filepath) {
    unsigned int position = filepath.find_last_of(DIR_SEPARATOR);

    if (position != std::string::npos) {
        return filepath.substr(position + 1, std::string::npos);
    }

    return filepath;
}

std::string StringManipulator::replace(const std::string &initialString, const std::string &replaceWhat,
                                       const std::string &replaceWith) {
    size_t index = initialString.find(replaceWhat);
    std::string initialStringCopy = initialString;

    while (index != std::string::npos) {
        initialStringCopy.replace(initialStringCopy.find(replaceWhat), replaceWhat.length(), replaceWith);

        index = initialStringCopy.find(replaceWhat);
    }

    return initialStringCopy;
}

std::vector<std::string> StringManipulator::split(const std::string &initialString,
                                                  const std::string &delimiter) {
    std::vector<std::string> tokens;

    return (
        boost::split(
            tokens,
            initialString,
            boost::is_any_of(delimiter)
        )
    );
}

std::string StringManipulator::trimRight(std::string &inputString) {
    inputString.erase(
        std::find_if(
            inputString.rbegin(),
            inputString.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))
        ).base(),
        inputString.end()
   );

   return inputString;
}

std::string StringManipulator::trimRight(const std::string &inputString) {
    std::string trimmedString = inputString;

    trimRight(trimmedString);

    return trimmedString;
}


namespace multiscale {

    template <>
    unsigned long StringManipulator::convert<unsigned long>(const std::string &inputString) {
        return std::stoul(inputString);
    }

    template <>
    long StringManipulator::convert<long>(const std::string &inputString) {
        return std::stol(inputString);
    }

    template <>
    int StringManipulator::convert<int>(const std::string &inputString) {
        return std::stoi(inputString);
    }

    template <>
    float StringManipulator::convert<float>(const std::string &inputString) {
        return std::stof(inputString);
    }

    template <>
    double StringManipulator::convert<double>(const std::string &inputString) {
        return std::stod(inputString);
    }

};


// Constants
const char StringManipulator::DIR_SEPARATOR = '/';

const std::string StringManipulator::ERR_INVALID_CONVERSION_BEGIN   = "The provided string (";
const std::string StringManipulator::ERR_INVALID_CONVERSION_MIDDLE  = ") could not be converted to a ";
const std::string StringManipulator::ERR_INVALID_CONVERSION_END     = ". Please change.";
