#ifndef SPATIALMEASURETYPE_HPP
#define SPATIALMEASURETYPE_HPP

/******************************************************************************
/*{% for line in auto_generated_warning %}*/
 /*{{ line }}*/
/*{% endfor %}*/
 *****************************************************************************/
 
 
namespace multiscale {

    namespace verification {

        //! Enumeration for representing the types of spatial measures
        enum class SpatialMeasureType : unsigned int {
            /*{{ "%-33s"|format(spatial_measures[0].name|first_to_upper) }}*/ = 0,    /*!< /*{{ spatial_measures[0].description }}*/ */
            /*{% for spatial_measure in spatial_measures[1:] %}*/
            /*{{ "%-33s"|format(spatial_measure.name|first_to_upper) }}*/    ,    /*!< /*{{ spatial_measure.description }}*/ */
            /*{% endfor %}*/
            /*{{ "%-33s"|format("NrOfSpatialMeasureTypeEntries") }}*/         /*!< Enumeration type used to store the number of
            /*{{ "%-33s"|format(" ") }}*/              elements in the enumeration. Always leave it last! */
        };

    };

};


#endif