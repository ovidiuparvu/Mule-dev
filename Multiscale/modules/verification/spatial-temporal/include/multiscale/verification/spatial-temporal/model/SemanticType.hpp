#ifndef SEMANTICTYPE_HPP
#define SEMANTICTYPE_HPP

#include <string>


namespace multiscale {

    namespace verification {

        //! Enumeration for defining a semantic type
        class SemanticType {

            public:

                static const std::string DEFAULT_VALUE; /*!< The default semantic type value used when no explicit
                                                             semantic type is associated to a spatial entity and/or
                                                             numeric state variable */

        };

    };

};


#endif
