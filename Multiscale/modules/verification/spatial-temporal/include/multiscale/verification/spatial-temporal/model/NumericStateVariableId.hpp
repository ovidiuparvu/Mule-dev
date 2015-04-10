#ifndef NUMERICSTATEVARIABLEID_HPP
#define NUMERICSTATEVARIABLEID_HPP

#include "multiscale/verification/spatial-temporal/model/ScaleAndSubsystem.hpp"
#include "multiscale/verification/spatial-temporal/model/StateVariable.hpp"

#include <string>


namespace multiscale {

    namespace verification {

        //! Class for representing the identity (name, type) of a numeric state variable
        class NumericStateVariableId : public StateVariable {

            private:

                std::string name;               /*!< The name of the numeric state variable */
                
            public:

                NumericStateVariableId(const std::string &name,
                                       const std::string &scaleAndSubsystem = ScaleAndSubsystem::DEFAULT_VALUE);

                ~NumericStateVariableId();

                //! Get the name of the numeric state variable
                const std::string& getName() const;

                //! Set the name of the numeric state variable
                /*!
                 * \param name  The name of the numeric state variable
                 */
                void setName(const std::string& name);

                //! Overload the < operator
                /*!
                 * \param rhs   The right hand side numeric state variable identity
                 *              in the expression (lhs < rhs)
                 */
                bool operator<(const NumericStateVariableId &rhs) const;

                //! Return the string representation of the numeric state variable identity
                std::string toString() const;


                // Constants
                static const std::string OUTPUT_STRING_BEGIN;
                static const std::string OUTPUT_STRING_SEPARATOR;
                static const std::string OUTPUT_STRING_END;

        };

    };

};

#endif
