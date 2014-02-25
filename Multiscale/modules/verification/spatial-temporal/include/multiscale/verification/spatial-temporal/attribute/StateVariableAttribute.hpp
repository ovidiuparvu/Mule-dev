#ifndef STATEVARIABLEATTRIBUTE_HPP
#define STATEVARIABLEATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <string>


namespace multiscale {

    namespace verification {

        //! Class for representing a state variable attribute
        class StateVariableAttribute {

            public:

                std::string name;   /*!< Name of the state variable */

            public:

                //! Return the name of the state variable as a string
                std::string evaluate() const;

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::StateVariableAttribute,
    (std::string, name)
)

#endif
