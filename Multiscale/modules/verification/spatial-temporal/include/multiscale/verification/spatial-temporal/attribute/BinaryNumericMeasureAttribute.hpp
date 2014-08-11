#ifndef BINARYNUMERICMEASUREATTRIBUTE_HPP
#define BINARYNUMERICMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing a binary numeric measure type
        enum class BinaryNumericMeasureType : int {
            Add         = 1,    /*!< Addition */
            Div         = 2,    /*!< Division */
            Log         = 3,    /*!< Logarithm */
            Mod         = 4,    /*!< Remainder of division */
            Multiply    = 5,    /*!< Multiplication */
            Power       = 6,    /*!< Raise to power */
            Subtract    = 7     /*!< Subtraction */
        };


        //! Overload the output stream operator for the enumeration
        /*!
         * \param out                       Output stream
         * \param binaryNumericMeasureType  The binary numeric measure type to be printed out
         */
        std::ostream& operator<<(std::ostream& out, const BinaryNumericMeasureType &binaryNumericMeasureType);


        //! Class for representing a binary numeric measure attribute
        class BinaryNumericMeasureAttribute {

            public:

                BinaryNumericMeasureType binaryNumericMeasureType;  /*!< The binary numeric measure type */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinaryNumericMeasureAttribute,
    (multiscale::verification::BinaryNumericMeasureType, binaryNumericMeasureType)
)


#endif
