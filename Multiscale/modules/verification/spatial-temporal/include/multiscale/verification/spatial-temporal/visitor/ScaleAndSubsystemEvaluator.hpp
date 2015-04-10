#ifndef SCALEANDSUBSYSTEMEVALUATOR_HPP
#define SCALEANDSUBSYSTEMEVALUATOR_HPP

#include "multiscale/verification/spatial-temporal/attribute/ScaleAndSubsystemAttribute.hpp"


namespace multiscale {

    namespace verification {

        // Class used to evaluate scale and subsystems
        class ScaleAndSubsystemEvaluator {

            public:

                //! Check if the provided scale and subsystem exists and otherwise throw an exception
                /*!
                 * \param scaleAndSubsystem     The provided scale and subsystem
                 * \param typeSemanticsTable    The type semantics table which stores all valid semantic types
                 */
                static void validate(const std::string &scaleAndSubsystem,
                                     const TypeSemanticsTable &typeSemanticsTable);

            private:

                // Constants
                static const std::string ERR_INVALID_SCALE_AND_SUBSYSTEM_BEGIN;
                static const std::string ERR_INVALID_SCALE_AND_SUBSYSTEM_END;

        };

    };

};


#endif
