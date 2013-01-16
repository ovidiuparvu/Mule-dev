#ifndef STRINGMANIPULATOR_HPP_
#define STRINGMANIPULATOR_HPP_

#include <string>
#include <vector>
#include <sstream>

#define DIR_SEPARATOR '/'

using namespace std;

namespace multiscale {


	class StringManipulator {

	public:
		static string 			filenameFromPath  (string& filepath);
		static string 			replace 		  (string& initialString,
							   	       	   	   	   string  replaceWhat,
							   	       	   	   	   string  replaceTo);
		template <class T>
		static string 			toString 		  (T number);
		static vector<string> 	split			  (string initialString,
												   string delimiter);

	};

};

// Convert an instance of type T to a string
template <class T>
string multiscale::StringManipulator::toString(T number) {
	ostringstream stringStream;

	stringStream << number;

	return stringStream.str();
}


#endif
