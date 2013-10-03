#ifndef RECTANGULARENTITYCSVTOINPUTFILESCONVERTER_HPP
#define RECTANGULARENTITYCSVTOINPUTFILESCONVERTER_HPP

#include "multiscale/util/NumberIterator.hpp"
#include "multiscale/util/iterator/NumberIteratorType.hpp"

#include <string>
#include <vector>

using namespace std;


namespace multiscale {

    namespace video {

        //! Csv entity file to input file converter considering cartesian coordinates
        class RectangularEntityCsvToInputFilesConverter {

            private:

                string inputFilepath;   /*!< Path to the input file */
                string outputFilepath;  /*!< Path to the output file */

                unsigned int height;            /*!< Height of the grid */
                unsigned int width;             /*!< Width of the grid */
                unsigned int nrOfEntities;      /*!< Number of entities */

                unsigned int maxNrOfEntitiesPerPosition; /*!< The maximum number of entities per position */

                NumberIterator* entitiesIterator;   /*!< Iterator over the number of rows */

            public:

                RectangularEntityCsvToInputFilesConverter (const string &inputFilepath,
                                                           const string &outputFilepath,
                                                           unsigned int height,
                                                           unsigned int width,
                                                           unsigned int nrOfEntities,
                                                           unsigned int maxNrOfEntitiesPerPosition,
                                                           NumberIteratorType numberIteratorType);
                ~RectangularEntityCsvToInputFilesConverter();

                //! Start the conversion
                void convert();

            private:

                //! Initialise the input file stream over the given input file
                /*!
                 * \param fin Input file stream
                 */
                void initInputFile(ifstream &fin);


                //! Initialise the output file with the given index and simulation time
                /*!
                 * \param fout Output file stream
                 * \param index Index of the output file
                 * \param simulationTime Simulation time
                 */
                void initOutputFile(ofstream &fout, unsigned int index, double &simulationTime);

                //! Initialise the iterators considering the given number iterator type
                /*!
                 * \param numberIteratorType The type of the number iterator
                 */
                void initIterators(const NumberIteratorType &numberIteratorType);

                //! Check if the maximum number of entities per position is a non-zero natural number
                void validateMaxNrOfEntitiesPerPosition();

                //! Validate the input
                /*!
                 * \param fin Input file stream
                 */
                void validateInput(ifstream &fin);

                //! Validate the provided line identified by a line number
                /*!
                 * \param line Line from input file
                 * \param lineNumber Number of the line
                 */
                void validateInputLine(const string &line, unsigned int lineNumber);

                //! Process the input file
                /*!
                 * Read the concentrations and normalise them if it is the case.
                 *
                 * \param fin Input file stream
                 */
                void processInputFile(ifstream &fin);

                //! Process the provided line
                /*!
                 * \param line Line
                 * \param outputIndex Index integrated in the name of the output file
                 */
                void processLine(const string &line, unsigned int outputIndex);

                //! Split the line in coordinates and return the grid of size height * width showing the position of the entities
                /*!
                 * The number of entities per grid position is normalised to the range [0, 1]
                 *
                 * \param line Line
                 * \param simulationTime Simulation time associated with the line
                 */
                vector<double> splitLineInCoordinates(const string &line, double &simulationTime);

                //! Compute the simulation time from the given token and check if it is valid
                /*!
                 * \param token Token (string)
                 */
                double computeSimulationTime(const string &token);

                //! Compute the coordinate from the given string and check if it is valid
                /*!
                 * \param token Token (string)
                 * \param isOxCoordinate Flag which indicates if the coordinate corresponds to Ox axis or not
                 */
                unsigned int computeCoordinate(const string &token, bool isOxCoordinate);

                //! Check if the simulation time is valid
                /*!
                 * \param token Token (string)
                 * \param lineNumber Number of the line
                 */
                void validateSimulationTime(const string &token, unsigned int lineNumber);

                //! Check if the coordinate is valid
                /*!
                 * \param token Token (string)
                 * \param lineNumber Number of the line
                 * \param isOxCoordinate Flag which indicates if the coordinate corresponds to Ox axis or not
                 */
                void validateCoordinate(const string &token, unsigned int lineNumber, bool isOxCoordinate);

                //! Check if the entities grid contains only values between zero and one
                /*!
                 * \param entitiesGrid The grid of entities
                 */
                void validateEntitiesGrid(const vector<double> &entitiesGrid);

            private:

                // Constants
                static const string OUTPUT_EXTENSION;
                static const string OUTPUT_SEPARATOR;
                static const string OUTPUT_FILE_SEPARATOR;
                static const string INPUT_FILE_SEPARATOR;

                static const string ERR_INVALID_NR_ENTITIES;
                static const string ERR_INVALID_OX_COORDINATE;
                static const string ERR_INVALID_OY_COORDINATE;
                static const string ERR_MAX_NR_ENTITIES;
                static const string ERR_NR_COORDINATES;
                static const string ERR_NEG_SIM_TIME;
                static const string ERR_INPUT_OPEN;
                static const string ERR_INVALID_VALUE_LINE;
                static const string ERR_INVALID_VALUE_TOKEN;


        };

    };

};

#endif
