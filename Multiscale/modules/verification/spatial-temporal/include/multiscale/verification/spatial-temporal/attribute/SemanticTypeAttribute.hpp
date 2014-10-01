#ifndef SEMANTICTYPEATTRIBUTE_HPP
#define SEMANTICTYPEATTRIBUTE_HPP

#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/optional.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        //! Class for representing a semantic type attribute
        class SemanticTypeAttribute {

            public:

                unsigned long type;    /*!< The considered type */


            public:

                SemanticTypeAttribute(unsigned long type = 0) : type(type) {}

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::SemanticTypeAttribute,
    (unsigned long, type)
)


#endif
