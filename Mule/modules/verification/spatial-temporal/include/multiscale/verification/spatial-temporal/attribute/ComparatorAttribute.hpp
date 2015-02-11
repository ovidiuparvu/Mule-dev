#ifndef COMPARATORATTRIBUTE_HPP
#define COMPARATORATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing a comparator type
        enum class ComparatorType : unsigned int {
            GreaterThan         = 0,        /*!< Greater than */
            GreaterThanOrEqual     ,        /*!< Greater than or equal */
            LessThan               ,        /*!< Less than */
            LessThanOrEqual        ,        /*!< Less than or equal */
            Equal                           /*!< Equal */
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
