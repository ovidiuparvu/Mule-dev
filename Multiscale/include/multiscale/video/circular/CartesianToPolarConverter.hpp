#ifndef CARTESIANTOPOLARCONVERTER_HPP_
#define CARTESIANTOPOLARCONVERTER_HPP_

#include "multiscale/video/circular/AnnularSector.hpp"

#include <string>
#include <vector>

using namespace std;

#define ERR_CONC                "All concentrations have to be between 0 and 1."
#define ERR_NEG_DIMENSION       "The dimensions N and M must be non-negative."
#define ERR_IN_EXTRA_DATA       "The input file contains more data than required."

#define OUTPUT_FILE_EXTENSION   ".out"

#define RADIUS_MIN              0.001
#define RADIUS_MAX              0.3

// Converter from the rectangular geometry grid cells to annular sectors

namespace multiscale {

    namespace video {

        class CartesianToPolarConverter {

            private:

                vector<AnnularSector>   annularSectors;
                vector<double>          concentrations;

                unsigned long nrOfConcentricCircles;
                unsigned long nrOfSectors;

                string inputFilepath;
                string outputFilepath;

            public:

                CartesianToPolarConverter (string inputFilepath, string outputFilepath);
                ~CartesianToPolarConverter();

                void convert(bool outputToScript);

            private:

                void readInputData              () throw (string);
                void readHeaderLine             (ifstream& fin) throw (string);
                void readConcentrations         (ifstream& fin) throw (string);
                void transformToAnnularSectors  ();
                void outputResultsAsFile        ();
                void outputResultsAsScript      ();

        };

    };

};

#endif
