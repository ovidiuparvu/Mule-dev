#ifndef CARTESIANTOCONCENTRATIONSCONVERTER_HPP_
#define CARTESIANTOCONCENTRATIONSCONVERTER_HPP_

#include <string>
#include <vector>

using namespace std;

#define ERR_CONC                "All concentrations have to be between 0 and 1."
#define ERR_NEG_DIMENSION       "The dimensions N and M must be non-negative."
#define ERR_NEG_SIM_TIME        "The simulation time must be non-negative."
#define ERR_IN_EXTRA_DATA       "The input file contains more data than required."

#define OUTPUT_FILE_EXTENSION   ".out"

#define RADIUS_MIN              0.001
#define RADIUS_MAX              0.3

// Scale the values of the rectangular geometry grid cells

namespace multiscale {

    namespace video {

        class CartesianToConcentrationsConverter {

            private:

                vector<double>  concentrations;

                unsigned long   height;
                unsigned long   width;
                double          simulationTime;

                string inputFilepath;
                string outputFilepath;

            public:

                CartesianToConcentrationsConverter (string inputFilepath, string outputFilepath);
                ~CartesianToConcentrationsConverter();

                void convert();

            private:

                void readInputData              () throw (string);
                void readHeaderLine             (ifstream& fin) throw (string);
                void readConcentrations         (ifstream& fin) throw (string);
                void outputResults              ();

        };

    };

};

#endif
