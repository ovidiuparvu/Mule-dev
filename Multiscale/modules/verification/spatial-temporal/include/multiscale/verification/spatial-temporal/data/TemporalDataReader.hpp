#ifndef TEMPORALDATAREADER_HPP
#define TEMPORALDATAREADER_HPP

#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"

#include <fstream>
#include <string>


namespace multiscale {

    namespace verification {

        //! Class for reading (non-spatial) timeseries data from a .csv file
        /*!
         * The format of the .csv input files is:
         *     Time,Observable 1,Observable 2, ..., Observable n
         *     T1, O11, O21, ..., On1
         *     T2, O12, O22, ..., On2
         *     ...
         *     Tm, O1m, O2m, ..., Onm
         * where the first line contains the name of the observable variables (e.g. species)
         * and the subsequent lines the values of these variables for a given timepoint
         * (Ti, 1 <= i <= m)
         */
        class TemporalDataReader {

            private:

                std::string                 filePath;               /*!< The path to the input file */

                std::vector<std::string>    observableVariables;    /*!< The names of the observable variables */

                unsigned long               currentLineNumber;      /*!< The current input file line number */

            public:

                TemporalDataReader();

                //! Read the data from the input file and use it to construct a spatial temporal trace
                /*!
                 * \param filePath  The input file path
                 */
                SpatialTemporalTrace readTimeseriesFromFile(const std::string &filePath);

            private:

                //! Read the data from the valid input file and construct a spatial temporal trace
                SpatialTemporalTrace readFromValidInputFile();

                //! Read the data from the valid opened input file and construct a spatial temporal trace
                /*!
                 * \param fin   The input file stream opened for the given input file
                 * \param trace The spatial temporal trace created using the data from the input file
                 */
                void readFromValidOpenedInputFile(std::ifstream &fin, SpatialTemporalTrace &trace);

                //! Read the header row from the input file
                /*!
                 * \param fin   The input file stream opened for the given input file
                 * \param trace The spatial temporal trace created using the data from the input file
                 */
                void readInputFileHeader(std::ifstream &fin, SpatialTemporalTrace &trace);

                //! Validate the observable variables
                /*!
                 * The observable variables collection is valid if it contains two or more elements.
                 */
                void validateObservableVariables();

                //! Read the contents (excluding header row) from the input file
                /*!
                 * \param fin   The input file stream opened for the given input file
                 * \param trace The spatial temporal trace created using the data from the input file
                 */
                void readInputFileContents(std::ifstream &fin, SpatialTemporalTrace &trace);

                //! Check if the provided line tokens are valid and, if yes, add them to the trace
                /*!
                 * \param lineTokens   The given line tokens
                 * \param trace        The spatial temporal trace created using the data from the input file
                 */
                void processLineTokens(const std::vector<std::string> &lineTokens, SpatialTemporalTrace &trace);

                //! Create a new timepoint in the trace from the given tokens
                /*!
                 * \param lineTokens   The given line tokens
                 * \param trace        The spatial temporal trace created using the data from the input file
                 */
                void createTimePointFromTokens(const std::vector<std::string> &lineTokens,
                                               SpatialTemporalTrace &trace);

                //! Set the value of the given timepoint considering the first token
                /*!
                 * \param lineTokens   The given line tokens
                 * \param timePoint    The provided timepoint
                 */
                void setTimePointValue(const std::vector<std::string> &lineTokens,
                                       TimePoint &timePoint);

                //! Add the numeric state variable values to the timepoint
                /*!
                 * \param lineTokens   The given line tokens
                 * \param timePoint    The provided timepoint
                 */
                void addNumericStateVariablesToTimePoint(const std::vector<std::string> &lineTokens,
                                                         TimePoint &timePoint);


                // Constants
                static const std::string INPUT_FILE_EXTENSION;

                static const std::string INPUT_FILE_DELIMITER;

                static const std::string ERR_INVALID_INPUT_FILE_PATH_BEGIN;
                static const std::string ERR_INVALID_INPUT_FILE_PATH_END;

                static const std::string ERR_OPEN_INPUT_FILE_BEGIN;
                static const std::string ERR_OPEN_INPUT_FILE_END;

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
