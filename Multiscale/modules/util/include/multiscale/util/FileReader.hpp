#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include <fstream>
#include <string>
#include <vector>


namespace multiscale {

    //! Class for representing a file reader
    class FileReader {

        public:

            //! Read a file line by line and return the read lines as a collection of strings
            /*!
             * \param filePath      The path to the input file including extension
             * \param fileExtension The extension of the input file (only for validation purposes)
             */
            static std::vector<std::string> readFileLineByLine(const std::string &filePath,
                                                               const std::string &fileExtension);

        private:

            //! Check if the provided file path is valid and throw an exception otherwise
            /*!
             * \param filePath      The path to the input file including extension
             * \param fileExtension The extension of the input file (only for validation purposes)
             */
            static void validateFilePath(const std::string &filePath, const std::string &fileExtension);

            //! Read the file having a valid path line by line and return the read lines as a collection of strings
            /*!
             * \param filePath      The path to the input file
             */
            static std::vector<std::string> readValidFileLineByLine(const std::string &filePath);

            //! Read the input file stream contents and split the contents in lines
            /*!
             * \param filePath          The path to the input file
             * \param inputFileStream   The considered input file stream
             */
            static std::vector<std::string> readStreamContentsAndSplitLines(const std::string &filePath,
                                                                            std::ifstream &inputFileStream);

            //! Read the open input file stream contents and split the contents in lines
            /*!
             * \param filePath          The path to the input file
             * \param inputFileStream   The considered input file stream
             */
            static std::vector<std::string> readOpenStreamContentsAndSplitLines(const std::string &filePath,
                                                                                std::ifstream &inputFileStream);

            //! Read the open input file stream contents
            /*!
             * \param filePath          The path to the input file
             * \param inputFileStream   The considered input file stream
             * \param buffer            The buffer in which data from the input file stream is temporarily stored
             */
            static std::string readOpenStreamContents(const std::string &filePath,
                                                      std::ifstream &inputFileStream,
                                                      char *buffer);

            //! Read up to BUFFER_SIZE characters from the provided input file stream
            /*! If an error occurs during the read, an exception is thrown
             *
             * \param filePath          The path to the input file
             * \param inputFileStream   The considered input file stream
             * \param buffer            The considered buffer
             */
            static void readFromInputFileStream(const std::string &filePath,
                                                std::ifstream &inputFileStream,
                                                char *buffer);

            //! Close the provided input file stream
            /*! If the input file stream cannot be successfully closed, an exception is thrown.
             *
             * \param filePath          The path to the input file
             * \param inputFileStream   The considered input file stream
             */
            static void closeInputFileStream(const std::string &filePath,
                                             std::ifstream &inputFileStream);


            // Constants
            static const long int   BUFFER_SIZE;

            static const std::string ERR_INVALID_INPUT_FILE_PATH_BEGIN;
            static const std::string ERR_INVALID_INPUT_FILE_PATH_MIDDLE;
            static const std::string ERR_INVALID_INPUT_FILE_PATH_END;

            static const std::string ERR_OPEN_INPUT_FILE_STREAM_BEGIN;
            static const std::string ERR_OPEN_INPUT_FILE_STREAM_END;

            static const std::string ERR_READ_DATA_FROM_INPUT_FILE_STREAM_BEGIN;
            static const std::string ERR_READ_DATA_FROM_INPUT_FILE_STREAM_END;

            static const std::string ERR_CLOSE_INPUT_FILE_STREAM_BEGIN;
            static const std::string ERR_CLOSE_INPUT_FILE_STREAM_END;

    };

};


#endif
