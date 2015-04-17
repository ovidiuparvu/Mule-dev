#ifndef TIMEPOINTSSPATIALENTITIESATTRIBUTESINITIALIZER_HPP
#define TIMEPOINTSSPATIALENTITIESATTRIBUTESINITIALIZER_HPP

/******************************************************************************
 *
 * WARNING! AUTO-GENERATED FILE.
 *
 * PLEASE DO NOT UPDATE THIS FILE MANUALLY. 
 * USE THE PYTHON GENERATOR SCRIPTS FOR ANY MODIFICATIONS.
 *
 *****************************************************************************/
 
#include "NonEmptyTraceEvaluationTest.hpp"

#include "multiscale/verification/spatial-temporal/model/Cluster.hpp"
#include "multiscale/verification/spatial-temporal/model/Region.hpp"

using namespace multiscale;
using namespace multiscaletest;
 

namespace multiscaletest {

    //! Class for initializing spatial entities' attributes in a given collection of timepoints
    class TimepointsSpatialEntitiesAttributesInitializer {

        protected:

            double clustersClusterednessMinValue;          /*!< The minimum clusteredness value for the cluster spatial entity type */
            double clustersClusterednessMaxValue;          /*!< The maximum clusteredness value for the cluster spatial entity type */
            double clustersDensityMinValue;                /*!< The minimum density value for the cluster spatial entity type */
            double clustersDensityMaxValue;                /*!< The maximum density value for the cluster spatial entity type */
            double clustersAreaMinValue;                   /*!< The minimum area value for the cluster spatial entity type */
            double clustersAreaMaxValue;                   /*!< The maximum area value for the cluster spatial entity type */
            double clustersPerimeterMinValue;              /*!< The minimum perimeter value for the cluster spatial entity type */
            double clustersPerimeterMaxValue;              /*!< The maximum perimeter value for the cluster spatial entity type */
            double clustersDistanceFromOriginMinValue;     /*!< The minimum distanceFromOrigin value for the cluster spatial entity type */
            double clustersDistanceFromOriginMaxValue;     /*!< The maximum distanceFromOrigin value for the cluster spatial entity type */
            double clustersAngleMinValue;                  /*!< The minimum angle value for the cluster spatial entity type */
            double clustersAngleMaxValue;                  /*!< The maximum angle value for the cluster spatial entity type */
            double clustersTriangleMeasureMinValue;        /*!< The minimum triangleMeasure value for the cluster spatial entity type */
            double clustersTriangleMeasureMaxValue;        /*!< The maximum triangleMeasure value for the cluster spatial entity type */
            double clustersRectangleMeasureMinValue;       /*!< The minimum rectangleMeasure value for the cluster spatial entity type */
            double clustersRectangleMeasureMaxValue;       /*!< The maximum rectangleMeasure value for the cluster spatial entity type */
            double clustersCircleMeasureMinValue;          /*!< The minimum circleMeasure value for the cluster spatial entity type */
            double clustersCircleMeasureMaxValue;          /*!< The maximum circleMeasure value for the cluster spatial entity type */
            double clustersCentroidXMinValue;              /*!< The minimum centroidX value for the cluster spatial entity type */
            double clustersCentroidXMaxValue;              /*!< The maximum centroidX value for the cluster spatial entity type */
            double clustersCentroidYMinValue;              /*!< The minimum centroidY value for the cluster spatial entity type */
            double clustersCentroidYMaxValue;              /*!< The maximum centroidY value for the cluster spatial entity type */
            double regionsClusterednessMinValue;           /*!< The minimum clusteredness value for the region spatial entity type */
            double regionsClusterednessMaxValue;           /*!< The maximum clusteredness value for the region spatial entity type */
            double regionsDensityMinValue;                 /*!< The minimum density value for the region spatial entity type */
            double regionsDensityMaxValue;                 /*!< The maximum density value for the region spatial entity type */
            double regionsAreaMinValue;                    /*!< The minimum area value for the region spatial entity type */
            double regionsAreaMaxValue;                    /*!< The maximum area value for the region spatial entity type */
            double regionsPerimeterMinValue;               /*!< The minimum perimeter value for the region spatial entity type */
            double regionsPerimeterMaxValue;               /*!< The maximum perimeter value for the region spatial entity type */
            double regionsDistanceFromOriginMinValue;      /*!< The minimum distanceFromOrigin value for the region spatial entity type */
            double regionsDistanceFromOriginMaxValue;      /*!< The maximum distanceFromOrigin value for the region spatial entity type */
            double regionsAngleMinValue;                   /*!< The minimum angle value for the region spatial entity type */
            double regionsAngleMaxValue;                   /*!< The maximum angle value for the region spatial entity type */
            double regionsTriangleMeasureMinValue;         /*!< The minimum triangleMeasure value for the region spatial entity type */
            double regionsTriangleMeasureMaxValue;         /*!< The maximum triangleMeasure value for the region spatial entity type */
            double regionsRectangleMeasureMinValue;        /*!< The minimum rectangleMeasure value for the region spatial entity type */
            double regionsRectangleMeasureMaxValue;        /*!< The maximum rectangleMeasure value for the region spatial entity type */
            double regionsCircleMeasureMinValue;           /*!< The minimum circleMeasure value for the region spatial entity type */
            double regionsCircleMeasureMaxValue;           /*!< The maximum circleMeasure value for the region spatial entity type */
            double regionsCentroidXMinValue;               /*!< The minimum centroidX value for the region spatial entity type */
            double regionsCentroidXMaxValue;               /*!< The maximum centroidX value for the region spatial entity type */
            double regionsCentroidYMinValue;               /*!< The minimum centroidY value for the region spatial entity type */
            double regionsCentroidYMaxValue;               /*!< The maximum centroidY value for the region spatial entity type */

