#ifndef SPATIALMEASURECOLLECTIONVISITOR_HPP
#define SPATIALMEASURECOLLECTIONVISITOR_HPP

#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureCollectionAttribute.hpp"
#include "multiscale/verification/spatial-temporal/model/TimePoint.hpp"
#include "multiscale/verification/spatial-temporal/model/MultiscaleArchitectureGraph.hpp"
#include "multiscale/verification/spatial-temporal/visitor/NumericEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/visitor/SubsetVisitor.hpp"
#include "multiscale/verification/spatial-temporal/visitor/TimePointEvaluator.hpp"

#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        //! Class for evaluating spatial measure collections
        class SpatialMeasureCollectionVisitor : public boost::static_visitor<std::vector<double>> {

            private:

                TimePoint
                    &timePoint;                     /*!< The considered time point */
                const MultiscaleArchitectureGraph
                    &multiscaleArchitectureGraph;   /*!< The considered multiscale architecture graph */


            public:

                SpatialMeasureCollectionVisitor(TimePoint &timePoint,
                                                const MultiscaleArchitectureGraph &multiscaleArchitectureGraph)
                                                : timePoint(timePoint),
                                                  multiscaleArchitectureGraph(multiscaleArchitectureGraph) {}

                //! Overloading the "()" operator for the PrimarySpatialMeasureCollectionAttribute alternative
                /*!
                 * \param primarySpatialMeasureCollection  The primary spatial measure collection
                 */
                std::vector<double>
                operator()(const PrimarySpatialMeasureCollectionAttribute &primarySpatialMeasureCollection) const {
                    // Create the subset time point corresponding to the given time point
                    TimePoint subsetTimePoint(
                        boost::apply_visitor(
                            SubsetVisitor(
                                timePoint,
                                multiscaleArchitectureGraph
                            ),
                            primarySpatialMeasureCollection.subset.subset
                        )
                    );

                    // Compute the spatial measure values corresponding to the above created
                    // subset time point
                    std::vector<double> spatialMeasureValues =
                        TimePointEvaluator::getSpatialMeasureValues(
                            subsetTimePoint,
                            primarySpatialMeasureCollection.spatialMeasure.spatialMeasureType
                        );

                    return spatialMeasureValues;
                }

                //! Overloading the "()" operator for the UnaryNumericSpatialAttribute alternative
                /*!
                 * \param unaryNumericSpatialMeasureCollection  The attribute containing a unary numeric measure and
                 *                                              a spatial measure collection
                 */
                std::vector<double>
                operator()(const UnaryNumericSpatialAttribute &unaryNumericSpatialMeasureCollection) const {
                    // Compute the collection of spatial measure values
                    std::vector<double> spatialMeasureValuesCollection
                        = evaluateSpatialMeasureCollection(
                              unaryNumericSpatialMeasureCollection.spatialMeasureCollection
                          );

                    // Compute the value of the unary numeric measure for each spatial measure value
                    return (
                        evaluateUnaryNumericSpatialMeasureCollection(
                            unaryNumericSpatialMeasureCollection.unaryNumericMeasure,
                            spatialMeasureValuesCollection
                        )
                    );
                }

                //! Overloading the "()" operator for the BinaryNumericSpatialAttribute alternative
                /*!
                 * \param binaryNumericSpatialMeasureCollection The attribute containing a binary numeric measure and
                 *                                              two spatial measure collections
                 */
                std::vector<double>
                operator()(const BinaryNumericSpatialAttribute &binaryNumericSpatialMeasureCollection) const {
                    // Compute the collection of spatial measure values
                    std::vector<double> firstSpatialMeasureValuesCollection
                        = evaluateSpatialMeasureCollection(
                            binaryNumericSpatialMeasureCollection.firstSpatialMeasureCollection
                          );
                    std::vector<double> secondSpatialMeasureValuesCollection
                        = evaluateSpatialMeasureCollection(
                            binaryNumericSpatialMeasureCollection.secondSpatialMeasureCollection
                          );

                    // Compute the value of the binary numeric measure for each spatial measure value
                    return (
                        evaluateBinaryNumericSpatialMeasureCollection(
                            binaryNumericSpatialMeasureCollection.binaryNumericMeasure,
                            firstSpatialMeasureValuesCollection,
                            secondSpatialMeasureValuesCollection
                        )
                    );
                }

            private:

                //! Evaluate the given spatial measure collection
                /*! The time point and multiscale architecture graph provided in the constructor are employed
                 *  during the evaluation of the spatial measure collection.
                 *
                 * \param spatialMeasureCollection  The given spatial measure collection
                 */
                std::vector<double>
                evaluateSpatialMeasureCollection(const SpatialMeasureCollectionAttribute
                                                 &spatialMeasureCollection) const {
                    return (
                        NumericMeasureCollectionEvaluator::evaluateSpatialMeasureCollection(
                            timePoint,
                            multiscaleArchitectureGraph,
                            spatialMeasureCollection
                        )
                    );
                }

                //! Evaluate the given unary numeric measure for each spatial measure value
                /*!
                 * \param unaryNumericMeasure   The provided unary numeric measure
                 * \param spatialMeasureValues  The collection of spatial measure values
                 */
                std::vector<double>
                evaluateUnaryNumericSpatialMeasureCollection(const UnaryNumericMeasureAttribute
                                                             &unaryNumericMeasure,
                                                             const std::vector<double>
                                                             &spatialMeasureValues) const {
                    std::vector<double> processedSpatialMeasureValues;

                    // Compute the value of the unary numeric measure for each spatial measure value
                    for (double spatialMeasureValue : spatialMeasureValues) {
                        processedSpatialMeasureValues.push_back(
                            NumericEvaluator::evaluate(
                                unaryNumericMeasure.unaryNumericMeasureType,
                                spatialMeasureValue
                            )
                        );
                    }

                    return processedSpatialMeasureValues;
                }

                //! Evaluate the given binary numeric measure for each pair of spatial measure values
                /*!
                 * \param binaryNumericMeasure                  The provided binary numeric measure
                 * \param firstSpatialMeasureValuesCollection   The first collection of spatial measure values
                 * \param secondSpatialMeasureValuesCollection  The second collection of spatial measure values
                 */
                std::vector<double>
                evaluateBinaryNumericSpatialMeasureCollection(const BinaryNumericMeasureAttribute
                                                              &binaryNumericMeasure,
                                                              const std::vector<double>
                                                              &firstSpatialMeasureValuesCollection,
                                                              const std::vector<double>
                                                              &secondSpatialMeasureValuesCollection) const {
                    std::vector<double> processedSpatialMeasureValues;

                    std::size_t nrOfConsideredPairs = computeNrOfConsideredSpatialMeasureValuesPairs(
                                                          firstSpatialMeasureValuesCollection,
                                                          secondSpatialMeasureValuesCollection
                                                      );

                    // Compute the value of the binary numeric measure for each
                    // considered spatial measure values pair
                    for (std::size_t i = 0; i < nrOfConsideredPairs; i++) {
                        processedSpatialMeasureValues.push_back(
                            NumericEvaluator::evaluate(
                                binaryNumericMeasure.binaryNumericMeasureType,
                                firstSpatialMeasureValuesCollection[i],
                                secondSpatialMeasureValuesCollection[i]
                            )
                        );
                    }

                    return processedSpatialMeasureValues;
                }

                //! Compute the number of available spatial measure values pairs
                /*! The number of considered pairs is equal to the minimum number of values
                 *  in the provided collections.
                 *
                 *  \param firstSpatialMeasureValuesCollection  The first collection of spatial measure values
                 *  \param secondSpatialMeasureValuesCollection The second collection of spatial measure values
                 */
                std::size_t
                computeNrOfConsideredSpatialMeasureValuesPairs(const std::vector<double>
                                                               &firstSpatialMeasureValuesCollection,
                                                               const std::vector<double>
                                                               &secondSpatialMeasureValuesCollection) const {
                    return (
                        std::min(
                            firstSpatialMeasureValuesCollection.size(),
                            secondSpatialMeasureValuesCollection.size()
                        )
                    );
                }

        };

    };

};

#endif
