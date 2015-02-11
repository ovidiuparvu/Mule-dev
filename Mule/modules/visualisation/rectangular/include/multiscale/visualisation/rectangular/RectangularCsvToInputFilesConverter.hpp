#ifndef RECTANGULARCSVTOINPUTFILESCONVERTER_HPP
#define RECTANGULARCSVTOINPUTFILESCONVERTER_HPP

#include "multiscale/util/NumberIterator.hpp"
#include "multiscale/util/iterator/NumberIteratorType.hpp"

#include <string>
#include <vector>


namespace multiscale {

    namespace visualisation {

        //! Csv file to input file converter considering cartesian coordinates
        class RectangularCsvToInputFilesConverter {

            private:

                std::string inputFilepath;                  /*!< Path to the input file */
                std::string outputFilepath;                 /*!< Path to the output file */

                unsigned int height;                        /*!< Height of the grid */
                unsigned int width;                         /*!< Width of the grid */
                unsigned int nrOfConcentrationsForPosition; /*!< Number of concentrations for each position */

                unsigned int concentrationsIndex;           /*!< Index of the current concentration */

                unsigned int selectedConcentrationIndex;    /*!< Index of the concentration A in case the number of
                                                                 concentrations for each position is greater than 1

                                                                 finalConcentration = A / (A1 + A2 + ... + AN), where
                                                                 N is the number of concentrations for each position
                                                            */

                bool useLogScaling;                         /*!< Flag for using logarithmic scaling for
                                                                 concentrations */

                double maximumConcentration;                /*!< The maximum concentration in the input file */

                NumberIterator* rowsIterator;               /*!< Iterator over the number of rows */
                NumberIterator* columnsIterator;            /*!< Iterator over the number of columns */

            public:

                RectangularCsvToInputFilesConverter(const std::string &inputFilepath,
                                                    const std::string &outputFilepath,
                                                    unsigned int height,
                                                    unsigned int width,
                                                    unsigned int nrOfConcentrationsForPosition,
                                                    unsigned int selectedConcentrationIndex,
                                                    bool useLogScaling,
                                                    NumberIteratorType numberIteratorType);
                ~RectangularCsvToInputFilesConverter();

                //! Start the conversion
                void convert();

            private:

                //! Initialise the input file stream over the given input file
                /*!
                 * \param fin Input file stream
                 */
                void initInputFile(std::ifstream &fin);


                //! Compute the value of member maximum concentration
                /*!
                 * \param fin Input file stream
                 */
                void initMaximumConcentration(std::ifstream &fin);

                //! Initialise the output file with the given index and simulation time
                /*!
                 * \param fout Output file stream
                 * \param index Index of the output file
                 * \param simulationTime Simulation time
                 */
                void initOutputFile(std::ofstream &fout, unsigned int index, double &simulationTime);

                //! Initialise the iterators considering the given number iterator type
                /*!
                 * \param numberIteratorType The type of the number iterator
                 */
                void initIterators(const NumberIteratorType &numberIteratorType);

                //! Validate the selected concentration index in case of more than one concentration for each position
                void validateSelectedConcentrationIndex();

                //! Validate the input
                /*!
                 * \param fin Input file stream
                 */
                void validateInput(std::ifstream &fin);

                //! Validate the provided line identified by a line number
                /*!
                 * \param line Line from input file
                 * \param lineNumber Number of the line
                 */
                void validateInputLine(const std::string &line, unsigned int lineNumber);

                //! Process the input file
                /*!
                 * Read the concentrations and normalise them if it is the case.
                 *
                 * \param fin Input file stream
                 */
                void processInputFile(std::ifstream &fin);

                //! Process the provided line
                /*!
                 * \param line Line
                 * \param outputIndex Index integrated in the name of the output file
                 */
                void processLine(const std::string &line, unsigned int outputIndex);

                //! Split the line in concentrations
                /*!
                 * \param line Line
                 * \param simulationTime Simulation time associated with the line
                 */
                std::vector<double> splitLineInConcentrations(const std::string &line, double &simulationTime);

                //! Split line into concentrations
                /*!
                 * \param concentrations Concentrations extracted from tokens
                 * \param tokens Tokens representing the line
                 * \param rowIndex Index of the current row
                 */
                void splitLineInConcentrations(std::vector<double> &concentrations,
                                               std::vector<std::string> &tokens,
                                               unsigned int rowIndex);

                //! Compute the simulation time from the given token and check if it is valid
                /*!
                 * \param token Token (string)
                 */
                double computeSimulationTime(const std::string &token);

                //! Compute the concentration for the next position
                /*!
                 * \param concentrationIndex Index of the current concentration from the vector of tokens
                 * \param tokens Vector of tokens
                 */
                double computeNextPositionConcentration(int concentrationIndex,
                                                        std::vector<std::string> &tokens);

                //! Compute the concentration from the given string
                /*!
                 * \param concentration String representing the concentration
                 */
                double computeConcentration(const std::string &concentration);

                //! Compute the non-scaled concentration from the given string
                /*!
                 * \param concentration String representing the concentration
                 */
                double computeNonScaledConcentration(const std::string &concentration);

                //! Compute the scaled concentration from the given string
                /*! Compute the scaled concentration from the given string by applying
                 *  a logit transformation to it
                 *
                 * \param concentration String representing the concentration
                 */
                double computeScaledConcentration(const std::string &concentration);

                //! Normalise the given concentration by dividing it to the maximum concentration
                /*!
                 * \param concentration The concentration
                 */
                double computeNormalisedConcentration(double concentration);

                //! Update the maximum concentration if the values from the given line are greater than it
                /*!
                 * \param line Line from input file
                 * \param maximumConcentration The maximum concentration
                 */
                void updateMaximumConcentration(const std::string &line,
                                                double &maximumConcentration);

            private:

                // Constants
                static const int         OUTPUT_PRECISION;

                static const std::string OUTPUT_EXTENSION;
                static const std::string OUTPUT_SEPARATOR;
                static const std::string OUTPUT_FILE_SEPARATOR;
                static const std::string INPUT_FILE_SEPARATOR;

                static const std::string ERR_NEG_CONCENTRATION;
                static const std::string ERR_SELECTED_CONCENTRATION_INDEX;
                static const std::string ERR_NR_CONCENTRATIONS;
                static const std::string ERR_NEG_SIM_TIME;
                static const std::string ERR_INPUT_OPEN;
                static const std::string ERR_INVALID_VALUE_LINE;
                static const std::string ERR_INVALID_VALUE_TOKEN;


        };

    };

};


#endif
