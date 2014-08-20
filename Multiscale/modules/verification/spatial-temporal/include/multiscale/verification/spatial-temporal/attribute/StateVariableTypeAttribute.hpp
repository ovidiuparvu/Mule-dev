#ifndef STATEVARIABLETYPEATTRIBUTE_HPP
#define STATEVARIABLETYPEATTRIBUTE_HPP

#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/optional.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a state variable type attribute
        class StateVariableTypeAttribute {

            public:

                unsigned long type;    /*!< The considered type */


            public:

                StateVariableTypeAttribute(unsigned long type = 0) : type(type) {}

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::StateVariableTypeAttribute,
    (unsigned long, type)
)


#endif
