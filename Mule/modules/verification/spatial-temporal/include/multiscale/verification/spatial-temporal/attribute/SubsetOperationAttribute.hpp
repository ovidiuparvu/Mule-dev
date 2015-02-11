#ifndef SUBSETOPERATIONATTRIBUTE_HPP
#define SUBSETOPERATIONATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing the types of subset operations
        enum class SubsetOperationType : unsigned int {
            Difference      = 0,    /*!< Difference of two subsets */
            Intersection       ,    /*!< Intersection of two subsets */
            Union                   /*!< Union of two subsets */
        };


        //! Overload the output stream operator for the enumeration
        /*!
         * \param out                   Output stream
         * \param subsetOperationType   The subset operation type to be printed out
         */
        std::ostream& operator<<(std::ostream& out, const SubsetOperationType &subsetOperationType);


        //! Class for representing a subset operation attribute
        class SubsetOperationAttribute {

            public:

                SubsetOperationType subsetOperationType;    /*!< The subset operation type */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::SubsetOperationAttribute,
    (multiscale::verification::SubsetOperationType, subsetOperationType)
)


#endif
