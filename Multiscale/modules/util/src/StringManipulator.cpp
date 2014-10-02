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

string StringManipulator::filenameFromPath(const string &filepath) {
    unsigned int position = filepath.find_last_of(DIR_SEPARATOR);

    if (position != string::npos) {
        return filepath.substr(position + 1, string::npos);
    }

    return filepath;
}

string StringManipulator::replace(const string &initialString, const string &replaceWhat, const string &replaceWith) {
    size_t index = initialString.find(replaceWhat);
    string initialStringCopy = initialString;

    while (index != string::npos) {
        initialStringCopy.replace(initialStringCopy.find(replaceWhat), replaceWhat.length(), replaceWith);

        index = initialStringCopy.find(replaceWhat);
    }

    return initialStringCopy;
}

vector<string> StringManipulator::split(const string &initialString, const string &delimiter) {
    vector<string> tokens;
    string initialStringCopy = initialString;

    return boost::split(tokens, initialStringCopy, boost::is_any_of(delimiter));
}

string StringManipulator::trimRight(string &inputString) {
    inputString.erase(
        std::find_if(
                inputString.rbegin(),
                inputString.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base()
        , inputString.end()
   );

   return inputString;
}

string StringManipulator::trimRight(const string &inputString) {
    string trimmedString = inputString;

    trimRight(trimmedString);

    return trimmedString;
}

// Constants
const char StringManipulator::DIR_SEPARATOR = '/';

const std::string StringManipulator::ERR_INVALID_CONVERSION_BEGIN   = "The provided string (";
const std::string StringManipulator::ERR_INVALID_CONVERSION_MIDDLE  = ") could not be converted to a ";
const std::string StringManipulator::ERR_INVALID_CONVERSION_END     = ". Please change.";
