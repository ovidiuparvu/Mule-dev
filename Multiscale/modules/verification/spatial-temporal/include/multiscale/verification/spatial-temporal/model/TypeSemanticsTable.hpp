#ifndef TYPESEMANTICSTABLE_HPP
#define TYPESEMANTICSTABLE_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <map>
#include <string>

namespace pt = boost::property_tree;


namespace multiscale {

    namespace verification {

        //! Class for defining a type semantics table
        class TypeSemanticsTable {

            private:

                std::string
                    inputFilePath;                  /*!< The path to the input file */

                std::string
                    semanticCriteriaDescription;    /*!< The description of the considered semantic criteria */
                unsigned long
                    nrOfDescribedSemanticCriteria;  /*!< The number of considered semantic criteria */

                std::map<std::string, unsigned long>
                    table;                          /*!< The type semantics table mapping the semantic
                                                         criteria values to abstract positive natural
                                                         numbers */

            public:

                TypeSemanticsTable();
                ~TypeSemanticsTable();

                //! Read the type semantics table from the provided input file
                /*! Warning: The contents of the existing table will be overwritten by the contents
                 *           stored in the file.
                 *
                 * \param inputFilePath The path to the input file
                 */
                void readTableFromFile(const std::string &inputFilePath);

                //! Add a mapping to the table between semantic criteria values and an abstract type
                /*!
                 * If another type T was already associated with the semantic criteria values, T will
                 * be overwritten by the newly provided type.
                 *
                 * \param semanticCriteriaValues    The considered semantic criteria values specified in the
                 *                                  "semanticCriterion1Value.semanticCriterion2Value. ... .
                 *                                  semanticCriterionNValue" format
                 * \param type                      The abstract natural number representing the type associated to
                 *                                  the given semantic criteria values
                 */
                void addTableEntry(const std::string &semanticCriteriaValues,
                                   unsigned long type);

                //! Get a const reference to the iterator pointing at the beginning of the table
                std::map<std::string, unsigned long>::const_iterator getBeginIterator() const;

                //! Get a const reference to the iterator pointing at the end of the table
                std::map<std::string, unsigned long>::const_iterator getEndIterator() const;

                //! Check if the given semantic type exists in the table
                /*!
                 * \param semanticType  The provided semantic type
                 */
                bool existsSemanticType(const std::string &semanticType) const;

                //! Get the type corresponding to the semantic criteria values
                /*!
                 * \param semanticCriteriaValues    The semantic criteria values for which the type
                 *                                  (if it exists) is computed
                 */
                unsigned long getTypeOfSemanticCriteriaValues(const std::string &semanticCriteriaValues) const;

            private:

                //! Read the type semantics table from the provided input file
                void read();

                //! Read the type semantics table from the provided valid input file
                /*!
                 * Precondition: The provided input file path points to a regular file with the correct extension.
                 */
                void readFromValidFile();

                //! Read the type semantics table from the provided valid xml input file
                /*!
                 * Precondition: The provided input file path points to a valid xml file (relative to xsd).
                 */
                void readFromValidXmlFile();

                //! Construct a type semantics table from the provided property tree
                /*!
                 * \param propertyTree  The property tree corresponding to the xml input file
                 */
                void constructTypeSemanticsTable(const pt::ptree &propertyTree);

                //! Process semantic criteria description and initialise the corresponding fields
                /*!
                 * \param propertyTree  The property tree corresponding to the xml input file
                 */
                void processSemanticCriteriaDescription(const pt::ptree &propertyTree);

                //! Add the semantic types to the type semantics table
                /*!
                 * \param propertyTree  The property tree corresponding to the xml input file
                 */
                void addSemanticTypesToTable(const pt::ptree &propertyTree);

                //! Add a semantic type to the type semantics table
                /*!
                 * \param semanticTypeTree  The property tree corresponding to the semantic type
                 */
                void addSemanticTypeToTable(const pt::ptree &semanticTypeTree);

                //! Check if the provided semantic criteria value is valid

                //! Check if at least one of the provided semantic criteria values is undefined
                /*!
                 * \param semanticCriteriaValues The provided semantic criteria values
                 */
                bool isNoUndefinedSemanticCriteriaValue(const std::string &semanticCriteriaValues);

                //! Check if an entry exists in the table for the provided semantic criteria values
                /*!
                 * \param semanticCriteriaValues    The provided semantic criteria values
                 */
                bool existsEntryInTableForSemanticCriteriaValues(const std::string &semanticCriteriaValues) const;

                //! Check if the provided semantic criteria values equal the default semantic criteria value
                /*!
                 * \param semanticCriteriaValues    The provided semantic criteria values
                 */
                bool areDefaultSemanticCriteriaValues(const std::string &semanticCriteriaValues) const;


                // Constants
                static const unsigned long  DEFAULT_TYPE_VALUE;

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

                static const std::string ERR_NO_TABLE_ENTRY_SEMANTIC_CRITERIA_VALUES_BEGIN;
                static const std::string ERR_NO_TABLE_ENTRY_SEMANTIC_CRITERIA_VALUES_END;

        };

    };

};


#endif
