#ifndef TIMESERIESCOMPONENTEVALUATOR_HPP
#define TIMESERIESCOMPONENTEVALUATOR_HPP

#include <multiscale/verification/spatial-temporal/attribute/HomogeneousTimeSeriesComponentAttribute.hpp>
#include "multiscale/exception/MultiscaleException.hpp"
#include <vector>


namespace multiscale {

    namespace verification {

        //! Class for evaluating time series components
        class TimeSeriesComponentEvaluator {

            public:

                //! Evaluate the homogeneous time series component considering the given collection of values
                /*!
                 * \param homogeneousTimeSeriesComponent    The given homogeneous time series component
                 * \param values                            The given collection of values
                 */
                static std::vector<std::size_t>
                evaluate(const HomogeneousTimeSeriesComponentAttribute &homogeneousTimeSeriesComponent,
                         const std::vector<double> &values) {
                    switch (homogeneousTimeSeriesComponent.homogeneousTimeSeriesComponent) {
                        case HomogeneousTimeSeriesComponentType::Ascent:
                            return evaluateHomogeneousComponentIndices(
                                values, std::less<double>(),
                                HomogeneousComponentEvaluator<std::less<double>>()
                            );
                            break;

                        case HomogeneousTimeSeriesComponentType::Descent:
                            return evaluateHomogeneousComponentIndices(
                                values, std::greater<double>(),
                                HomogeneousComponentEvaluator<std::greater<double>>()
                            );
                            break;

                        case HomogeneousTimeSeriesComponentType::Plateau:
                            return evaluateHomogeneousComponentIndices(
                                values, std::equal_to<double>(),
                                HomogeneousComponentEvaluator<std::equal_to<double>>()
                            );
                            break;

                        case HomogeneousTimeSeriesComponentType::UniformAscent:
                            return evaluateHomogeneousComponentIndices(
                                values, std::less<double>(),
                                UniformHomogeneousComponentEvaluator<std::less<double>>()
                            );
                            break;

                        case HomogeneousTimeSeriesComponentType::UniformDescent:
                            return evaluateHomogeneousComponentIndices(
                                values, std::greater<double>(),
                                UniformHomogeneousComponentEvaluator<std::greater<double>>()
                            );
                            break;

                        default:
                            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
                    }

                    // Line added to avoid "control reaches end of non-void function" warnings
                    return std::vector<std::size_t>();
                }

                //! Compute the set of (start, end) indices pointing to nonuniform homogeneous time series components
                /*!
                 *  The value of relation depending on the considered homogeneous component type is:
                 *      - (uniform) ascent: "<"
                 *      - (uniform) descent: ">"
                 *      - plateu: "="
                 *
                 * \param values    The collection of given values
                 * \param relation  The considered relation
                 * \param evaluator The considered evaluator
                 */
                template <
                    typename Relation,
                    template <typename> class HomogeneousTimeSeriesComponentEvaluator
                >
                static std::vector<std::size_t>
                evaluateHomogeneousComponentIndices(const std::vector<double> &values, const Relation &relation,
                                                    const HomogeneousTimeSeriesComponentEvaluator<Relation>
                                                    &evaluator) {
                    std::vector<std::size_t> homogeneousComponentIndices;

                    std::size_t nrOfValues = values.size();
                    std::size_t i          = 0;

                    // Compute the homogeneous components indices
                    while (i < nrOfValues) {
                        if (evaluator.isStartIndex(i, nrOfValues, values, relation)) {
                            // Add the starting index to resulting collection
                            homogeneousComponentIndices.push_back(i);

                            // Advance index "i" until the homogeneous component end index
                            i = evaluator.computeEndIndex(i, nrOfValues, values, relation);

                            // Add the ending index to resulting collection
                            homogeneousComponentIndices.push_back(i);
                        }

                        i++;
                    }

                    return homogeneousComponentIndices;
                }


                // Class for evaluating homogeneous components
                template <typename Relation>
                class HomogeneousComponentEvaluator {

                    public:

                        //! Check if the given index is a homogeneous component start index
                        /*! A value located at index i in the collection, 0 < i < (values.size() - 1), is a nonuniform
                         *  homogeneous component starting index if and only if !relation(values[i - 1], values[i]) and
                         *  relation(values[i], values[i + 1]), respectively relation(values[i], values[i + 1]) if i = 0.
                         *
                         * \param index         The given index
                         * \param nrOfValues    The number of considered values
                         * \param values        The collection of values
                         * \param relation      The considered relation
                         */
                        bool
                        isStartIndex(std::size_t index, std::size_t nrOfValues, const std::vector<double> &values,
                                     const Relation &relation) const {
                            // If index is invalid
                            if ((0 > index) || (index >= (nrOfValues - 1))) {
                                return false;
                            }

                            // Else if index is 0
                            if (index == 0) {
                                return (
                                    hasValidSuccessor(index, nrOfValues, values, relation)
                                );
                            }

                            // Otherwise
                            return (
                                (!relation(values[index - 1], values[index])) &&
                                hasValidSuccessor(
                                    index, nrOfValues, values, relation
                                )
                            );
                        }

