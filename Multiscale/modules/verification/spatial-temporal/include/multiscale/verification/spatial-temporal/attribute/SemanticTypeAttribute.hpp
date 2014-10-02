#ifndef SEMANTICTYPEATTRIBUTE_HPP
#define SEMANTICTYPEATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        //! Class for representing a semantic type attribute
        class SemanticTypeAttribute {

            public:

                std::string semanticType;    /*!< The considered semantic type */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::SemanticTypeAttribute,
    (std::string, semanticType)
)


#endif
