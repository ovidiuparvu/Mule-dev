#ifndef TIMEPOINT_HPP
#define TIMEPOINT_HPP

#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SubsetOperationAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SubsetSpecificAttribute.hpp"
#include "multiscale/verification/spatial-temporal/model/NumericStateVariableId.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialEntity.hpp"

#include <bitset>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>


namespace multiscale {

    namespace verification {

        //! Class for representing a timepoint
        class TimePoint {

            private:

                unsigned long value;   /*!< The value of the timepoint within a simulation/experiment */

                /*
                 * TODO: Update Timepoint class if no longer validating input XML files
                 *
                 *  WARNING: The Timepoint class contains as a member a list of spatial entities
                 *           because the uniqueness of the spatial entities is determined using XML
                 *           input file validation. If this validation is no longer used then replace the list
                 *           in the Timepoint class with a set in order to ensure the uniqueness of
                 *           the spatial entities.
                 */
                std::vector<std::list<std::shared_ptr<SpatialEntity>>>
                    spatialEntities;                /*!< The meta-list of spatial entities smart pointers.
                                                         The i-th spatial entities list in the meta-list
                                                         corresponds to the i-th SubsetSpecificType
                                                         enumeration value */

                std::map<NumericStateVariableId, double>
                    numericStateVariables;          /*!< The associative map for storing numeric state variables */

                std::bitset<NR_SUBSET_SPECIFIC_TYPES>
                    consideredSpatialEntityTypes;   /*!< The collection of bits recording the considered
                                                         spatial entity types. The i-th bit corresponds to the
                                                         i-th SubsetSpecificType enum value. If the bit is set
                                                         true then the corresponding subset specific type is
                                                         considered. Otherwise it is not. */

            public:

                TimePoint(unsigned long value = std::numeric_limits<unsigned long>::max());
                TimePoint(const TimePoint &timePoint);
                ~TimePoint();

                //! Get the value of the timepoint
                unsigned long getValue() const;

                //! Set the value of the timepoint
                /*!
                 * \param value The value of the timepoint
                 */
                void setValue(unsigned long value);

                //! Get the considered spatial entity type
                std::bitset<NR_SUBSET_SPECIFIC_TYPES> getConsideredSpatialEntityTypes();

                //! Set the considered spatial entity type to the given type
                /*! The flag corresponding to the given spatial entity type is set to 1 and all others
                 *  are set to 0.
                 *
                 * \param consideredSpatialEntityType   The considered type of the spatial entities
                 */
                void setConsideredSpatialEntityType(const SubsetSpecificType &consideredSpatialEntityType);

                //! Add the given type to the collection of considered spatial entity types
                /*! The flag corresponding to the given spatial entity type is set to 1 and all other flags
                 *  will keep their previous value.
                 *
                 *  \param consideredSpatialEntityType  The considered spatial entity type
                 */
                void addConsideredSpatialEntityType(const SubsetSpecificType &consideredSpatialEntityType);

                //! Get the number of considered spatial entities
                double numberOfSpatialEntities() const;

                //! Add a spatial entity of the given type to the list of spatial entities
                /*! This method does not update the considered spatial entity types. If the considered spatial
                 *  entity types should be updated then use the addSpatialEntityAndType() method instead.
                 *
                 * \param spatialEntity         The spatial entity
                 * \param spatialEntityType     The type of the spatial entity
                 */
                void addSpatialEntity(const std::shared_ptr<SpatialEntity> &spatialEntity,
                                      const SubsetSpecificType &spatialEntityType);

                //! Add a spatial entity and its corresponding type to the timepoint
                /*! The spatial entity is added to the timepoint and the corresponding spatial entity type flag is set
                 *  to true in the collection of considered spatial entity types.
                 *
                 * \param spatialEntity         The spatial entity
                 * \param spatialEntityType     The type of the spatial entity
                 */
                void addSpatialEntityAndType(const std::shared_ptr<SpatialEntity> &spatialEntity,
                                             const SubsetSpecificType &spatialEntityType);

