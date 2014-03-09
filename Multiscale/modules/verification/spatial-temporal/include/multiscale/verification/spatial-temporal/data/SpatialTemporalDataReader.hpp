#ifndef SPATIALTEMPORALDATAREADER_HPP
#define SPATIALTEMPORALDATAREADER_HPP

#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"

#include <string>
#include <unordered_set>


namespace multiscale {

    namespace verification {

        //! Class for reading spatial temporal trace data from input files
        class SpatialTemporalDataReader {

            private:

                std::unordered_set<std::string> processedInputFiles;    /*!< The set of processed input files */
                std::unordered_set<std::string> unprocessedInputFiles;  /*!< The set of unprocessed input files */

                std::string folderPath;     /*!< The path to the folder where all input files are stored */

            public:

                SpatialTemporalDataReader(const std::string &folderPath);
                ~SpatialTemporalDataReader();

                //! Check if there are any remaining unprocessed traces in the given folder
                bool hasNext();

                //! Return the next spatial temporal trace
                SpatialTemporalTrace getNextSpatialTemporalTrace();

            private:

                //! Update the sets of files by checking if the folder contents have been updated
                void updateFilesLists();

                //! Check if the given input file is valid
                /*! An input file is valid if it is an xml file which conforms to the formal
                 *  specification given in the xml schema (xsd file).
                 *
                 * \param inputFilepath The path to the input file
                 */
                bool isValidInputFile(const std::string &inputFilepath);

        };

    };

};

#endif
