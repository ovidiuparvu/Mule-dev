#ifndef SYMBOLTABLES_HPP
#define SYMBOLTABLES_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SubsetSpecificAttribute.hpp"

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

	};

};

#endif