                //! Add a numeric state variable to the map
                /*!
                 * If a numeric state variable with the same id exists then the value
                 * of the existing numeric state variable will be replaced by the provided
                 * new value.
                 *
                 * \param id    The id (name, type) of the numeric state variable
                 * \param value The value of the numeric state variable
                 */
                void addNumericStateVariable(const NumericStateVariableId &id, double value);

                //! Check if the numeric state variable with the given id exists
                /*!
                 * \param id The id of the numeric state variable
                 */
                bool containsNumericStateVariable(const NumericStateVariableId &id);

                //! Check if the numeric state variable with the given id exists
                /*!
                 * \param id The id of the numeric state variable
                 */
                bool containsNumericStateVariable(const NumericStateVariableId &id) const;

                //! Check if an identical valued spatial entity is already contained by the timepoint
                /*!
                 * \param spatialEntity     The considered spatial entity
                 * \param spatialEntityType The type of the spatial entity
                 */
                bool containsSpatialEntity(const std::shared_ptr<SpatialEntity> &spatialEntity,
                                           const SubsetSpecificType &spatialEntityType);

                //! Check if an identical valued spatial entity is already contained by the timepoint
                /*!
                 * \param spatialEntity             The considered spatial entity
                 * \param spatialEntityTypeIndex    The index of the spatial entity type
                 */
                bool containsSpatialEntity(const std::shared_ptr<SpatialEntity> &spatialEntity,
                                           const std::size_t &spatialEntityTypeIndex);

                //! Check if an identical valued spatial entity is already contained by the timepoint
                /*!
                 * \param spatialEntity     The considered spatial entity
                 * \param spatialEntityType The type of the spatial entity
                 */
                bool containsSpatialEntity(const std::shared_ptr<SpatialEntity> &spatialEntity,
                                           const SubsetSpecificType &spatialEntityType) const;

                //! Check if an identical valued spatial entity is already contained by the timepoint
                /*!
                 * \param spatialEntity             The considered spatial entity
                 * \param spatialEntityTypeIndex    The index of the spatial entity type
                 */
                bool containsSpatialEntity(const std::shared_ptr<SpatialEntity> &spatialEntity,
                                           const std::size_t &spatialEntityTypeIndex) const;

                //! Get the begin iterator for the spatial entities of the given type
                /*!
                 * Return the spatial entities begin iterator if the considered spatial entity
                 * type is of the given type. Otherwise return the spatial entities end
                 * iterator.
                 *
                 * \param spatialEntityType The type of the spatial entities
                 */
                std::list<std::shared_ptr<SpatialEntity>>::iterator
                getSpatialEntitiesBeginIterator(const SubsetSpecificType &spatialEntityType);

                //! Get the begin iterator for the spatial entities corresponding to the given type index
                /*!
                 * Return the spatial entities begin iterator if the considered spatial entity
                 * type is of the given type. Otherwise return the spatial entities end
                 * iterator.
                 *
                 * \param spatialEntityTypeIndex    The index of the the spatial entities type
                 */
                std::list<std::shared_ptr<SpatialEntity>>::iterator
                getSpatialEntitiesBeginIterator(const std::size_t &spatialEntityTypeIndex);

                //! Get the begin iterator for the spatial entities of the given type
                /*!
                 * Return the spatial entities begin iterator if the considered spatial entity
                 * type is of the given type. Otherwise return the spatial entities end
                 * iterator.
                 *
                 * \param spatialEntityType The type of the spatial entities
                 */
                std::list<std::shared_ptr<SpatialEntity>>::const_iterator
                getSpatialEntitiesBeginIterator(const SubsetSpecificType &spatialEntityType) const;

                //! Get the begin iterator for the spatial entities corresponding to the given type index
                /*!
                 * Return the spatial entities begin iterator if the considered spatial entity
                 * type is of the given type. Otherwise return the spatial entities end
                 * iterator.
                 *
                 * \param spatialEntityTypeIndex    The index of the the spatial entities type
                 */
                std::list<std::shared_ptr<SpatialEntity>>::const_iterator
                getSpatialEntitiesBeginIterator(const std::size_t &spatialEntityTypeIndex) const;

                //! Get the end iterator for the spatial entities of the given type
                /*!
                 * \param spatialEntityType The type of the spatial entities
                 */
                std::list<std::shared_ptr<SpatialEntity>>::iterator
                getSpatialEntitiesEndIterator(const SubsetSpecificType &spatialEntityType);