                        //! Compute the homogeneous component end index considering the given homogeneous component start index
                        /*! A value located at index i in the collection, 0 < i < (values.size() - 1), is a
                         *  nonuniform homogeneous component ending index if and only if relation(values[i - 1], values[i])
                         *  and !relation(values[i], values[i + 1]), respectively relation(values[i - 1], values[i]) if
                         *  i = (values.size() - 1).
                         *
                         * \param startIndex    The given start index
                         * \param nrOfValues    The number of considered values
                         * \param values        The collection of values
                         * \param relation      The considered relation
                         */
                        std::size_t
                        computeEndIndex(std::size_t startIndex, std::size_t nrOfValues,
                                        const std::vector<double> &values, const Relation &relation) const {
                            // Validate precondition of the method
                            assert(isStartIndex(startIndex, nrOfValues, values, relation));

                            std::size_t endIndex = startIndex;

                            // Compute the end index
                            while (hasValidSuccessor(endIndex, nrOfValues, values, relation)) {
                                endIndex++;
                            }

                            return endIndex;
                        }

                    private:

                        //! Check if the provided homogeneous component index has a valid successor
                        /*!
                         * \param index         The given index
                         * \param nrOfValues    The number of considered values
                         * \param values        The collection of values
                         * \param relation      The considered relation
                         */
                        std::size_t
                        hasValidSuccessor(std::size_t index, std::size_t nrOfValues, const std::vector<double> &values,
                                          const Relation &relation) const {
                            // If index is invalid or has no successor
                            if ((0 > index) || (index >= (nrOfValues - 1))) {
                                return false;
                            }

                            // Otherwise
                            return (
                               relation(values[index], values[index + 1])
                            );
                        }

                };


                // Class for evaluating uniform homogeneous components
                template <typename Relation>
                class UniformHomogeneousComponentEvaluator {

                    public:

                        //! Check if the given index is a uniform homogeneous component start index
                        /*! A value located at index i in the collection, 0 < i < (values.size() - 2), is a uniform
                         *  homogeneous component starting index if and only if (!relation(values[i - 1], values[i])) or
                         *  (values[i - 2] - values[i - 1]) != (values[i - 1] - values[i]), relation(values[i], values[i + 1]),
                         *  relation(values[i + 1], values[i + 2]) and (values[i] - values[i + 1]) = (values[i + 1] -
                         *  values[i + 2]), respectively relation(values[i], values[i + 1]), relation(values[i + 1],
                         *  values[i + 2]), and (values[i] - values[i + 1]) = (values[i + 1] - values[i + 2]) if i = 0.
                         *
                         * \param index         The given index
                         * \param nrOfValues    The number of considered values
                         * \param values        The collection of values
                         * \param relation      The considered relation
                         */
                        bool
                        isStartIndex(std::size_t index, std::size_t nrOfValues, const std::vector<double> &values,
                                     const Relation &relation) const {
                            // If index is invalid
                            if ((0 > index) || (index >= (nrOfValues - 2))) {
                                return false;
                            }

                            // If a uniform homogeneous subcomponent started previously return false
                            for (std::size_t i = 1; ((index - i) >= 0) && (i <= 2); i++) {
                                if (hasValidSuccessors(
                                       index - i, nrOfValues, values, relation
                                    )) {
                                    return false;
                                }
                            }

                            // Return
                            return hasValidSuccessors(
                                index, nrOfValues, values, relation
                            );
                        }

                        //! Compute the uniform homogeneous component end index considering the given start index
                        /*! A value located at index i in the collection, 1 < i < (values.size() - 1), is a
                         *  nonuniform homogeneous component ending index if and only if relation(values[i - 2],
                         *  values[i - 1]), relation(values[i - 1], values[i]), (values[i - 2] - values[i - 1]) =
                         *  values[i - 1] - values[i]) and !relation(values[i], values[i + 1]) or
                         *  (values[i - 1] - values[i]) != (values[i] - values[i + 1]), respectively relation(values[i - 2],
                         *  values[i - 1]), relation(values[i - 1], values[i]) and (values[i - 2] - values[i - 1]) =
                         *  (values[i - 1] - values[i]) if i = (values.size() - 1).
                         *
                         * \param startIndex    The given start index
                         * \param nrOfValues    The number of considered values
                         * \param values        The collection of values
                         * \param relation      The considered relation
                         */
                        std::size_t
                        computeEndIndex(std::size_t startIndex, std::size_t nrOfValues,
                                        const std::vector<double> &values, const Relation &relation) const {
                            // Validate precondition of the method
                            assert(isStartIndex(startIndex, nrOfValues, values, relation));

                            std::size_t endIndex = startIndex;

                            // Compute the end index
                            while (hasValidSuccessors(endIndex, nrOfValues, values, relation)) {
                                endIndex++;
                            }

                            // Advance the end index another position since only the successor of the
                            // following element is invalid
                            endIndex++;

                            return endIndex;
                        }

                    private:

                        //! Check if a valid uniform homogeneous subcomponent starts from the given index
                        /*!
                         * \param index         The given index
                         * \param nrOfValues    The number of considered values
                         * \param values        The collection of values
                         * \param relation      The considered relation
                         */
                        bool
                        hasValidSuccessors(std::size_t index, std::size_t nrOfValues,
                                           const std::vector<double> &values, const Relation &relation) const {
                            // If index is invalid
                            if ((0 > index) || (index >= (nrOfValues - 2))) {
                                return false;
                            }

                            // Otherwise
                            return (
                                relation(values[index], values[index + 1]) &&
                                relation(values[index + 1], values[index + 2]) &&
                                Numeric::almostEqual(
                                    (values[index] - values[index + 1]),
                                    (values[index + 1] - values[index + 2])
                                )
                            );
                        }

                };

        };

    };

};



#endif
