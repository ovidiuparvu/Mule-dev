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
                 * \param scaleAndSubsystem             The provided scale and subsystem
                 * \param multiscaleArchitectureGraph   The multiscale architecture graph which stores all valid
                 *                                      scales and subsystems
                 */
                static void validateScaleAndSubsystem(const std::string &scaleAndSubsystem,
                                                      const MultiscaleArchitectureGraph &multiscaleArchitectureGraph);

                //! Check if the provided scales and subsystems are equal
                /*! Precondition: The provided scales and subsystem are valid.
                 *
                 * \param lhsScaleAndSubsystem  The left hand side scale and subsystem
                 * \param rhsScaleAndSubsystem  The right hand side scale and subsystem
                 */
                static bool areEqualScalesAndSubsystems(const std::string &lhsScaleAndSubsystem,
                                                        const std::string &rhsScaleAndSubsystem);

            private:

                // Constants
                static const std::string ERR_INVALID_SCALE_AND_SUBSYSTEM_BEGIN;
                static const std::string ERR_INVALID_SCALE_AND_SUBSYSTEM_END;

        };

    };

};


#endif
