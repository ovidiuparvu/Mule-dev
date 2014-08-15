#ifndef BINARYNUMERICMEASUREATTRIBUTE_HPP
#define BINARYNUMERICMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing a binary numeric measure type
        enum class BinaryNumericMeasureType : unsigned int {
            Add         = 0,    /*!< Addition */
            Div            ,    /*!< Division */
            Log            ,    /*!< Logarithm */
            Mod            ,    /*!< Remainder of division */
            Multiply       ,    /*!< Multiplication */
            Power          ,    /*!< Raise to power */
            Subtract            /*!< Subtraction */
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
