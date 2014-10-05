#ifndef SEMANTICTYPEATTRIBUTE_HPP
#define SEMANTICTYPEATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/model/SemanticType.hpp"

#include <boost/fusion/include/adapt_struct.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        //! Class for representing a semantic type attribute
        class SemanticTypeAttribute {

            public:

                std::string semanticType;    /*!< The considered semantic type */

            public:

                SemanticTypeAttribute(const std::string &semanticType = SemanticType::DEFAULT_VALUE)
                                      : semanticType(semanticType) {}

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::SemanticTypeAttribute,
    (std::string, semanticType)
)


#endif
