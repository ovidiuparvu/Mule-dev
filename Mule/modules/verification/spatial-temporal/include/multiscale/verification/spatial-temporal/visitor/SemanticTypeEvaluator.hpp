#ifndef SEMANTICTYPEEVALUATOR_HPP
#define SEMANTICTYPEEVALUATOR_HPP

#include "multiscale/verification/spatial-temporal/attribute/SemanticTypeAttribute.hpp"


namespace multiscale {

    namespace verification {

        // Class used to evaluate semantic types
        class SemanticTypeEvaluator {

            public:

                //! Check if the provided semantic type exists and otherwise throw an exception
                /*!
                 * \param semanticType          The provided semantic type
                 * \param typeSemanticsTable    The type semantics table which stores all valid semantic types
                 */
                static void validate(const std::string &semanticType,
                                     const TypeSemanticsTable &typeSemanticsTable);

            private:

                // Constants
                static const std::string ERR_INVALID_SEMANTIC_TYPE_BEGIN;
                static const std::string ERR_INVALID_SEMANTIC_TYPE_END;

        };

    };

};


#endif
