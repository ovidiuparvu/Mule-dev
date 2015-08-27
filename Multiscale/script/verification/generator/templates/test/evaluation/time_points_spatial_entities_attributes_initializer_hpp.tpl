#ifndef TIMEPOINTSSPATIALENTITIESATTRIBUTESINITIALIZER_HPP
#define TIMEPOINTSSPATIALENTITIESATTRIBUTESINITIALIZER_HPP

/******************************************************************************
/*{% for line in auto_generated_warning %}*/
 /*{{ line }}*/
/*{% endfor %}*/
 *****************************************************************************/
 
#include "NonEmptyTraceEvaluationTest.hpp"

/*{% for spatial_entity in spatial_entities %}*/
#include "multiscale/verification/spatial-temporal/model//*{{ spatial_entity.name|first_to_upper }}*/.hpp"
/*{% endfor %}*/

using namespace multiscale;
using namespace multiscaletest;
 

namespace multiscaletest {

    //! Class for initializing spatial entities' attributes in a given collection of time points
    class TimePointsSpatialEntitiesAttributesInitializer {

        protected:

    /*{% for spatial_entity in spatial_entities %}*/
        /*{% for spatial_measure in spatial_measures %}*/
            double /*{{ "%-38s"|format(spatial_entity.name + "s" + spatial_measure.name|first_to_upper + "MinValue;") }}*/  /*!< The minimum /*{{ spatial_measure.name }}*/ value for the /*{{ spatial_entity.name }}*/ spatial entity type */
            double /*{{ "%-38s"|format(spatial_entity.name + "s" + spatial_measure.name|first_to_upper + "MaxValue;") }}*/  /*!< The maximum /*{{ spatial_measure.name }}*/ value for the /*{{ spatial_entity.name }}*/ spatial entity type */
        /*{% endfor %}*/
    /*{% endfor %}*/

        public:

            TimePointsSpatialEntitiesAttributesInitializer();
            ~TimePointsSpatialEntitiesAttributesInitializer();

            //! Add spatial entities attributes to the provided collection of time points
            /*!
             * \param timePoints    The collection of time points to which numeric state variables values are added
             */
            void addSpatialEntitiesAttributesToTimePoints(std::vector<mv::TimePoint> &timePoints);

    };


    TimePointsSpatialEntitiesAttributesInitializer::TimePointsSpatialEntitiesAttributesInitializer()
        : /*{{ spatial_entities[0].name ~ "s" ~ spatial_measures[0].name|first_to_upper ~ "MinValue" }}*/(/*{{ spatial_measures[0].min_value }}*/),
          /*{{ spatial_entities[0].name ~ "s" ~ spatial_measures[0].name|first_to_upper ~ "MaxValue" }}*/(/*{{ spatial_measures[0].max_value }}*/),
    /*{% for spatial_measure in spatial_measures[1:] %}*/
          /*{{ spatial_entities[0].name ~ "s" ~ spatial_measure.name|first_to_upper ~ "MinValue" }}*/(/*{{ spatial_measure.min_value }}*/),
          /*{{ spatial_entities[0].name ~ "s" ~ spatial_measure.name|first_to_upper ~ "MaxValue" }}*/(/*{{ spatial_measure.max_value }}*/),
    /*{% endfor %}*/
/*{% for spatial_entity in spatial_entities[1:-1] %}*/
    /*{% for spatial_measure in spatial_measures %}*/
          /*{{ spatial_entity.name ~ "s" ~ spatial_measure.name|first_to_upper ~ "MinValue" }}*/(/*{{ spatial_measure.min_value }}*/),
          /*{{ spatial_entity.name ~ "s" ~ spatial_measure.name|first_to_upper ~ "MaxValue" }}*/(/*{{ spatial_measure.max_value }}*/),
    /*{% endfor %}*/
/*{% endfor %}*/
    /*{% for spatial_measure in spatial_measures[:-1] %}*/
          /*{{ spatial_entities[-1].name ~ "s" ~ spatial_measure.name|first_to_upper ~ "MinValue" }}*/(/*{{ spatial_measure.min_value }}*/),
          /*{{ spatial_entities[-1].name ~ "s" ~ spatial_measure.name|first_to_upper ~ "MaxValue" }}*/(/*{{ spatial_measure.max_value }}*/),
    /*{% endfor %}*/
          /*{{ spatial_entities[-1].name ~ "s" ~ spatial_measures[-1].name|first_to_upper ~ "MinValue" }}*/(/*{{ spatial_measures[-1].min_value }}*/),
          /*{{ spatial_entities[-1].name ~ "s" ~ spatial_measures[-1].name|first_to_upper ~ "MaxValue" }}*/(/*{{ spatial_measures[-1].max_value }}*/) {}

