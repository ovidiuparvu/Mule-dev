#ifndef SPATIALTEMPORALDATAREADER_HPP
#define SPATIALTEMPORALDATAREADER_HPP

#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <set>
#include <string>

namespace pt = boost::property_tree;


namespace multiscale {

    namespace verification {

        //! Class for reading spatial temporal trace data from input files
        class SpatialTemporalDataReader {

            private:

                std::set<std::string> processedInputFiles;    /*!< The set of processed input files */
                std::set<std::string> unprocessedInputFiles;  /*!< The set of unprocessed input files */

                std::string folderPath;     /*!< The path to the folder where all input files are stored */

            public:

                SpatialTemporalDataReader(const std::string &folderPath);
                ~SpatialTemporalDataReader();

                //! Check if there are any remaining valid unprocessed traces in the given folder
                /*!
                 * This method does not automatically refresh the sets of input files.
                 */
                bool hasNext();

                //! Refresh the sets of processed and unprocessed traces' input files considering the given folder
                void refresh();

                //! Return the next spatial temporal trace
                SpatialTemporalTrace getNextSpatialTemporalTrace();

                //! Return the next spatial temporal trace and its path
                /*!
                 * \param tracePath The path to the spatial temporal trace
                 */
                SpatialTemporalTrace getNextSpatialTemporalTrace(std::string &tracePath);

            private:

                //! Initialize the sets for storing processed and unprocessed input files
                /*!
                 * \param folderPath    Path to the input folder
                 */
                void initialize(const std::string &folderPath);

                //! Initialize the sets for storing processed and unprocessed input files
                void initialize();

                //! Clear the contents of the sets of processed and unprocessed input files
                void clearInputFilesSets();

                //! Check if there are any remaining valid unprocessed traces in the given folder
                bool hasValidNext();

                //! Process the invalid input file to which the given iterator points
                /*! The iterator corresponds to a position in the list of unprocessed input files
                 *
                 * \param invalidInputFileIterator  The iterator pointing to the invalid input file path
                 */
                std::set<std::string>::iterator processInvalidInputFile(const std::set<std::string>::iterator
                                                                        &invalidInputFileIterator);

                //! Generate the spatial temporal trace corresponding to the first valid unprocessed input file
                /*! The unprocessed input file will be moved to the set of processed input files after
                 *  creating the spatial temporal trace.
                 */
                SpatialTemporalTrace generateSpatialTemporalTrace();

                //! Generate the spatial temporal trace corresponding to the first valid unprocessed input file
                /*! The unprocessed input file will be moved to the set of processed input files after
                 *  creating the spatial temporal trace.
                 *
                 *  The path to the trace will be returned in the tracePath output parameter.
                 *
                 *  \param tracePath    The path to the spatial temporal trace
                 */
                SpatialTemporalTrace generateSpatialTemporalTrace(std::string &tracePath);

                //! Construct the spatial temporal trace corresponding to the first valid unprocessed input file
                /*! The unprocessed input file will be processed and returned as a property tree.
                 *
                 *  \param inputFilepath    The valid unprocessed input file path
                 */
                SpatialTemporalTrace constructSpatialTemporalTrace(const std::string &inputFilepath);

                //! Construct the spatial temporal trace corresponding to the given property tree
                /*  The property tree is the in-memory representation of the valid unprocessed
                 *  input xml file.
                 *
                 *  \param tree The valid unprocessed input file represented as a property tree
                 */
                SpatialTemporalTrace constructSpatialTemporalTrace(const pt::ptree &tree);

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

                //! Set the value of the timepoint considering the given timepoint tree
                /*!
                 * \param timePointTree Property tree representation of the timepoint
                 * \param timePoint     The TimePoint representation of the timepoint
                 */
                void setTimePointValue(const pt::ptree &timePointTree, TimePoint& timePoint);

                //! Check if the provided property tree contains the attribute "value"
                /*!
                 * \param propertyTree  The provided property tree
                 * \param value         The value (if it exists)
                 */
                bool timePointHasValue(const pt::ptree &propertyTree, unsigned long &value);

                //! Add the numeric state variables and spatial entities contained by the property tree to the given timepoint
                /*!
                 * \param timePointTree The given property tree
                 * \param timePoint     The given timepoint
                 */
                void addEntitiesToTimePoint(const pt::ptree &timePointTree, TimePoint &timePoint);

                //! Add the numeric state variable (provided as a tree) to the provided timepoint
                /*!
                 * \param numericStateVariableTree  The provided numeric state variable property tree
                 * \param timePoint                 The given timepoint
                 */
                void addNumericStateVariableToTimePoint(const pt::ptree &numericStateVariableTree, TimePoint &timePoint);

