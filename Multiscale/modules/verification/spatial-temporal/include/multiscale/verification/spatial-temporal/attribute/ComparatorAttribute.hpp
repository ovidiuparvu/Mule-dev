#ifndef COMPARATORATTRIBUTE_HPP
#define COMPARATORATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing a comparator type
        enum class ComparatorType : int {
            GreaterThan         = 1,        /*!< Greater than */
            GreaterThanOrEqual  = 2,        /*!< Greater than or equal */
            LessThan            = 3,        /*!< Less than */
            LessThanOrEqual     = 4,        /*!< Less than or equal */
            Equal               = 5         /*!< Equal */
        };


        //! Overload the output stream operator for the enumeration
        /*!
         * \param out                Output stream
         * \param comparatorType    The comparator type to be printed out
         */
        std::ostream& operator<<(std::ostream& out, const ComparatorType &comparatorType);


        //! Class for representing a comparator attribute
        class ComparatorAttribute {

            public:

                ComparatorType comparatorType;  /*!< The comparator type */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::ComparatorAttribute,
    (multiscale::verification::ComparatorType, comparatorType)
)

#endif