    TimePointsSpatialEntitiesAttributesInitializer::~TimePointsSpatialEntitiesAttributesInitializer() {}

    void TimePointsSpatialEntitiesAttributesInitializer::addSpatialEntitiesAttributesToTimePoints(
        std::vector<mv::TimePoint> &timePoints
    ) {
        std::size_t nrOfTimePoints = timePoints.size();
        
        // Add spatial entities to each time point
        for (std::size_t i = 0; i < nrOfTimePoints; i++) {

            // Add /*{{ spatial_entities[0].name }}*/s with scale and subsystem "Organ.Kidney" to the time point
            for (std::size_t j = ((((i + 1) % 4) == 0) ? (i - 1) : 0); j <= i; j++) {
                std::shared_ptr<SpatialEntity> /*{{ spatial_entities[0].name }}*/ = std::make_shared</*{{ spatial_entities[0].name|first_to_upper }}*/>();

                /*{{ spatial_entities[0].name }}*/->setSpatialMeasureValue(SpatialMeasureType::/*{{ spatial_measures[0].name|first_to_upper }}*/, ((i != 0) ? (static_cast<double>(j) / static_cast<double>(nrOfTimePoints - 1)) : 0) * (/*{{ spatial_entities[0].name ~ "s" ~ spatial_measures[0].name|first_to_upper ~ "MaxValue" }}*/ - /*{{ spatial_entities[0].name ~ "s" ~ spatial_measures[0].name|first_to_upper ~ "MinValue" }}*/) + /*{{ spatial_entities[0].name ~ "s" ~ spatial_measures[0].name|first_to_upper ~ "MinValue" }}*/);
            /*{% for spatial_measure in spatial_measures[1:] %}*/
                /*{{ spatial_entities[0].name }}*/->setSpatialMeasureValue(SpatialMeasureType::/*{{ spatial_measure.name|first_to_upper }}*/, (static_cast<double>(1) / static_cast<double>(2)) * (/*{{ spatial_entities[0].name ~ "s" ~ spatial_measure.name|first_to_upper ~ "MaxValue" }}*/ - /*{{ spatial_entities[0].name ~ "s" ~ spatial_measure.name|first_to_upper ~ "MinValue" }}*/) + /*{{ spatial_entities[0].name ~ "s" ~ spatial_measure.name|first_to_upper ~ "MinValue" }}*/);
            /*{% endfor %}*/
                /*{{ spatial_entities[0].name }}*/->setScaleAndSubsystem(NonEmptyTraceEvaluationTest::SCALE_AND_SUBSYSTEM_ORGAN_KIDNEY);

                timePoints[i].addSpatialEntityAndType(/*{{ spatial_entities[0].name }}*/, SubsetSpecificType::/*{{ spatial_entities[0].name|first_to_upper }}*/s);
            }
            
        /*{% for spatial_entity in spatial_entities[1:] %}*/
            // Add /*{{ spatial_entity.name }}*/s with default scale and subsystem to the time point
            for (std::size_t k = 0; k <= i; k++) {
                std::shared_ptr<SpatialEntity> /*{{ spatial_entity.name }}*/ = std::make_shared</*{{ spatial_entity.name|first_to_upper }}*/>();

                /*{{ spatial_entity.name }}*/->setSpatialMeasureValue(SpatialMeasureType::/*{{ spatial_measures[0].name|first_to_upper }}*/, ((i != 0) ? (static_cast<double>(k) / (static_cast<double>(nrOfTimePoints - 1) * 1.2)) : 0) * (/*{{ spatial_entity.name ~ "s" ~ spatial_measures[0].name|first_to_upper ~ "MaxValue" }}*/ - /*{{ spatial_entity.name ~ "s" ~ spatial_measures[0].name|first_to_upper ~ "MinValue" }}*/) + /*{{ spatial_entity.name ~ "s" ~ spatial_measures[0].name|first_to_upper ~ "MinValue" }}*/);
            /*{% for spatial_measure in spatial_measures[1:] %}*/
                /*{{ spatial_entity.name }}*/->setSpatialMeasureValue(SpatialMeasureType::/*{{ spatial_measure.name|first_to_upper }}*/, (static_cast<double>(1) / static_cast<double>(3)) * (/*{{ spatial_entity.name ~ "s" ~ spatial_measure.name|first_to_upper ~ "MaxValue" }}*/ - /*{{ spatial_entity.name ~ "s" ~ spatial_measure.name|first_to_upper ~ "MinValue" }}*/) + /*{{ spatial_entity.name ~ "s" ~ spatial_measure.name|first_to_upper ~ "MinValue" }}*/);
            /*{% endfor %}*/
                /*{{ spatial_entity.name }}*/->setScaleAndSubsystem(ScaleAndSubsystem::DEFAULT_VALUE);

                timePoints[i].addSpatialEntityAndType(/*{{ spatial_entity.name }}*/, SubsetSpecificType::/*{{ spatial_entity.name|first_to_upper }}*/s);
            }
            
            // Add /*{{ spatial_entity.name }}*/s with scale and subsystem "Organ.Heart" to the time point
            for (std::size_t k = 0; k <= i; k++) {
                std::shared_ptr<SpatialEntity> /*{{ spatial_entity.name }}*/ = std::make_shared</*{{ spatial_entity.name|first_to_upper }}*/>();

                /*{{ spatial_entity.name }}*/->setSpatialMeasureValue(SpatialMeasureType::/*{{ spatial_measures[0].name|first_to_upper }}*/, ((i != 0) ? (static_cast<double>(k) / (static_cast<double>(nrOfTimePoints - 1) * 1.2)) : 0) * (/*{{ spatial_entity.name ~ "s" ~ spatial_measures[0].name|first_to_upper ~ "MaxValue" }}*/ - /*{{ spatial_entity.name ~ "s" ~ spatial_measures[0].name|first_to_upper ~ "MinValue" }}*/) + /*{{ spatial_entity.name ~ "s" ~ spatial_measures[0].name|first_to_upper ~ "MinValue" }}*/);
            /*{% for spatial_measure in spatial_measures[1:] %}*/
                /*{{ spatial_entity.name }}*/->setSpatialMeasureValue(SpatialMeasureType::/*{{ spatial_measure.name|first_to_upper }}*/, (static_cast<double>(1) / static_cast<double>(3)) * (/*{{ spatial_entity.name ~ "s" ~ spatial_measure.name|first_to_upper ~ "MaxValue" }}*/ - /*{{ spatial_entity.name ~ "s" ~ spatial_measure.name|first_to_upper ~ "MinValue" }}*/) + /*{{ spatial_entity.name ~ "s" ~ spatial_measure.name|first_to_upper ~ "MinValue" }}*/);
            /*{% endfor %}*/
                /*{{ spatial_entity.name }}*/->setScaleAndSubsystem(NonEmptyTraceEvaluationTest::SCALE_AND_SUBSYSTEM_ORGAN_HEART);

                timePoints[i].addSpatialEntityAndType(/*{{ spatial_entity.name }}*/, SubsetSpecificType::/*{{ spatial_entity.name|first_to_upper }}*/s);
            }
        /*{% endfor %}*/
        }
    }

}


#endif
