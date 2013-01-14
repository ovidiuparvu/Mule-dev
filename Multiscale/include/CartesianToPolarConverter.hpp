#ifndef CARTESIANTOPOLARCONVERTER_HPP_
#define CARTESIANTOPOLARCONVERTER_HPP_

#include "CircularSegment.hpp"

#include <string>
#include <vector>

using namespace std;

#define ERR_CONC        		"All concentrations have to be between 0 and 1."
#define ERR_NEG_DIMENSION   	"The dimensions N and M must be non-negative."
#define ERR_IN_EXTRA_DATA   	"The input file contains more data than required."

#define OUTPUT_FILE_EXTENSION 	".out"

#define RADIUS_MIN				0.001
#define RADIUS_MAX				0.3

// Class for converting from grid cells to circular segments

namespace multiscale {

    class CartesianToPolarConverter {

	private:

    	vector<CircularSegment> circularSegments;
    	vector<double>			concentrations;

    	unsigned long nrOfConcentricCircles;
    	unsigned long nrOfSectors;

    	string inputFilepath;
    	string outputFilepath;

	public:

    	CartesianToPolarConverter (string inputFilepath, string outputFilename);
		~CartesianToPolarConverter();

		void convert(bool outputToScript);

	private:

		void readInputData				() throw (string);
		void readHeaderLine				(ifstream& fin) throw (string);
		void readConcentrations			(ifstream& fin) throw (string);
		void transformToCircularSegments();
		void outputResultsAsFile		();
		void outputResultsAsScript		();

    };

};

#endif