        public:

            TimepointsSpatialEntitiesAttributesInitializer();
            ~TimepointsSpatialEntitiesAttributesInitializer();

            //! Add spatial entities attributes to the provided collection of timepoints
            /*!
             * \param timePoints    The collection of timepoints to which numeric state variables values are added
             */
            void addSpatialEntitiesAttributesToTimepoints(std::vector<mv::TimePoint> &timePoints);

    };


    TimepointsSpatialEntitiesAttributesInitializer::TimepointsSpatialEntitiesAttributesInitializer() 
        : clustersClusterednessMinValue(0),
          clustersClusterednessMaxValue(1),
          clustersDensityMinValue(0),
          clustersDensityMaxValue(1),
          clustersAreaMinValue(0),
          clustersAreaMaxValue(1E+6),
          clustersPerimeterMinValue(0),
          clustersPerimeterMaxValue(1E+6),
          clustersDistanceFromOriginMinValue(0),
          clustersDistanceFromOriginMaxValue(1E+6),
          clustersAngleMinValue(0),
          clustersAngleMaxValue(360),
          clustersTriangleMeasureMinValue(0),
          clustersTriangleMeasureMaxValue(1),
          clustersRectangleMeasureMinValue(0),
          clustersRectangleMeasureMaxValue(1),
          clustersCircleMeasureMinValue(0),
          clustersCircleMeasureMaxValue(1),
          clustersCentroidXMinValue(0),
          clustersCentroidXMaxValue(1E+6),
          clustersCentroidYMinValue(0),
          clustersCentroidYMaxValue(1E+6),
          regionsClusterednessMinValue(0),
          regionsClusterednessMaxValue(1),
          regionsDensityMinValue(0),
          regionsDensityMaxValue(1),
          regionsAreaMinValue(0),
          regionsAreaMaxValue(1E+6),
          regionsPerimeterMinValue(0),
          regionsPerimeterMaxValue(1E+6),
          regionsDistanceFromOriginMinValue(0),
          regionsDistanceFromOriginMaxValue(1E+6),
          regionsAngleMinValue(0),
          regionsAngleMaxValue(360),
          regionsTriangleMeasureMinValue(0),
          regionsTriangleMeasureMaxValue(1),
          regionsRectangleMeasureMinValue(0),
          regionsRectangleMeasureMaxValue(1),
          regionsCircleMeasureMinValue(0),
          regionsCircleMeasureMaxValue(1),
          regionsCentroidXMinValue(0),
          regionsCentroidXMaxValue(1E+6),
          regionsCentroidYMinValue(0),
          regionsCentroidYMaxValue(1E+6) {}

    TimepointsSpatialEntitiesAttributesInitializer::~TimepointsSpatialEntitiesAttributesInitializer() {}

