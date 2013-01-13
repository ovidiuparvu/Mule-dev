#ifndef STRINGMANIPULATOR_HPP_
#define STRINGMANIPULATOR_HPP_

#include <string>
#include <vector>

#define DIR_SEPARATOR '/'

using namespace std;

namespace multiscale {

	class StringManipulator {

	public:
		static string 			filenameFromPath  (string& filepath);
		static string 			replace 		  (string& initialString,
							   	       	   	   	   string  replaceWhat,
							   	       	   	   	   string  replaceTo);
		static string 			toString		  (int number);
		static string 			toString		  (unsigned int number);
		static string 			toString		  (double number);
		static vector<string> 	split			  (string initialString,
												   string delimiter);

	};

};


#endif
