#ifndef TIMEPOINTSNUMERICVALUESINITIALIZER_HPP
#define TIMEPOINTSNUMERICVALUESINITIALIZER_HPP

#include "NonEmptyTraceEvaluationTest.hpp"


namespace multiscaletest {

    //! Class for initializing numeric values in a given collection of time points
    class TimePointsNumericValuesInitializer {

        protected:

            NumericStateVariableId
                aNumericStateVariableId;            /*!< The id of the numeric state variable "A" (no type) */
            NumericStateVariableId
                bNumericStateVariableId;            /*!< The id of the numeric state variable "B" (no type) */
            NumericStateVariableId
                aWithTypeNumericStateVariableId;    /*!< The id of the numeric state variable "A" (with type) */
            NumericStateVariableId
                bWithTypeNumericStateVariableId;    /*!< The id of the numeric state variable "B" (with type) */
            NumericStateVariableId
                cNumericStateVariableId;            /*!< The id of the numeric state variable "C" */
            NumericStateVariableId
                dNumericStateVariableId;            /*!< The id of the numeric state variable "D" */

            double aMinValue;                       /*!< The minimum value of numeric state variable "A" */
            double aMaxValue;                       /*!< The maximum value of numeric state variable "A" */
            double bConstantValue;                  /*!< The constant value of numeric state variable "B" */
            double cMinValue;                       /*!< The minimum value of numeric state variable "C" */
            double cMaxValue;                       /*!< The maximum value of numeric state variable "C" */
            double dConstantValue;                  /*!< The constant value of numeric state variable "D" */

        public:

            TimePointsNumericValuesInitializer();
            ~TimePointsNumericValuesInitializer();

            //! Add numeric state variables values to the provided collection of time points
            /*!
             * \param timePoints    The collection of time points to which numeric state variables values are added
             */
            void addValuesOfNumericStateVariablesToTimePoints(std::vector<mv::TimePoint> &timePoints);

        private:

            //! Add the values of the numeric state variables A to time points
            /*!
             * \param timePoints    The collection of time points to which numeric state variables values are added
             */
            void addValuesOfNumericStateVariablesAToTimePoints(std::vector<mv::TimePoint> &timePoints);

            //! Add the values of the numeric state variables B to time points
            /*!
             * \param timePoints    The collection of time points to which numeric state variables values are added
             */
            void addValuesOfNumericStateVariablesBToTimePoints(std::vector<mv::TimePoint> &timePoints);

            //! Add the values of the numeric state variables C to time points
            /*!
             * \param timePoints    The collection of time points to which numeric state variables values are added
             */
            void addValuesOfNumericStateVariablesCToTimePoints(std::vector<mv::TimePoint> &timePoints);

            //! Add the values of the numeric state variables D to time points
            /*!
             * \param timePoints    The collection of time points to which numeric state variables values are added
             */
            void addValuesOfNumericStateVariablesDToTimePoints(std::vector<mv::TimePoint> &timePoints);

    };


    TimePointsNumericValuesInitializer::TimePointsNumericValuesInitializer()
        : aNumericStateVariableId("A", ScaleAndSubsystem::DEFAULT_VALUE),
          bNumericStateVariableId("B", ScaleAndSubsystem::DEFAULT_VALUE),
          aWithTypeNumericStateVariableId("A", NonEmptyTraceEvaluationTest::SCALE_AND_SUBSYSTEM_ORGAN_KIDNEY),
          bWithTypeNumericStateVariableId("B", NonEmptyTraceEvaluationTest::SCALE_AND_SUBSYSTEM_ORGAN_KIDNEY),
          cNumericStateVariableId("C", NonEmptyTraceEvaluationTest::SCALE_AND_SUBSYSTEM_ORGAN_HEART),
          dNumericStateVariableId("D", NonEmptyTraceEvaluationTest::SCALE_AND_SUBSYSTEM_ORGAN_LIVER),
          aMinValue(1),
          aMaxValue(12),
          bConstantValue(3),
          cMinValue(0),
          cMaxValue(12),
          dConstantValue(5) {}

