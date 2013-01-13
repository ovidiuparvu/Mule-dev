#include "../include/StringManipulator.hpp"

#include <sstream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

using namespace multiscale;


// Get the filename from an absolute/relative path
string StringManipulator::filenameFromPath(string& filepath) {
	unsigned int position = filepath.find_last_of(DIR_SEPARATOR);

	if (position != string::npos) {
		return filepath.substr(position + 1, string::npos);
	}

	return filepath;
}

// Find and replace a part of a string with another string
string StringManipulator::replace(string& initialString,
		  	  	  	  	  	  	  string  replaceWhat,
		  	  	  	  	  	  	  string  replaceWith) {
	size_t index = initialString.find(replaceWhat);

	while (index != string::npos) {
		initialString.replace(initialString.find(replaceWhat), replaceWhat.length(), replaceWith);

		index = initialString.find(replaceWhat);
	}

	return initialString;
}

// Convert an integer to a string
string StringManipulator::toString(int number) {
	ostringstream stringStream;

	stringStream << number;

	return stringStream.str();
}

// Convert an unsigned integer to a string
string StringManipulator::toString(unsigned int number) {
	ostringstream stringStream;

	stringStream << number;

	return stringStream.str();
}

// Convert an integer to a string
string StringManipulator::toString(double number) {
	ostringstream stringStream;

	stringStream << number;

	return stringStream.str();
}

// Split a string and return all tokens as a new vector
vector<string>& StringManipulator::split(string initialString,
										 string delimiter) {
	vector<string> tokens;

	boost::split(tokens, initialString, boost::is_any_of(delimiter));

	return tokens;
}