                //! Get the end iterator for the spatial entities corresponding to the given type index
                /*!
                 * \param spatialEntityTypeIndex    The index of the spatial entities type
                 */
                std::list<std::shared_ptr<SpatialEntity>>::iterator
                getSpatialEntitiesEndIterator(const std::size_t &spatialEntityTypeIndex);

                //! Get the end iterator for the spatial entities of the given type
                /*!
                 * \param spatialEntityType The type of the spatial entities
                 */
                std::list<std::shared_ptr<SpatialEntity>>::const_iterator
                getSpatialEntitiesEndIterator(const SubsetSpecificType &spatialEntityType) const;

                //! Get the end iterator for the spatial entities corresponding to the given type index
                /*!
                 * \param spatialEntityTypeIndex    The index of the spatial entities type
                 */
                std::list<std::shared_ptr<SpatialEntity>>::const_iterator
                getSpatialEntitiesEndIterator(const std::size_t &spatialEntityTypeIndex) const;

                //! Get the collection of considered spatial entities
                std::vector<std::shared_ptr<SpatialEntity>> getConsideredSpatialEntities() const;

                //! Get the value of the numeric state variable with the given id
                /*! Get the value of the numeric state variable with the given id if it exists and
                 *  throw an exception otherwise
                 *
                 * \param id The id of the numeric state variable
                 */
                double getNumericStateVariableValue(const NumericStateVariableId &id) const;

                //! Get the begin iterator for the collection of numeric state variables
                std::map<NumericStateVariableId, double>::iterator
                getNumericStateVariablesBeginIterator();

                //! Get the begin iterator for the collection of numeric state variables
                std::map<NumericStateVariableId, double>::const_iterator
                getNumericStateVariablesBeginIterator() const;

                //! Get the end iterator for the collection of numeric state variables
                std::map<NumericStateVariableId, double>::iterator
                getNumericStateVariablesEndIterator();

                //! Get the end iterator for the collection of numeric state variables
                std::map<NumericStateVariableId, double>::const_iterator
                getNumericStateVariablesEndIterator() const;

                //! Compute the difference of this timepoint and the given timepoint (spatial entities only)
                /*! Compute the difference of this timepoint and the given timepoint by taking into account
                 *  the value of consideredSpatialEntityType
                 *
                 *  Spatial entities belonging to the first and not to the second timepoint will be
                 *  included in the resulting timepoint.
                 *
                 *  The consideredSpatialEntityType of the resulting timepoint will be the consideredSpatialEntityType
                 *  of this timepoint.
                 *
                 * \param timePoint The given timepoint
                 */
                void timePointDifference(const TimePoint &timePoint);

                //! Compute the intersection of this timepoint and the given timepoint (spatial entities only)
                /*! Compute the intersection of this timepoint and the given timepoint by taking into account
                 *  the value of consideredSpatialEntityType
                 *
                 *  Spatial entities belonging both to the first and the second timepoint will be
                 *  included in the resulting timepoint.
                 *
                 *  The consideredSpatialEntityType of the resulting timepoint will be the intersection of the
                 *  timepoints' consideredSpatialEntityTypes.
                 *
                 * \param timePoint The given timepoint
                 */
                void timePointIntersection(const TimePoint &timePoint);

                //! Compute the union of this timepoint and the given timepoint (spatial entities only)
                /*! Compute the union of this timepoint and the given timepoint by taking into account
                 *  the value of consideredSpatialEntityType.
                 *
                 *  Spatial entities belonging either to the first or the second timepoint will be
                 *  included in the resulting timepoint.
                 *
                 *  The consideredSpatialEntityType of the resulting timepoint will be the union of the
                 *  timepoints' consideredSpatialEntityTypes.
                 *
                 * \param timePoint The given timepoint
                 */
                void timePointUnion(const TimePoint &timePoint);

                //! Remove the spatial entity of the given type from the given position
                /*!
                 * \param position          The position of the spatial entity to be removed
                 * \param spatialEntityType The type of the spatial entity
                 */
                std::list<std::shared_ptr<SpatialEntity>>::iterator
                removeSpatialEntity(std::list<std::shared_ptr<SpatialEntity>>::iterator &position,
                                    const SubsetSpecificType &spatialEntityType);

