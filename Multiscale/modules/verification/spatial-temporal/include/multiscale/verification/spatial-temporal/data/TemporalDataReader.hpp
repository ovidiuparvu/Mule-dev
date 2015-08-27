#ifndef TEMPORALDATAREADER_HPP
#define TEMPORALDATAREADER_HPP

#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"

#include <fstream>
#include <string>


namespace multiscale {

    namespace verification {

        //! Class for reading (non-spatial) time series data from a .csv file
        /*!
         * The format of the .csv input files is:
         *     Time,Observable 1,Observable 2, ..., Observable n
         *     T1, O11, O21, ..., On1
         *     T2, O12, O22, ..., On2
         *     ...
         *     Tm, O1m, O2m, ..., Onm
         * where the first line contains the name of the observable variables (e.g. species)
         * and the subsequent lines the values of these variables for a given time point
         * (Ti, 1 <= i <= m)
         */
        class TemporalDataReader {

            private:

                std::string
                    filePath;                   /*!< The path to the input file */

                std::vector<std::string>
                    observableVariables;        /*!< The names of the observable variables */
                std::vector<NumericStateVariableId>
                    numericStateVariableIds;    /*!< The ids of the numeric state variables */

                unsigned long
                    currentLineNumber;          /*!< The current input file line number */

            public:

                TemporalDataReader();

                //! Read the data from the input file and use it to construct a spatial temporal trace
                /*!
                 * \param filePath  The input file path
                 */
                SpatialTemporalTrace readTimeSeriesFromFile(const std::string &filePath);

            private:

                //! Read the data from the input file and use it to construct a spatial temporal trace
                /*!
                 * \param inputFile The input file represented as a collection of lines
                 */
                SpatialTemporalTrace readTimeSeriesFromFile(const std::vector<std::string> &inputFile);

                //! Check if the input file is valid i.e. it contains at least one line
                /*! If the input file does not contain at least one line, then it does not contain a header line,
                 *  and an exception is thrown.
                 *
                 * \param inputFile     The input file represented as a collection of lines
                 */
                bool isValidInputFile(const std::vector<std::string> &inputFile);

                //! Read the header row from the input file
                /*!
                 * \param inputFile The input file represented as a collection of lines
                 */
                void readInputFileHeader(const std::vector<std::string> &inputFile);

                //! Create numeric state variable ids from the observable variables
                void createNumericStateVariableIdsFromObservableVariables();

                //! Validate the observable variables
                /*!
                 * The observable variables collection is valid if it contains two or more elements.
                 */
                void validateObservableVariables();

                //! Read the contents (excluding header row) from the input file
                /*!
                 * \param inputFile The input file represented as a collection of lines
                 * \param trace     The spatial temporal trace created using the data from the input file
                 */
                void readInputFileContents(const std::vector<std::string> &inputFile,
                                           SpatialTemporalTrace &trace);

                //! Check if the provided line is valid and, if yes, process the values it contains
                /*!
                 * \param line  The considered line
                 * \param trace The spatial temporal trace created using the data from the input file
                 */
                void processLine(const std::string &line, SpatialTemporalTrace &trace);

                //! Check if the provided line tokens are valid and, if yes, add them to the trace
                /*!
                 * \param lineTokens   The given line tokens
                 * \param trace        The spatial temporal trace created using the data from the input file
                 */
                void processLineTokens(const std::vector<std::string> &lineTokens, SpatialTemporalTrace &trace);

                //! Create a new time point in the trace from the given tokens
                /*!
                 * \param lineTokens   The given line tokens
                 * \param trace        The spatial temporal trace created using the data from the input file
                 */
                void createTimePointFromTokens(const std::vector<std::string> &lineTokens,
                                               SpatialTemporalTrace &trace);

                //! Set the value of the given time point considering the first token
                /*!
                 * \param lineTokens   The given line tokens
                 * \param timePoint    The provided time point
                 */
                void setTimePointValue(const std::vector<std::string> &lineTokens,
                                       TimePoint &timePoint);

                //! Add the numeric state variable values to the time point
                /*!
                 * \param lineTokens   The given line tokens
                 * \param timePoint    The provided time point
                 */
                void addNumericStateVariablesToTimePoint(const std::vector<std::string> &lineTokens,
                                                         TimePoint &timePoint);


                // Constants
                static const std::string INPUT_FILE_EXTENSION;

                static const std::string INPUT_FILE_DELIMITER;

                static const std::string ERR_INPUT_FILE_EMPTY_BEGIN;
                static const std::string ERR_INPUT_FILE_EMPTY_END;

                static const std::string ERR_INVALID_NR_OBSERVABLE_VARIABLES_BEGIN;
                static const std::string ERR_INVALID_NR_OBSERVABLE_VARIABLES_END;

                static const std::string ERR_EMPTY_OBSERVABLE_VARIABLE_NAME;

                static const std::string ERR_INVALID_NR_LINE_TOKENS_BEGIN;
                static const std::string ERR_INVALID_NR_LINE_TOKENS_MIDDLE;
                static const std::string ERR_INVALID_NR_LINE_TOKENS_END;

        };

    };

};


#endif
