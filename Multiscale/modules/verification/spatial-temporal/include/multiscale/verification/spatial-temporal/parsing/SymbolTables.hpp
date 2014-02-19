#ifndef SYMBOLTABLES_HPP
#define SYMBOLTABLES_HPP

#include "multiscale/verification/spatial-temporal/attribute/BinaryNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/BinarySubsetMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/QuaternarySubsetMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SubsetSpecificAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/TernarySubsetMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnarySubsetMeasureAttribute.hpp"

#include <boost/spirit/include/qi_symbols.hpp>


namespace multiscale {

    namespace verification {

        //! Symbol table and parser for the comparator type
        struct ComparatorTypeParser : qi::symbols<char, multiscale::verification::ComparatorType> {

            ComparatorTypeParser() {
                add
                    (">"    , ComparatorType::GreaterThan)
                    (">="   , ComparatorType::GreaterThanOrEqual)
                    ("<"    , ComparatorType::LessThan)
                    ("<="   , ComparatorType::LessThanOrEqual)
                    ("="    , ComparatorType::Equal)
                ;
            }

        };

        //! Symbol table and parser for the spatial measure type
        struct SpatialMeasureTypeParser : qi::symbols<char, multiscale::verification::SpatialMeasureType> {

            SpatialMeasureTypeParser() {
                add
                    ("clusteredness"        , SpatialMeasureType::Clusteredness)
                    ("density"              , SpatialMeasureType::Density)
                    ("area"                 , SpatialMeasureType::Area)
                    ("perimeter"            , SpatialMeasureType::Perimeter)
                    ("distanceFromOrigin"   , SpatialMeasureType::DistanceFromOrigin)
                    ("angle"                , SpatialMeasureType::Angle)
                    ("triangleMeasure"      , SpatialMeasureType::TriangleMeasure)
                    ("rectangleMeasure"     , SpatialMeasureType::RectangleMeasure)
                    ("circleMeasure"        , SpatialMeasureType::CircleMeasure)
                    ("centroidX"            , SpatialMeasureType::CentroidX)
                    ("centroidY"            , SpatialMeasureType::CentroidY)
                ;
            }

        };

        //! Symbol table and parser for a specific subset type
        struct SubsetSpecificTypeParser : qi::symbols<char, multiscale::verification::SubsetSpecificType> {

            SubsetSpecificTypeParser() {
                add
                    ("clusters" , SubsetSpecificType::Clusters)
                    ("regions"  , SubsetSpecificType::Regions)
                ;
            }

        };


        //! Symbol table and parser for the binary numeric measure type
        struct BinaryNumericMeasureTypeParser : qi::symbols<char, multiscale::verification::BinaryNumericMeasureType> {

            BinaryNumericMeasureTypeParser() {
                add
                    ("add"      , BinaryNumericMeasureType::Add)
                    ("div"      , BinaryNumericMeasureType::Div)
                    ("log"      , BinaryNumericMeasureType::Log)
                    ("mod"      , BinaryNumericMeasureType::Mod)
                    ("multiply" , BinaryNumericMeasureType::Multiply)
                    ("power"    , BinaryNumericMeasureType::Power)
                    ("subtract" , BinaryNumericMeasureType::Subtract)
                ;
            }

        };

        //! Symbol table and parser for the unary numeric measure type
        struct UnaryNumericMeasureTypeParser : qi::symbols<char, multiscale::verification::UnaryNumericMeasureType> {

            UnaryNumericMeasureTypeParser() {
                add
                    ("abs"      , UnaryNumericMeasureType::Abs)
                    ("ceil"     , UnaryNumericMeasureType::Ceil)
                    ("floor"    , UnaryNumericMeasureType::Floor)
                    ("round"    , UnaryNumericMeasureType::Round)
                    ("sign"     , UnaryNumericMeasureType::Sign)
                    ("sqrt"     , UnaryNumericMeasureType::Sqrt)
                    ("trunc"    , UnaryNumericMeasureType::Trunc)
                ;
            }

        };

        //! Symbol table and parser for the quaternary subset measure type
        struct QuaternarySubsetMeasureTypeParser : qi::symbols<char, multiscale::verification::QuaternarySubsetMeasureType> {

            QuaternarySubsetMeasureTypeParser() {
                add
                    ("covar"    , QuaternarySubsetMeasureType::Covar)
                ;
            }

        };

        //! Symbol table and parser for the ternary subset measure type
        struct TernarySubsetMeasureTypeParser : qi::symbols<char, multiscale::verification::TernarySubsetMeasureType> {

            TernarySubsetMeasureTypeParser() {
                add
                    ("percentile"   , TernarySubsetMeasureType::Percentile)
                    ("quartile"     , TernarySubsetMeasureType::Quartile)
                ;
            }

        };

        //! Symbol table and parser for the binary subset measure type
        struct BinarySubsetMeasureTypeParser : qi::symbols<char, multiscale::verification::BinarySubsetMeasureType> {

            BinarySubsetMeasureTypeParser() {
                add
                    ("avg"      , BinarySubsetMeasureType::Avg)
                    ("geomean"  , BinarySubsetMeasureType::Geomean)
                    ("harmean"  , BinarySubsetMeasureType::Harmean)
                    ("kurt"     , BinarySubsetMeasureType::Kurt)
                    ("max"      , BinarySubsetMeasureType::Max)
                    ("median"   , BinarySubsetMeasureType::Median)
                    ("min"      , BinarySubsetMeasureType::Min)
                    ("mode"     , BinarySubsetMeasureType::Mode)
                    ("product"  , BinarySubsetMeasureType::Product)
                    ("skew"     , BinarySubsetMeasureType::Skew)
                    ("stdev"    , BinarySubsetMeasureType::Stdev)
                    ("sum"      , BinarySubsetMeasureType::Sum)
                    ("var"      , BinarySubsetMeasureType::Var)
                ;
            }

        };

        //! Symbol table and parser for the unary subset measure type
        struct UnarySubsetMeasureTypeParser : qi::symbols<char, multiscale::verification::UnarySubsetMeasureType> {

            UnarySubsetMeasureTypeParser() {
                add
                    ("count"            , UnarySubsetMeasureType::Count)
                    ("clusteredness"    , UnarySubsetMeasureType::Clusteredness)
                    ("density"          , UnarySubsetMeasureType::Density)
                ;
            }

        };

    };

};

#endif
