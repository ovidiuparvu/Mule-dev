#ifndef UNARYSTATISTICALMEASUREATTRIBUTE_HPP
#define UNARYSTATISTICALMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing a unary statistical measure type
        enum class UnaryStatisticalMeasureType : unsigned int {
            Avg     = 0,    /*!< The average (arithmetic mean) */
            Count      ,    /*!< The cardinality of a collection */
            Geomean    ,    /*!< The geometric mean */
            Harmean    ,    /*!< The harmonic mean */
            Kurt       ,    /*!< The kurtosis */
            Max        ,    /*!< The maximum */
            Median     ,    /*!< The median */
            Min        ,    /*!< The minimum */
            Mode       ,    /*!< The mode */
            Product    ,    /*!< The product */
            Skew       ,    /*!< The skew */
            Stdev      ,    /*!< The standard deviation */
            Sum        ,    /*!< The sum */
            Var             /*!< The variance */
        };


        //! Overload the output stream operator for the enumeration
        /*!
         * \param out                           Output stream
         * \param unaryStatisticalMeasureType   The unary statistical measure type to be printed out
         */
        std::ostream& operator<<(std::ostream& out, const UnaryStatisticalMeasureType &unaryStatisticalMeasureType);


        //! Class for representing a unary statistical measure attribute
        class UnaryStatisticalMeasureAttribute {

            public:

                UnaryStatisticalMeasureType unaryStatisticalMeasureType;    /*!< The unary statistical measure type */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnaryStatisticalMeasureAttribute,
    (multiscale::verification::UnaryStatisticalMeasureType, unaryStatisticalMeasureType)
)


#endif
