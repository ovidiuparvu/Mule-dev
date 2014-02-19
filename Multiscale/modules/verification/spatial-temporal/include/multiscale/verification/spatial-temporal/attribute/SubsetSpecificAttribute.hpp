#ifndef SUBSETSPECIFICATTRIBUTE_HPP
#define SUBSETSPECIFICATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing a specific subset type
        enum class SubsetSpecificType : int {
            Clusters    = 1,    /*!< Clusters */
            Regions     = 2     /*!< Regions */
        };

        //! Overload the output stream operator for the enumeration
        /*!
         * \param out                   Output stream
         * \param subsetSpecificType    The specific subset type to be printed out
         */
        std::ostream& operator<<(std::ostream& out, const SubsetSpecificType &subsetSpecificType);


        //! Class for representing a subset specific attribute
        class SubsetSpecificAttribute {

            public:

                SubsetSpecificType subsetSpecific;    /*!< The specific subset which should be considered */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::SubsetSpecificAttribute,
    (multiscale::verification::SubsetSpecificType, subsetSpecific)
)

#endif
