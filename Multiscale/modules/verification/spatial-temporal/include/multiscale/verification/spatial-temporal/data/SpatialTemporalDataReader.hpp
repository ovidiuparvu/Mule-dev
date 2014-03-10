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

                //! Check if there are any remaining valid unprocessed traces in the given folder
                bool hasNext();

                //! Return the next spatial temporal trace
                SpatialTemporalTrace getNextSpatialTemporalTrace();

            private:

                //! Initialise the sets for storing processed and unprocessed input files
                /*!
                 * \param folderPath    Path to the input folder
                 */
                void initialise(const std::string &folderPath);

                //! Initialise the sets for storing processed and unprocessed input files
                void initialise();

                //! Check if there are any remaining valid unprocessed traces in the given folder
                bool hasValidNext();

                //! Generate the spatial temporal trace corresponding to the first valid unprocessed input file
                /*! The unprocessed input file will be moved to the set of processed input files after
                 *  creating the spatial temporal trace.
                 */
                SpatialTemporalTrace generateSpatialTemporalTrace();

                //! Generate the spatial temporal trace corresponding to the first valid unprocessed input file
                /*! The unprocessed input file will be moved to the set of processed input files after
                 *  creating the spatial temporal trace.
                 *
                 *  \param inputFilepath    The valid unprocessed input file path
                 */
                SpatialTemporalTrace generateSpatialTemporalTrace(const std::string &inputFilepath);

                //! Generate the spatial temporal trace corresponding to the given property tree
                /*  The property tree is the in-memory representation of the valid unprocessed
                 *  input xml file.
                 *
                 *  \param tree The valid unprocessed input file represented as a property tree
                 */
                SpatialTemporalTrace generateSpatialTemporalTrace(const pt::ptree &tree);

                //! Add a timepoint corresponding to the given property tree to the spatial temporal trace
                /*!
                 * \param timePointTree The property tree corresponding to the timepoint
                 * \param trace         The spatial temporal trace
                 */
                void addTimePointToTrace(const pt::ptree &timePointTree, SpatialTemporalTrace &trace);

                //! Convert a time point from a property tree to a timepoint representation
                /*!
                 * \param timePointTree Property tree representation of the timepoint
                 * \param timePoint     The TimePoint representation of the timepoint
                 */
                void convertTimePointPropertyTreeToTrace(const pt::ptree &timePointTree, TimePoint &timePoint);

                //! Check if the provided property tree contains the attribute "value"
                /*!
                 * \param propertyTree  The provided property tree
                 * \param value         The value (if it exists)
                 */
                bool timePointHasValue(const pt::ptree &propertyTree, unsigned long &value);

                //! Add the numeric state variables contained by the property tree to the given timepoint
                /*!
                 * \param timePointTree The given property tree
                 * \param timePoint     The given timepoint
                 */
                void addNumericStateVariablesToTimePoint(const pt::ptree &timePointTree, TimePoint &timePoint);

                //! Add the numeric state variable (provided as a tree) to the provided timepoint
                /*!
                 * \param numericStateVariableTree  The provided numeric state variable property tree
                 * \param timePoint                 The given timepoint
                 */
                void addNumericStateVariableToTimePoint(const pt::ptree &numericStateVariableTree, TimePoint &timePoint);

                //! Add the spatial entities contained by the property tree to the given timepoint
                /*!
                 * \param timePointTree The given property tree
                 * \param timePoint     The given timepoint
                 */
                void addSpatialEntitiesToTimePoint(const pt::ptree &timePointTree, TimePoint &timePoint);

                //! Add the spatial entity contained by the property tree to the given timePoint
                /*!
                 * \param spatialEntityTree The given spatial entity represented as a property tree
                 * \param timePoint         The given timepoint
                 */
                void addSpatialEntityToTimePoint(const pt::ptree &spatialEntityTree, TimePoint &timePoint);

                //! Add the cluster contained by the property tree to the given timePoint
                /*!
                 * \param clusterTree   The given cluster represented as a property tree
                 * \param timePoint     The given timepoint
                 */
                void addClusterToTimePoint(const pt::ptree &clusterTree, TimePoint &timePoint);

                //! Add the region contained by the property tree to the given timePoint
                /*!
                 * \param regionTree    The given region represented as a property tree
                 * \param timePoint     The given timepoint
                 */
                void addRegionToTimePoint(const pt::ptree &regionTree, TimePoint &timePoint);

                //! Get the first valid unprocessed input file
                std::string getFirstValidUnprocessedInputFilepath();

                //! Update the sets of files by checking if the folder contents have been updated
                void updateFilesLists();

                //! Check if the given input file is valid
                /*! An input file is valid if it is an xml file which conforms to the formal
                 *  specification given in the xml schema (xsd file).
                 *
                 * \param inputFilepath The path to the input file
                 */
                bool isValidInputFile(const std::string &inputFilepath);

                //! Check if the given folder path is valid
                /*! The folder path is valid if it is a path pointing to a folder.
                 *
                 *  \param folderPath
                 */
                void validateFolderPath(const std::string &folderPath);

            private:

                // Constants
                static const std::string ERR_INVALID_FOLDER_PATH;
                static const std::string ERR_NO_VALID_INPUT_FILES_REMAINING;
                static const std::string ERR_UNDEFINED_SPATIAL_ENTITY_TYPE;

                static const std::string LABEL_EXPERIMENT;
                static const std::string LABEL_TIMEPOINT_VALUE;

                static const std::string LABEL_NUMERIC_STATE_VARIABLE;
                static const std::string LABEL_NUMERIC_STATE_VARIABLE_NAME;
                static const std::string LABEL_NUMERIC_STATE_VARIABLE_VALUE;

                static const std::string LABEL_SPATIAL_ENTITY;
                static const std::string LABEL_SPATIAL_ENTITY_PSEUDO3D_TYPE;

                static const std::string LABEL_SPATIAL_ENTITY_CLUSTEREDNESS;
                static const std::string LABEL_SPATIAL_ENTITY_DENSITY;
                static const std::string LABEL_SPATIAL_ENTITY_AREA;
                static const std::string LABEL_SPATIAL_ENTITY_PERIMETER;
                static const std::string LABEL_SPATIAL_ENTITY_DISTANCE_FROM_ORIGIN;
                static const std::string LABEL_SPATIAL_ENTITY_ANGLE;
                static const std::string LABEL_SPATIAL_ENTITY_TRIANGLE_MEASURE;
                static const std::string LABEL_SPATIAL_ENTITY_RECTANGLE_MEASURE;
                static const std::string LABEL_SPATIAL_ENTITY_CIRCLE_MEASURE;
                static const std::string LABEL_SPATIAL_ENTITY_CENTROID_X;
                static const std::string LABEL_SPATIAL_ENTITY_CENTROID_Y;

                static const std::string PSEUDO3D_SPATIAL_ENTITY_TYPE_REGION;
                static const std::string PSEUDO3D_SPATIAL_ENTITY_TYPE_CLUSTER;

        };

    };

};

#endif
