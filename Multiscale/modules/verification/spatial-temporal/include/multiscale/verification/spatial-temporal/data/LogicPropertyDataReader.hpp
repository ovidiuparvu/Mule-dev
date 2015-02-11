#ifndef LOGICPROPERTYDATAREADER_HPP
#define LOGICPROPERTYDATAREADER_HPP

#include <fstream>
#include <sstream>
#include <string>
#include <vector>


namespace multiscale {

    namespace verification {

        //! Class used to input logic properties
        class LogicPropertyDataReader {

            private:

                std::stringstream stringBuilder;    /*!< The string builder used to concatenate strings */

            public:

                //! Return the logic properties read from a file
                /*! All lines which start with "#" are used to write comments.
                 *  All lines which start with "P" introduce a new logic property.
                 *
                 * \param inputFilepath The path to the input file
                 */
                std::vector<std::string> readLogicPropertiesFromFile(const std::string &inputFilepath);


            private:

                //! Read the logic properties from the given file
                /* Assumption: The path is pointing to a regular file.
                 *
                 * \param inputFilepath The path to the input file
                 */
                std::vector<std::string> readLogicPropertiesFromValidFilepath(const std::string &fin);

                //! Read the logic properties from the given already opened input stream
                /*!
                 * \param fin   The input stream
                 */
                std::vector<std::string> readLogicPropertiesFromOpenStream(std::ifstream &fin);

                //! Process a line from the input file
                /*!
                 * \param line              The line read from the input file
                 * \param logicProperties   The collection of logic properties obtained from the input file
                 */
                void processLineFromInputFile(const std::string &line,
                                              std::vector<std::string> &logicProperties);

                //! Create a new logic property from the string builder contents
                /*! A new logic property is created only if the size of the string builder contents
                 *  is greater than 0.
                 *
                 * \param logicProperties   The collection of logic properties obtained from the input file
                 */
                void createNewLogicProperty(std::vector<std::string> &logicProperties);

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

                static const char           CHAR_START_LOGIC_PROPERTY;
                static const char           CHAR_START_COMMENT;
        };

    };

};


#endif
