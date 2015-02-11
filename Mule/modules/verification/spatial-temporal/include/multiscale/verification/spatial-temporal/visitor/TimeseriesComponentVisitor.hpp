#ifndef TIMESERIESCOMPONENTVISITOR_HPP
#define TIMESERIESCOMPONENTVISITOR_HPP

#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/verification/spatial-temporal/attribute/TimeseriesComponentAttribute.hpp"
#include "multiscale/verification/spatial-temporal/visitor/TimeseriesComponentEvaluator.hpp"

#include <boost/variant.hpp>
#include <functional>


namespace multiscale {

    namespace verification {

        //! Class for evaluating timeseries components
        /*!
         * The output values of the visitor is a collection of indices pointing to the
         * start and end positions of the timeseries components identified in the given collection of
         * values. In case of heterogeneous timeseries components the start position = end position,
         * while in the case of homogeneous timeseries components start position != end position.
         */
        class TimeseriesComponentVisitor : public boost::static_visitor<std::vector<std::size_t>> {

            private:

                const std::vector<double> &values;   /*!< The collection of considered values */

            public:

                TimeseriesComponentVisitor(const std::vector<double> &values) : values(values) {}

                //! Overloading the "()" operator for the HeterogeneousTimeseriesComponentAttribute alternative
                /*!
                 * \param heterogeneousTimeseriesComponent  The heterogeneous timeseries component
                 */
                std::vector<std::size_t>
                operator()(const HeterogeneousTimeseriesComponentAttribute &heterogeneousTimeseriesComponent) const {
                    switch (heterogeneousTimeseriesComponent.heterogeneousTimeseriesComponent) {
                        case HeterogeneousTimeseriesComponentType::Peak:
                            return duplicateCollectionElements(
                                evaluateHeterogeneousComponentsIndices(values, std::less<double>())
                            );
                            break;

                        case HeterogeneousTimeseriesComponentType::Valley:
                            return duplicateCollectionElements(
                                evaluateHeterogeneousComponentsIndices(values, std::greater<double>())
                            );
                            break;

                        default:
                            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
                    }

                    // Line added to avoid "control reaches end of non-void function" warnings
                    return std::vector<std::size_t>();
                }

                //! Overloading the "()" operator for the HomogeneousTimeseriesComponentAttribute alternative
                /*!
                 * \param homogeneousTimeseriesComponent  The homogeneous timeseries component
                 */
                std::vector<std::size_t>
                operator()(const HomogeneousTimeseriesComponentAttribute &homogeneousTimeseriesComponent) const {
                    return TimeseriesComponentEvaluator::evaluate(
                        homogeneousTimeseriesComponent,
                        values
                    );
                }

            private:

                //! Duplicate each element in the given indices collection
                std::vector<std::size_t>
                duplicateCollectionElements(const std::vector<std::size_t> &collection) const {
                    std::vector<std::size_t> duplicatedElementsCollection;

                    // Reserve the required amount of memory
                    duplicatedElementsCollection.reserve(collection.size() * 2);

                    // Add each element from old into new collection twice
                    for (auto element : collection) {
                        // Add element once
                        duplicatedElementsCollection.push_back(element);

                        // Add element twice
                        duplicatedElementsCollection.push_back(element);
                    }

                    return duplicatedElementsCollection;
                }

                //! Compute the set of indices pointing to the heterogeneous components in the given values collection
                /*! A value located at index i in the collection, 0 < i < (values.size() - 1), is a heterogeneous
                 *  component if and only if relation(values[i - 1], values[i]) and !relation(values[i], values[i + 1])
                 *  and !equal_to(values[i], values[i + 1])
                 *
                 * \param values            The collection of given values
                 * \param relation          The considered relation
                 */
                template <typename Relation>
                std::vector<std::size_t>
                evaluateHeterogeneousComponentsIndices(const std::vector<double> &values,
                                                       const Relation &relation) const {
                    std::vector<std::size_t> heterogeneousComponentsIndices;

                    // Stop at the last but one element index because both (index) and
                    // (index + 1) are considered below
                    std::size_t consideredValuesEndIndex = (values.size() > 0)
                                                               ? (values.size() - 1)
                                                               : 0;

                    // Compute the peak indices
                    for (std::size_t i = 1; i < consideredValuesEndIndex; i++) {
                        if ((relation(values[i - 1], values[i])) &&
                            (!relation(values[i], values[i + 1])) &&
                            (!std::equal_to<double>()(values[i], values[i + 1]))) {
                            heterogeneousComponentsIndices.push_back(i);
                        }
                    }

                    return heterogeneousComponentsIndices;
                }

        };

    };

};


#endif
