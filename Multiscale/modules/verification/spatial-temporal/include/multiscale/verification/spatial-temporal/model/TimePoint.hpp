#ifndef TIMEPOINT_HPP
#define TIMEPOINT_HPP

#include "multiscale/verification/spatial-temporal/model/Cluster.hpp"
#include "multiscale/verification/spatial-temporal/model/Region.hpp"

#include <list>
#include <map>
#include <string>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing the considered spatial entity type(s)
        enum class ConsideredSpatialEntityType : int {
            All,        /*!< All */
            Clusters,   /*!< Clusters */
            Regions     /*!< Regions */
        };


        //! Class for representing a timepoint
        class TimePoint {

            private:

                double value;   /*!< The value of the timepoint within a simulation/experiment */

                std::list<Cluster>  clusters;     /*!< The list of clusters */
                std::list<Region>   regions;      /*!< The list of regions */

                std::map<std::string, double>   numericStateVariables;      /*!< The associative map for storing numeric state variables */

                ConsideredSpatialEntityType consideredSpatialEntityType;    /*!< The considered spatial entity type */

            public:

                TimePoint(double value = -1);
                ~TimePoint();

                //! Add a cluster to the list of clusters
                /*!
                 * \param cluster The cluster to be added
                 */
                void addCluster(const Cluster &cluster);

                //! Add a region to the list of regions
                /*!
                 * \param region The region to be added
                 */
                void addRegion(const Region &region);

                //! Add a numeric state variable to the map
                /*!
                 * If a numeric state variable with the same name exists then the value
                 * of the existing numeric state variable will be replaced by the provided
                 * new value.
                 *
                 * \param name  The name of the numeric state variable
                 * \param value The value of the numeric state variable
                 */
                void addNumericStateVariable(const std::string &name, double value);

                //! Check if the numeric state variable with the given name exists
                /*!
                 * \param name The name of the numeric state variable
                 */
                bool existsNumericStateVariable(const std::string &name);

                //! Get the list of clusters
                std::list<Cluster> getClusters();

                //! Get the list of regions
                std::list<Region> getRegions();

                //! Get the value of the numeric state variable with the given name if it exists and throw an exception otherwise
                /*!
                 * \param name The name of the numeric state variable
                 */
                double getNumericStateVariable(const std::string &name) const;

                //! Remove the cluster from the given position
                /*!
                 * \param position  The position of the cluster to be removed
                 */
                void removeCluster(const std::list<Cluster>::iterator &position);

                //! Remove the region from the given position
                /*!
                 * \param position  The position of the region to be removed
                 */
                void removeRegion(const std::list<Region>::iterator &position);

                //! Set the considered spatial entity type
                /*!
                 * \param consideredSpatialEntityType   The considered type of the spatial entities
                 */
                void setConsideredSpatialEntityType(const ConsideredSpatialEntityType &consideredSpatialEntityType);

                //! Construct the error message
                /*!
                 * \param errorString   The error string which will be enclosed by the error prefix and suffix
                 */
                std::string constructErrorMessage(const std::string &errorString) const;

            private:

                // Constants
                static const std::string ERR_GET_NUMERIC_STATE_VARIABLE_PREFIX;
                static const std::string ERR_GET_NUMERIC_STATE_VARIABLE_SUFFIX;

        };

    };

};

#endif