    TimePointsNumericValuesInitializer::~TimePointsNumericValuesInitializer() {}

    void TimePointsNumericValuesInitializer::addValuesOfNumericStateVariablesToTimePoints(
        std::vector<mv::TimePoint> &timePoints
    ) {
        addValuesOfNumericStateVariablesAToTimePoints(timePoints);
        addValuesOfNumericStateVariablesBToTimePoints(timePoints);
        addValuesOfNumericStateVariablesCToTimePoints(timePoints);
        addValuesOfNumericStateVariablesDToTimePoints(timePoints);
    }

    void TimePointsNumericValuesInitializer::addValuesOfNumericStateVariablesAToTimePoints(
        std::vector<mv::TimePoint> &timePoints
    ) {
        std::size_t nrOfTimePoints = timePoints.size();

        // Add a numeric state variable "A" (without type) to the collection of time points
        for (std::size_t i = 0; i < nrOfTimePoints; i++) {
            if (i % 4 == 0) {
                timePoints[i].addNumericStateVariable(
                    aNumericStateVariableId,
                    aMinValue
                );
            } else {
                timePoints[i].addNumericStateVariable(
                    aNumericStateVariableId,
                    aMinValue + (aMaxValue - aMinValue) * (static_cast<double>(i) / static_cast<double>(nrOfTimePoints - 1))
                );
            }
        }

        // Add a numeric state variable "A" (with type) to the collection of time points
        for (std::size_t i = 0; i < nrOfTimePoints; i++) {
            if (i % 4 == 0) {
                timePoints[i].addNumericStateVariable(
                    aWithTypeNumericStateVariableId,
                    aMinValue
                );
            } else {
                timePoints[i].addNumericStateVariable(
                    aWithTypeNumericStateVariableId,
                    aMinValue + (aMaxValue - aMinValue) * (static_cast<double>(i) / static_cast<double>(nrOfTimePoints - 1))
                );
            }
        }
    }

    void TimePointsNumericValuesInitializer::addValuesOfNumericStateVariablesBToTimePoints(
        std::vector<mv::TimePoint> &timePoints
    ) {
        std::size_t nrOfTimePoints = timePoints.size();

        // Add a numeric state variable "B" (without type) to the collection of time points
        for (std::size_t i = 0; i < nrOfTimePoints; i++) {
            timePoints[i].addNumericStateVariable(bNumericStateVariableId, bConstantValue);
        }

        // Add a numeric state variable "B" (with type) to the collection of time points
        for (std::size_t i = 0; i < nrOfTimePoints; i++) {
            timePoints[i].addNumericStateVariable(bWithTypeNumericStateVariableId, bConstantValue);
        }
    }

    void TimePointsNumericValuesInitializer::addValuesOfNumericStateVariablesCToTimePoints(
        std::vector<mv::TimePoint> &timePoints
    ) {
        std::size_t nrOfTimePoints = timePoints.size();

        // Add a numeric state variable "C" to the collection of time points
        for (std::size_t i = 0; i < nrOfTimePoints; i++) {
            if (i % 4 == 0) {
                timePoints[i].addNumericStateVariable(
                    cNumericStateVariableId,
                    cMaxValue
                );
            } else {
                timePoints[i].addNumericStateVariable(
                    cNumericStateVariableId,
                    cMinValue +
                    (cMaxValue - cMinValue) * (
                        static_cast<double>(nrOfTimePoints - i) /
                        static_cast<double>(nrOfTimePoints)
                    )
                );
            }
        }
    }

    void TimePointsNumericValuesInitializer::addValuesOfNumericStateVariablesDToTimePoints(
        std::vector<mv::TimePoint> &timePoints
    ) {
        std::size_t nrOfTimePoints = timePoints.size();

        // Add a numeric state variable "D" (with type) to the collection of time points
        for (std::size_t i = 0; i < nrOfTimePoints; i++) {
            timePoints[i].addNumericStateVariable(dNumericStateVariableId, dConstantValue);
        }
    }

}


#endif
