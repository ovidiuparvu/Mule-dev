#ifndef SYNTHESIZEDATTRIBUTE_HPP
#define SYNTHESIZEDATTRIBUTE_HPP

/*
 * File for including (in)directly all the synthesized attribute types.
 *
 * The reason for creating this file is that some of the includes below cannot be
 * specified directly in the files where they are used because they cause circular
 * include dependencies.
 */

// Include forward declared types

#include <multiscale/verification/spatial-temporal/attribute/HomogeneousHomogeneousTimeSeriesAttribute.hpp>
#include "multiscale/verification/spatial-temporal/attribute/NotLogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/FutureLogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/GlobalLogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NextLogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NextKLogicPropertyAttribute.hpp"

#include "multiscale/verification/spatial-temporal/attribute/OrLogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/AndLogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ImplicationLogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/EquivalenceLogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UntilLogicPropertyAttribute.hpp"

#include "multiscale/verification/spatial-temporal/attribute/PrimaryLogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericComparisonAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ChangeTemporalNumericMeasureAttribute.hpp"

#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericTemporalAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/BinaryNumericTemporalAttribute.hpp"

#include "multiscale/verification/spatial-temporal/attribute/ChangeTemporalNumericCollectionAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/TimeSeriesTimeSeriesComponentAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/PrimaryNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericNumericAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/BinaryNumericNumericAttribute.hpp"

#include "multiscale/verification/spatial-temporal/attribute/NumericSpatialMeasureAttribute.hpp"

#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericSpatialAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/BinaryNumericSpatialAttribute.hpp"

#include "multiscale/verification/spatial-temporal/attribute/PrimaryConstraintAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NotConstraintAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/OrConstraintAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/AndConstraintAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ImplicationConstraintAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/EquivalenceConstraintAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnarySpatialConstraintAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnaryScaleAndSubsystemConstraintAttribute.hpp"

#include "multiscale/verification/spatial-temporal/attribute/SubsetSubsetOperationAttribute.hpp"

#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericFilterAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/BinaryNumericFilterAttribute.hpp"

#endif
