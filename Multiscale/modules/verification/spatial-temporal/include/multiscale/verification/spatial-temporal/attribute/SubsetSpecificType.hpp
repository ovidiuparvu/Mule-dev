#ifndef SUBSETSPECIFICTYPE_HPP
#define SUBSETSPECIFICTYPE_HPP

namespace multiscale {

    namespace verification {

        //! Enumeration for representing a specific subset type
        enum class SubsetSpecificType : unsigned int {
            Clusters                        = 0,            /*!< Clusters */
            Regions                            ,            /*!< Regions */
            NrOfSubsetSpecificTypeEntries                   /*!< Enumeration type used to store the number of
                                                                 elements in the enumeration. Always leave it last! */
        };

    };

};



#endif
