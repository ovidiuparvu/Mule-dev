#ifndef TYPESEMANTICSTABLEDATAREADER_HPP
#define TYPESEMANTICSTABLEDATAREADER_HPP

#include "multiscale/util/Filesystem.hpp"
#include "multiscale/util/XmlValidator.hpp"
#include "multiscale/verification/spatial-temporal/model/TypeSemanticsTable.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <string>

namespace pt = boost::property_tree;


namespace multiscale {

    namespace verification {

        //! Class for reading type semantic tables from input files
        /*!
         * Each type semantics table is formatted as an xml file. The structure
         * of this xml file is specified in a corresponding xsd file.
         */
        class TypeSemanticsTableDataReader {

            private:

                std::string inputFilePath;  /*!< The path to the input file */

                std::string     semanticCriteriaDescription;    /*!< The description of the considered semantic
                                                                     criteria */
                unsigned long   nrOfDescribedSemanticCriteria;  /*!< The number of considered semantic criteria */

            public:

                TypeSemanticsTableDataReader();

                //! Read the type semantics table from an input file
                /*!
                 * \param inputFilePath The path to the input file
                 */
                TypeSemanticsTable read(const std::string &inputFilePath);

            private:

                //! Read the type semantics table from the provided input file
                TypeSemanticsTable read();

                //! Read the type semantics table from the provided valid input file
                /*!
                 * Precondition: The provided input file path points to a regular file with the correct extension.
                 */
                TypeSemanticsTable readFromValidFile();

                //! Read the type semantics table from the provided valid xml input file
                /*!
                 * Precondition: The provided input file path points to a valid xml file (relative to xsd).
                 */
                TypeSemanticsTable readFromValidXmlFile();

                //! Construct a type semantics table from the provided property tree
                /*!
                 * \param propertyTree  The property tree corresponding to the xml input file
                 */
                TypeSemanticsTable constructTypeSemanticsTable(const pt::ptree &propertyTree);

                //! Process semantic criteria description and initialise the corresponding fields
                /*!
                 * \param propertyTree  The property tree corresponding to the xml input file
                 */
                void processSemanticCriteriaDescription(const pt::ptree &propertyTree);

                //! Add the semantic types to the type semantics table
                /*!
                 * \param propertyTree          The property tree corresponding to the xml input file
                 * \param typeSemanticsTable    The type semantics table to which semantics type will be added
                 */
                void addSemanticTypesToTable(const pt::ptree &propertyTree,
                                             TypeSemanticsTable &typeSemanticsTable);

                //! Add a semantic type to the type semantics table
                /*!
                 * \param semanticTypeTree      The property tree corresponding to the semantic type
                 * \param typeSemanticsTable    The type semantics table to which the semantic type will be added
                 */
                void addSemanticTypeToTable(const pt::ptree &semanticTypeTree,
                                            TypeSemanticsTable &typeSemanticsTable);

                //! Check if the provided semantic criteria value is valid

                //! Check if at least one of the provided semantic criteria values is undefined
                /*!
                 * \param semanticCriteriaValues The provided semantic criteria values
                 */
                bool isNoUndefinedSemanticCriteriaValue(const std::string &semanticCriteriaValues);


                // Constants
                static const std::string LABEL_TYPE_SEMANTICS_TABLE;
                static const std::string LABEL_SEMANTIC_CRITERIA_DESCRIPTION;
                static const std::string LABEL_SEMANTIC_TYPES;

                static const std::string LABEL_SEMANTIC_TYPE;
                static const std::string LABEL_SEMANTIC_TYPE_SEMANTICS;
                static const std::string LABEL_SEMANTIC_TYPE_VALUE;

                static const char SEMANTIC_CRITERIA_SEPARATOR;

                static const std::string TYPE_SEMANTICS_TABLE_INPUT_FILE_EXTENSION;
                static const std::string TYPE_SEMANTICS_TABLE_XSD_PATH;

                static const std::string ERR_INVALID_INPUT_FILE_PATH_BEGIN;
                static const std::string ERR_INVALID_INPUT_FILE_PATH_END;

                static const std::string ERR_INVALID_INPUT_FILE_RELATIVE_TO_XSD_BEGIN;
                static const std::string ERR_INVALID_INPUT_FILE_RELATIVE_TO_XSD_END;

                static const std::string ERR_UNDEFINED_SEMANTIC_CRITERIA_BEGIN;
                static const std::string ERR_UNDEFINED_SEMANTIC_CRITERIA_MIDDLE1;
                static const std::string ERR_UNDEFINED_SEMANTIC_CRITERIA_MIDDLE2;
                static const std::string ERR_UNDEFINED_SEMANTIC_CRITERIA_END;

        };

    };

};


#endif
