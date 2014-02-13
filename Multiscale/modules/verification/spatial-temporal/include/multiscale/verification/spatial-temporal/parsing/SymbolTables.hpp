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
		struct ComparatorType_ : qi::symbols<char, multiscale::verification::ComparatorType> {

			ComparatorType_() {
				add
					(">="	, ComparatorType::GreaterThanOrEqual)
					("<="	, ComparatorType::LessThanOrEqual)
					("="	, ComparatorType::Equal)
				;
			}

		} ComparatorTypeParser;

		//! Symbol table and parser for the spatial measure type
		struct SpatialMeasureType_ : qi::symbols<char, multiscale::verification::SpatialMeasureType> {

			SpatialMeasureType_() {
				add
					("clusteredness"		, SpatialMeasureType::Clusteredness)
					("density"				, SpatialMeasureType::Density)
					("area"					, SpatialMeasureType::Area)
					("perimeter"			, SpatialMeasureType::Perimeter)
					("distanceFromOrigin"	, SpatialMeasureType::DistanceFromOrigin)
					("angle"				, SpatialMeasureType::Angle)
					("triangleMeasure"		, SpatialMeasureType::TriangleMeasure)
					("rectangleMeasure"		, SpatialMeasureType::RectangleMeasure)
					("circleMeasure"		, SpatialMeasureType::CircleMeasure)
					("centroidX"			, SpatialMeasureType::CentroidX)
					("centroidY"			, SpatialMeasureType::CentroidY)
				;
			}

		} SpatialMeasureTypeParser;

		//! Symbol table and parser for a specific subset type
		struct SubsetSpecificType_ : qi::symbols<char, multiscale::verification::SubsetSpecificType> {

			SubsetSpecificType_() {
				add
					("clusters"	, SubsetSpecificType::Clusters)
					("regions"	, SubsetSpecificType::Regions)
				;
			}

		} SubsetSpecificTypeParser;


		//! Symbol table and parser for the binary numeric measure type
		struct BinaryNumericMeasureType_ : qi::symbols<char, multiscale::verification::BinaryNumericMeasureType> {

			BinaryNumericMeasureType_() {
				add
					("div"		, BinaryNumericMeasureType::Div)
					("log"		, BinaryNumericMeasureType::Log)
					("minus"	, BinaryNumericMeasureType::Minus)
					("mod"		, BinaryNumericMeasureType::Mod)
					("plus"		, BinaryNumericMeasureType::Plus)
					("power"	, BinaryNumericMeasureType::Power)
					("times"	, BinaryNumericMeasureType::Times)
				;
			}

		} BinaryNumericMeasureTypeParser;

		//! Symbol table and parser for the unary numeric measure type
		struct UnaryNumericMeasureType_ : qi::symbols<char, multiscale::verification::UnaryNumericMeasureType> {

			UnaryNumericMeasureType_() {
				add
					("abs"		, UnaryNumericMeasureType::Abs)
					("ceil"		, UnaryNumericMeasureType::Ceil)
					("floor"	, UnaryNumericMeasureType::Floor)
					("round"	, UnaryNumericMeasureType::Round)
					("sign"		, UnaryNumericMeasureType::Sign)
					("sqrt"		, UnaryNumericMeasureType::Sqrt)
					("trunc"	, UnaryNumericMeasureType::Trunc)
				;
			}

		} UnaryNumericMeasureTypeParser;

		//! Symbol table and parser for the quaternary subset measure type
		struct QuaternarySubsetMeasureType_ : qi::symbols<char, multiscale::verification::QuaternarySubsetMeasureType> {

			QuaternarySubsetMeasureType_() {
				add
					("covar"	, QuaternarySubsetMeasureType::Covar)
				;
			}

		} QuaternarySubsetMeasureTypeParser;

		//! Symbol table and parser for the ternary subset measure type
		struct TernarySubsetMeasureType_ : qi::symbols<char, multiscale::verification::TernarySubsetMeasureType> {

			TernarySubsetMeasureType_() {
				add
					("percentile"	, TernarySubsetMeasureType::Percentile)
					("quartile"		, TernarySubsetMeasureType::Quartile)
				;
			}

		} TernarySubsetMeasureTypeParser;

		//! Symbol table and parser for the binary subset measure type
		struct BinarySubsetMeasureType_ : qi::symbols<char, multiscale::verification::BinarySubsetMeasureType> {

			BinarySubsetMeasureType_() {
				add
					("avg"		, BinarySubsetMeasureType::Avg)
					("geomean"	, BinarySubsetMeasureType::Geomean)
					("harmean"	, BinarySubsetMeasureType::Harmean)
					("kurt"		, BinarySubsetMeasureType::Kurt)
					("max"		, BinarySubsetMeasureType::Max)
					("median"	, BinarySubsetMeasureType::Median)
					("min"		, BinarySubsetMeasureType::Min)
					("mode"		, BinarySubsetMeasureType::Mode)
					("product"	, BinarySubsetMeasureType::Product)
					("skew"		, BinarySubsetMeasureType::Skew)
					("stdev"	, BinarySubsetMeasureType::Stdev)
					("sum"		, BinarySubsetMeasureType::Sum)
					("var"		, BinarySubsetMeasureType::Var)
				;
			}

		} BinarySubsetMeasureTypeParser;

		//! Symbol table and parser for the unary subset measure type
		struct UnarySubsetMeasureType_ : qi::symbols<char, multiscale::verification::UnarySubsetMeasureType> {

			UnarySubsetMeasureType_() {
				add
					("count"			, UnarySubsetMeasureType::Count)
					("clusteredness"	, UnarySubsetMeasureType::Clusteredness)
					("density"			, UnarySubsetMeasureType::Density)
				;
			}

		} UnarySubsetMeasureTypeParser;

	};

};

#endif
