#ifndef CSVTOINPUTFILESCONVERTER_HPP_
#define CSVTOINPUTFILESCONVERTER_HPP_

#include "LexicographicNumberIterator.hpp"

#include <string>
#include <vector>

#define OUTPUT_EXTENSION 		".in"
#define OUTPUT_SEPARATOR 		" "
#define OUTPUT_FILE_SEPARATOR	"_"
#define INPUT_FILE_SEPARATOR	","

#define PI						3.141592

#define ERR_NEG_CONCENTRATION   "All concentrations must be non-negative.";

using namespace std;

namespace multiscale {

	class CsvToInputFilesConverter {

	private:

		string inputFilepath;
		string outputFilepath;

		unsigned int nrOfConcentricCircles;
		unsigned int nrOfSectors;
		unsigned int nrOfConcentrationsForPosition;

		LexicographicNumberIterator circlesIterator;
		LexicographicNumberIterator sectorsIterator;

	public:

		CsvToInputFilesConverter(string inputFilepath,
							 	 string outputFilepath,
				                 unsigned int nrOfConcentricCircles,
				                 unsigned int nrOfSectors,
				                 unsigned int nrOfConcentrationsForPosition);
		~CsvToInputFilesConverter();

		void convert();

	private:

		void 			initInputFile					(ifstream& fin);
		void	 		initOutputFile					(ofstream& fout, unsigned int index);
		void	  		processLine						(string line, unsigned int outputIndex);
		vector<double>&	splitLineInConcentrations		(string line);
		double	  		computeNextPositionConcentration(unsigned int circleIndex,
				                                         int concentrationIndex,
				                                         vector<string>& tokens);


	};

};

#endif