                //! Check if two timepoints (this instance and the provided one) are equal
                /*!
                 * \param rhsTimepoint  The provided timepoint against which this timepoint is compared
                 */
                bool operator==(const TimePoint &rhsTimepoint);

                //! Check if two timepoints (this instance and the provided one) are different (i.e. not equal)
                /*!
                 * \param rhsTimepoint  The provided timepoint against which this timepoint is compared
                 */
                bool operator!=(const TimePoint &rhsTimepoint);

            private:

                //! Compute the given set operation of this timepoint and the given timepoint considering the given set operation type
                /*!
                 * \param timePoint         The given timepoint
                 * \param setOperationType  The considered set operation type
                 */
                void timePointSetOperation(const TimePoint &timePoint, const SubsetOperationType &setOperationType);

                //! Apply the set operation to the collection of spatial entities from this and the given timepoint
                /*!
                 * \param timePoint         The given timepoint
                 * \param setOperationType  The considered set operation type
                 */
                void updateSpatialEntities(const TimePoint &timePoint, const SubsetOperationType &setOperationType);

                //! Compute the given set operation on the set of spatial entities of the given type from this and the provided timepoint
                /*!
                 * \param timePoint                 The given timepoint
                 * \param setOperationType          The considered set operation type
                 * \param spatialEntityTypeIndex    The considered spatial entity type index
                 */
                std::list<std::shared_ptr<SpatialEntity>>
                spatialEntitiesSetOperation(const TimePoint &timePoint, const SubsetOperationType &setOperationType,
                                            const SubsetSpecificType &spatialEntityTypeIndex);

                //! Update the considered spatial entity type of this timepoint considering the given setOperationType and consideredSpatialEntityTypes
                /*
                 * The i-th considered spatial entity type of this timepoint is updated depending on the given
                 * setOperationType as follows:
                 *     - Difference:    consideredSpatialEntityType(thisTimePoint) = consideredSpatialEntityType(thisTimePoint)
                 *     - Intersection:  consideredSpatialEntityType(thisTimePoint) = consideredSpatialEntityType(thisTimePoint) AND
                 *                                                                   consideredSpatialEntityType(givenTimePoint)
                 *     - Union:         consideredSpatialEntityType(thisTimePoint) = consideredSpatialEntityType(thisTimePoint) OR
                 *                                                                   consideredSpatialEntityType(thisTimePoint)
                 *
                 * \param consideredSpatialEntityTypes  The considered spatial entity types
                 * \param setOperationType              The considered set operation type
                 */
                void updateConsideredSpatialEntityTypes(const std::bitset<NR_SUBSET_SPECIFIC_TYPES> &consideredSpatialEntityTypes,
                                                        const SubsetOperationType &setOperationType);

                /*! Check if this and the provided timepoint contain the same numeric state variables
                 *
                 * \param rhsTimepoint  The timepoint against which this timepoint's numeric state variables
                 *                      are compared
                 */
                bool areEqualNumericStateVariables(const TimePoint &rhsTimepoint);

                //! Check if this and the provided timepoint contain the same spatial entities
                /*!
                 * \param rhsTimepoint  The timepoint against which this timepoint's numeric state variables
                 *                      are compared
                 */
                bool areEqualSpatialEntities(const TimePoint &rhsTimepoint);

                //! Check if this and the provided timepoint contain the same spatial entities of the given type
                /*!
                 * \param rhsTimepoint              The timepoint against which this timepoint's numeric state
                 *                                  variables are compared
                 * \param spatialEntityTypeIndex    The index of the considered spatial entity type
                 */
                bool areEqualSpatialEntitiesOfSpecificType(const TimePoint &rhsTimepoint,
                                                           const std::size_t &spatialEntityTypeIndex);


                // Constants
                static const std::string ERR_GET_NUMERIC_STATE_VARIABLE_PREFIX;
                static const std::string ERR_GET_NUMERIC_STATE_VARIABLE_SUFFIX;

        };

    };

};


#endif
