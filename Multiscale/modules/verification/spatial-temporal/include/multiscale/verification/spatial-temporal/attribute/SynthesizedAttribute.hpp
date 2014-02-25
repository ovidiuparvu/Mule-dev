#ifndef SYNTHESIZEDATTRIBUTE_HPP
#define SYNTHESIZEDATTRIBUTE_HPP

/*
 * File for including (in)directly all the synthesized attribute types
 */

// Include types

#include "multiscale/verification/spatial-temporal/attribute/ProbabilisticLogicPropertyAttribute.hpp"

// Include forward declared types

#include "multiscale/verification/spatial-temporal/attribute/Nil.hpp"

#include "multiscale/verification/spatial-temporal/attribute/PrimaryLogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/DifferenceAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericNumericComparisonAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericSpatialNumericComparisonAttribute.hpp"

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

#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericNumericAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/BinaryNumericNumericAttribute.hpp"

#include "multiscale/verification/spatial-temporal/attribute/PrimaryConstraintAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NotConstraintAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/OrConstraintAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/AndConstraintAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ImplicationConstraintAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/EquivalenceConstraintAttribute.hpp"

#endif
