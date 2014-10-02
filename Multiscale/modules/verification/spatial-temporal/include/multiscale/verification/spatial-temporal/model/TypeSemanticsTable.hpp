#ifndef TYPESEMANTICSTABLE_HPP
#define TYPESEMANTICSTABLE_HPP

#include <map>


namespace multiscale {

    namespace verification {

        //! Class for defining a type semantics table
        class TypeSemanticsTable {

            private:

                std::map<std::string, unsigned long> table; /*!< The type semantics table mapping the semantic
                                                                 criteria values to abstract positive natural
                                                                 numbers */

            public:

                TypeSemanticsTable();
                ~TypeSemanticsTable();

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
                void addMappingFromSemanticCriteriaValuesToType(const std::string &semanticCriteriaValues,
                                                                unsigned long type);

                //! Get a const reference to the iterator pointing at the beginning of the table
                std::map<std::string, unsigned long>::const_iterator getBeginIterator() const;

                //! Get a const reference to the iterator pointing at the end of the table
                std::map<std::string, unsigned long>::const_iterator getEndIterator() const;

                //! Get the type corresponding to the semantic criteria values
                /*!
                 * \param semanticCriteriaValues    The semantic criteria values for which the type
                 *                                  (if it exists) is computed
                 */
                unsigned long getTypeOfSemanticCriteriaValues(const std::string &semanticCriteriaValues);

            private:

                //! Check if an entry exists in the table for the provided semantic criteria values
                /*!
                 * \param semanticCriteriaValues    The provided semantic criteria values
                 */
                bool existsEntryInTableForSemanticCriteriaValues(const std::string &semanticCriteriaValues);

                //! Check if the provided semantic criteria values equal the default semantic criteria value
                /*!
                 * \param semanticCriteriaValues    The provided semantic criteria values
                 */
                bool areDefaultSemanticCriteriaValues(const std::string &semanticCriteriaValues);


                // Constants
                static const std::string    DEFAULT_SEMANTIC_CRITERIA_VALUE;
                static const unsigned long  DEFAULT_TYPE_VALUE;

                static const std::string    ERR_NO_TABLE_ENTRY_SEMANTIC_CRITERIA_VALUES_BEGIN;
                static const std::string    ERR_NO_TABLE_ENTRY_SEMANTIC_CRITERIA_VALUES_END;

        };

    };

};


#endif