                //! Add the spatial entity contained by the property tree to the given timePoint
                /*!
                 * \param spatialEntityTree The given spatial entity represented as a property tree
                 * \param timePoint         The given timepoint
                 */
                void addSpatialEntityToTimePoint(const pt::ptree &spatialEntityTree, TimePoint &timePoint);

                //! Create a derived spatial entity considering the type specified in the given tree
                /*!
                 * \param spatialEntityTree The given spatial entity represented as a property tree
                 * \param spatialEntity     The created spatial entity
                 * \param spatialEntityType The derived type of the spatial entity
                 */
                void createDerivedSpatialEntity(const pt::ptree &spatialEntityTree,
                                                std::shared_ptr<SpatialEntity> &spatialEntity,
                                                SubsetSpecificType &spatialEntityType);

                //! Initialize the spatial entity scale and subsystem using the given spatialEntityTree
                /*!
                 * If the value of the scale and subsystem is not provided in the spatialEntityTree
                 * the default empty string "" is used instead.
                 *
                 * \param spatialEntityTree The spatial entity tree
                 * \param spatialEntity     The spatial entity to be initialized
                 */
                void setSpatialEntityScaleAndSubsystem(const pt::ptree &spatialEntityTree,
                                                       const std::shared_ptr<SpatialEntity> &spatialEntity);

                //! Initialize the spatial entity measure values using the given spatialEntityTree
                /*!
                 * \param spatialEntityTree The spatial entity tree
                 * \param spatialEntity     The spatial entity to be initialized
                 */
                void setSpatialEntityMeasureValues(const pt::ptree &spatialEntityTree,
                                                   const std::shared_ptr<SpatialEntity> &spatialEntity);

                //! Get an iterator pointing to a random valid unprocessed input file
                std::set<std::string>::iterator getRandomValidUnprocessedInputFilepath();

                //! Get an iterator pointing to a random unprocessed input file
                std::set<std::string>::iterator getRandomUnprocessedInputFile();

                //! Process the valid input file to which the given iterator points
                /*! The iterator corresponds to a position in the list of unprocessed input files
                 *
                 * \param validInputFileIterator    The iterator pointing to the valid input file path
                 */
                void processValidInputFile(const std::set<std::string>::iterator &validInputFileIterator);

                //! Update the sets of processed and unprocessed files by checking if the folder contents have been updated
                void updateInputFilesSets();

                //! Get the collection of files stored in the input folder
                std::vector<std::string> getFilesInFolder();

                //! Check if the given input file is valid
                /*! An input file is valid if it is an xml file which conforms to the formal
                 *  specification given in the xml schema (xsd file).
                 *
                 *  WARNING: The Timepoint class contains as members lists of spatial entities
                 *           because the uniqueness of the spatial entities is determined using this
                 *           method. If this method is no longer used then replace the lists
                 *           in the Timepoint class with sets or unordered_sets in order to ensure
                 *           the uniqueness of the elements.
                 *
                 * \param inputFilepath The path to the input file
                 */
                // TODO: Update Timepoint class if no longer using this function in the code
                bool isValidInputFile(const std::string &inputFilepath);

                //! Check if the given folder path is valid
                /*! The folder path is valid if it is a path pointing to a folder.
                 *
                 * \param folderPath
                 */
                void validateFolderPath(const std::string &folderPath);

            private:

                // Constants
                static const std::string ERR_INVALID_FOLDER_PATH_BEGIN;
                static const std::string ERR_INVALID_FOLDER_PATH_END;

                static const std::string ERR_NO_VALID_INPUT_FILES_REMAINING;
                static const std::string ERR_UNDEFINED_SPATIAL_ENTITY_TYPE;

                static const std::string LABEL_EXPERIMENT;
                static const std::string LABEL_TIMEPOINT_VALUE;

                static const std::string LABEL_NUMERIC_STATE_VARIABLE;
                static const std::string LABEL_NUMERIC_STATE_VARIABLE_SCALE_AND_SUBSYSTEM;
                static const std::string LABEL_NUMERIC_STATE_VARIABLE_NAME;
                static const std::string LABEL_NUMERIC_STATE_VARIABLE_VALUE;

                static const std::string LABEL_SPATIAL_ENTITY;
                static const std::string LABEL_SPATIAL_ENTITY_SPATIAL_TYPE;
                static const std::string LABEL_SPATIAL_ENTITY_SCALE_AND_SUBSYSTEM;

                static const std::string INPUT_FILES_EXTENSION;
                static const std::string INPUT_FILES_SCHEMA_PATH;

        };

    };

};


#endif
