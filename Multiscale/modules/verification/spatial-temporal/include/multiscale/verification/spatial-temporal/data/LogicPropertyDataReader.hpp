#ifndef LOGICPROPERTYDATAREADER_HPP
#define LOGICPROPERTYDATAREADER_HPP

#include <fstream>
#include <sstream>
#include <string>
#include <vector>


namespace multiscale {

    namespace verification {

        //! Class used to input logic queries
        class LogicPropertyDataReader {

            private:

                std::stringstream stringBuilder;    /*!< The string builder used to concatenate strings */

            public:

                //! Return the logic queries read from a file
                /*! All lines which start with "#" are used for writing comments.
                 *  All lines which start with "P" introduce a new logic query.
                 *
                 * \param inputFilepath The path to the input file
                 */
                std::vector<std::string> readLogicQueriesFromFile(const std::string &inputFilepath);


            private:

                //! Read the logic queries from the given file
                /* Assumption: The path is pointing to a regular file.
                 *
                 * \param inputFilepath The path to the input file
                 */
                std::vector<std::string> readLogicQueriesFromValidFilepath(const std::string &fin);

                //! Read the logic queries from the given already opened input stream
                /*!
                 * \param fin   The input stream
                 */
                std::vector<std::string> readLogicQueriesFromOpenStream(std::ifstream &fin);

                //! Process a line from the input file
                /*!
                 * \param line          The line read from the input file
                 * \param logicQueries  The collection of logic queries obtained from the input file
                 */
                void processLineFromInputFile(const std::string &line,
                                                     std::vector<std::string> &logicQueries);

                //! Create a new logic query from the string builder contents
                /*! A new logic query is created only if the size of the string builder contents
                 *  is greater than 0.
                 *
                 * \param logicQueries  The collection of logic queries obtained from the input file
                 */
                void createNewLogicProperty(std::vector<std::string> &logicQueries);

                //! Append the given line to the string builder contents
                /*!
                 * \param line  The given line
                 */
                void appendLineUsingStringBuilder(const std::string &line);

                //! Remove the contents of the string builder
                void removeStringBuilderContents();


                // Constants
                static const std::string    ERR_INVALID_INPUT_PATH;
                static const std::string    ERR_OPEN_INPUT_FILE;

                static const char           CHAR_START_LOGIC_QUERY;
                static const char           CHAR_START_COMMENT;
        };

    };

};

#endif