    void TimepointsSpatialEntitiesAttributesInitializer::addSpatialEntitiesAttributesToTimepoints(
        std::vector<mv::TimePoint> &timePoints
    ) {
        std::size_t nrOfTimePoints = timePoints.size();
        
        // Add spatial entities to each timepoint
        for (std::size_t i = 0; i < nrOfTimePoints; i++) {

            // Add clusters with scale and subsystem "Organ.Kidney" to the timepoint
            for (std::size_t j = ((((i + 1) % 4) == 0) ? (i - 1) : 0); j <= i; j++) {
                std::shared_ptr<SpatialEntity> cluster = std::make_shared<Cluster>();

                cluster->setSpatialMeasureValue(SpatialMeasureType::Clusteredness, ((i != 0) ? (static_cast<double>(j) / static_cast<double>(nrOfTimePoints - 1)) : 0) * (clustersClusterednessMaxValue - clustersClusterednessMinValue) + clustersClusterednessMinValue);
                cluster->setSpatialMeasureValue(SpatialMeasureType::Density, (static_cast<double>(1) / static_cast<double>(2)) * (clustersDensityMaxValue - clustersDensityMinValue) + clustersDensityMinValue);
                cluster->setSpatialMeasureValue(SpatialMeasureType::Area, (static_cast<double>(1) / static_cast<double>(2)) * (clustersAreaMaxValue - clustersAreaMinValue) + clustersAreaMinValue);
                cluster->setSpatialMeasureValue(SpatialMeasureType::Perimeter, (static_cast<double>(1) / static_cast<double>(2)) * (clustersPerimeterMaxValue - clustersPerimeterMinValue) + clustersPerimeterMinValue);
                cluster->setSpatialMeasureValue(SpatialMeasureType::DistanceFromOrigin, (static_cast<double>(1) / static_cast<double>(2)) * (clustersDistanceFromOriginMaxValue - clustersDistanceFromOriginMinValue) + clustersDistanceFromOriginMinValue);
                cluster->setSpatialMeasureValue(SpatialMeasureType::Angle, (static_cast<double>(1) / static_cast<double>(2)) * (clustersAngleMaxValue - clustersAngleMinValue) + clustersAngleMinValue);
                cluster->setSpatialMeasureValue(SpatialMeasureType::TriangleMeasure, (static_cast<double>(1) / static_cast<double>(2)) * (clustersTriangleMeasureMaxValue - clustersTriangleMeasureMinValue) + clustersTriangleMeasureMinValue);
                cluster->setSpatialMeasureValue(SpatialMeasureType::RectangleMeasure, (static_cast<double>(1) / static_cast<double>(2)) * (clustersRectangleMeasureMaxValue - clustersRectangleMeasureMinValue) + clustersRectangleMeasureMinValue);
                cluster->setSpatialMeasureValue(SpatialMeasureType::CircleMeasure, (static_cast<double>(1) / static_cast<double>(2)) * (clustersCircleMeasureMaxValue - clustersCircleMeasureMinValue) + clustersCircleMeasureMinValue);
                cluster->setSpatialMeasureValue(SpatialMeasureType::CentroidX, (static_cast<double>(1) / static_cast<double>(2)) * (clustersCentroidXMaxValue - clustersCentroidXMinValue) + clustersCentroidXMinValue);
                cluster->setSpatialMeasureValue(SpatialMeasureType::CentroidY, (static_cast<double>(1) / static_cast<double>(2)) * (clustersCentroidYMaxValue - clustersCentroidYMinValue) + clustersCentroidYMinValue);
                cluster->setScaleAndSubsystem(NonEmptyTraceEvaluationTest::SCALE_AND_SUBSYSTEM_ORGAN_KIDNEY);

                timePoints[i].addSpatialEntityAndType(cluster, SubsetSpecificType::Clusters);
            }
            
            // Add regions with default scale and subsystem to the timepoint
            for (std::size_t k = 0; k <= i; k++) {
                std::shared_ptr<SpatialEntity> region = std::make_shared<Region>();

                region->setSpatialMeasureValue(SpatialMeasureType::Clusteredness, ((i != 0) ? (static_cast<double>(k) / (static_cast<double>(nrOfTimePoints - 1) * 1.2)) : 0) * (regionsClusterednessMaxValue - regionsClusterednessMinValue) + regionsClusterednessMinValue);
                region->setSpatialMeasureValue(SpatialMeasureType::Density, (static_cast<double>(1) / static_cast<double>(3)) * (regionsDensityMaxValue - regionsDensityMinValue) + regionsDensityMinValue);
                region->setSpatialMeasureValue(SpatialMeasureType::Area, (static_cast<double>(1) / static_cast<double>(3)) * (regionsAreaMaxValue - regionsAreaMinValue) + regionsAreaMinValue);
                region->setSpatialMeasureValue(SpatialMeasureType::Perimeter, (static_cast<double>(1) / static_cast<double>(3)) * (regionsPerimeterMaxValue - regionsPerimeterMinValue) + regionsPerimeterMinValue);
                region->setSpatialMeasureValue(SpatialMeasureType::DistanceFromOrigin, (static_cast<double>(1) / static_cast<double>(3)) * (regionsDistanceFromOriginMaxValue - regionsDistanceFromOriginMinValue) + regionsDistanceFromOriginMinValue);
                region->setSpatialMeasureValue(SpatialMeasureType::Angle, (static_cast<double>(1) / static_cast<double>(3)) * (regionsAngleMaxValue - regionsAngleMinValue) + regionsAngleMinValue);
                region->setSpatialMeasureValue(SpatialMeasureType::TriangleMeasure, (static_cast<double>(1) / static_cast<double>(3)) * (regionsTriangleMeasureMaxValue - regionsTriangleMeasureMinValue) + regionsTriangleMeasureMinValue);
                region->setSpatialMeasureValue(SpatialMeasureType::RectangleMeasure, (static_cast<double>(1) / static_cast<double>(3)) * (regionsRectangleMeasureMaxValue - regionsRectangleMeasureMinValue) + regionsRectangleMeasureMinValue);
                region->setSpatialMeasureValue(SpatialMeasureType::CircleMeasure, (static_cast<double>(1) / static_cast<double>(3)) * (regionsCircleMeasureMaxValue - regionsCircleMeasureMinValue) + regionsCircleMeasureMinValue);
                region->setSpatialMeasureValue(SpatialMeasureType::CentroidX, (static_cast<double>(1) / static_cast<double>(3)) * (regionsCentroidXMaxValue - regionsCentroidXMinValue) + regionsCentroidXMinValue);
                region->setSpatialMeasureValue(SpatialMeasureType::CentroidY, (static_cast<double>(1) / static_cast<double>(3)) * (regionsCentroidYMaxValue - regionsCentroidYMinValue) + regionsCentroidYMinValue);
                region->setScaleAndSubsystem(ScaleAndSubsystem::DEFAULT_VALUE);

                timePoints[i].addSpatialEntityAndType(region, SubsetSpecificType::Regions);
            }
            
            // Add regions with scale and subsystem "Organ.Heart" to the timepoint
            for (std::size_t k = 0; k <= i; k++) {
                std::shared_ptr<SpatialEntity> region = std::make_shared<Region>();

                region->setSpatialMeasureValue(SpatialMeasureType::Clusteredness, ((i != 0) ? (static_cast<double>(k) / (static_cast<double>(nrOfTimePoints - 1) * 1.2)) : 0) * (regionsClusterednessMaxValue - regionsClusterednessMinValue) + regionsClusterednessMinValue);
                region->setSpatialMeasureValue(SpatialMeasureType::Density, (static_cast<double>(1) / static_cast<double>(3)) * (regionsDensityMaxValue - regionsDensityMinValue) + regionsDensityMinValue);
                region->setSpatialMeasureValue(SpatialMeasureType::Area, (static_cast<double>(1) / static_cast<double>(3)) * (regionsAreaMaxValue - regionsAreaMinValue) + regionsAreaMinValue);
                region->setSpatialMeasureValue(SpatialMeasureType::Perimeter, (static_cast<double>(1) / static_cast<double>(3)) * (regionsPerimeterMaxValue - regionsPerimeterMinValue) + regionsPerimeterMinValue);
                region->setSpatialMeasureValue(SpatialMeasureType::DistanceFromOrigin, (static_cast<double>(1) / static_cast<double>(3)) * (regionsDistanceFromOriginMaxValue - regionsDistanceFromOriginMinValue) + regionsDistanceFromOriginMinValue);
                region->setSpatialMeasureValue(SpatialMeasureType::Angle, (static_cast<double>(1) / static_cast<double>(3)) * (regionsAngleMaxValue - regionsAngleMinValue) + regionsAngleMinValue);
                region->setSpatialMeasureValue(SpatialMeasureType::TriangleMeasure, (static_cast<double>(1) / static_cast<double>(3)) * (regionsTriangleMeasureMaxValue - regionsTriangleMeasureMinValue) + regionsTriangleMeasureMinValue);
                region->setSpatialMeasureValue(SpatialMeasureType::RectangleMeasure, (static_cast<double>(1) / static_cast<double>(3)) * (regionsRectangleMeasureMaxValue - regionsRectangleMeasureMinValue) + regionsRectangleMeasureMinValue);
                region->setSpatialMeasureValue(SpatialMeasureType::CircleMeasure, (static_cast<double>(1) / static_cast<double>(3)) * (regionsCircleMeasureMaxValue - regionsCircleMeasureMinValue) + regionsCircleMeasureMinValue);
                region->setSpatialMeasureValue(SpatialMeasureType::CentroidX, (static_cast<double>(1) / static_cast<double>(3)) * (regionsCentroidXMaxValue - regionsCentroidXMinValue) + regionsCentroidXMinValue);
                region->setSpatialMeasureValue(SpatialMeasureType::CentroidY, (static_cast<double>(1) / static_cast<double>(3)) * (regionsCentroidYMaxValue - regionsCentroidYMinValue) + regionsCentroidYMinValue);
                region->setScaleAndSubsystem(NonEmptyTraceEvaluationTest::SCALE_AND_SUBSYSTEM_ORGAN_HEART);

                timePoints[i].addSpatialEntityAndType(region, SubsetSpecificType::Regions);
            }
        }
    }

}


#endif