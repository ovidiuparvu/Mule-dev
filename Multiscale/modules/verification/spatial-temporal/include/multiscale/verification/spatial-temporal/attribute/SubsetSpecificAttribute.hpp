#ifndef SUBSETSPECIFICATTRIBUTE_HPP
#define SUBSETSPECIFICATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/SubsetSpecificType.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! An size_t constant which stores the number of subset specific type entries
        static const std::size_t
        NR_SUBSET_SPECIFIC_TYPES = static_cast<std::size_t>(SubsetSpecificType::NrOfSubsetSpecificTypeEntries);

        namespace subsetspecific {

            //! Check if the given subset specific type is valid
            /*!
             * \param subsetSpecificType    The given subset specific type
             */
            void validateSubsetSpecificType(const SubsetSpecificType &subsetSpecificType);

            //! Check if the given subset specific type index is valid
            /*!
             * \param subsetSpecificTypeIndex   The given subset specific type index
             */
            void validateSubsetSpecificTypeIndex(const std::size_t &subsetSpecificTypeIndex);

            //! Compute the index of the subset specific type
            /*!
             * \param subsetSpecificType The given subset specific type
             */
            size_t computeSubsetSpecificTypeIndex(const SubsetSpecificType &subsetSpecificType);

            //! Compute the subset specific type from the given index
            /*!
             * \param subsetSpecificTypeIndex    The given subset specific type index
             */
            SubsetSpecificType computeSubsetSpecificType(const std::size_t &subsetSpecificTypeIndex);

            //! Get the string representation of the given subset specific type
            /*!
             * \param subsetSpecificType    The given subset specific type
             */
            std::string toString(const SubsetSpecificType &subsetSpecificType);

            //! Get the string representation corresponding to the the given subset specific type index
            /*!
             * \param subsetSpecificTypeIndex   The given subset specific type index
             */
            std::string toString(const std::size_t &subsetSpecificTypeIndex);

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

                SubsetSpecificType subsetSpecificType;    /*!< The specific subset type */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::SubsetSpecificAttribute,
    (multiscale::verification::SubsetSpecificType, subsetSpecificType)
)


#endif
