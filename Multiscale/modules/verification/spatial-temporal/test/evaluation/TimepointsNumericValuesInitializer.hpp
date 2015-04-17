#ifndef TIMEPOINTSNUMERICVALUESINITIALIZER_HPP
#define TIMEPOINTSNUMERICVALUESINITIALIZER_HPP

#include "NonEmptyTraceEvaluationTest.hpp"


namespace multiscaletest {

    //! Class for initializing numeric values in a given collection of timepoints
    class TimepointsNumericValuesInitializer {

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

            TimepointsNumericValuesInitializer();
            ~TimepointsNumericValuesInitializer();

            //! Add numeric state variables values to the provided collection of timepoints
            /*!
             * \param timePoints    The collection of timepoints to which numeric state variables values are added
             */
            void addValuesOfNumericStateVariablesToTimepoints(std::vector<mv::TimePoint> &timePoints);

        private:

            //! Add the values of the numeric state variables A to timepoints
            /*!
             * \param timePoints    The collection of timepoints to which numeric state variables values are added
             */
            void addValuesOfNumericStateVariablesAToTimepoints(std::vector<mv::TimePoint> &timePoints);

            //! Add the values of the numeric state variables B to timepoints
            /*!
             * \param timePoints    The collection of timepoints to which numeric state variables values are added
             */
            void addValuesOfNumericStateVariablesBToTimepoints(std::vector<mv::TimePoint> &timePoints);

            //! Add the values of the numeric state variables C to timepoints
            /*!
             * \param timePoints    The collection of timepoints to which numeric state variables values are added
             */
            void addValuesOfNumericStateVariablesCToTimepoints(std::vector<mv::TimePoint> &timePoints);

            //! Add the values of the numeric state variables D to timepoints
            /*!
             * \param timePoints    The collection of timepoints to which numeric state variables values are added
             */
            void addValuesOfNumericStateVariablesDToTimepoints(std::vector<mv::TimePoint> &timePoints);

    };


    TimepointsNumericValuesInitializer::TimepointsNumericValuesInitializer()
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

    TimepointsNumericValuesInitializer::~TimepointsNumericValuesInitializer() {}

    void TimepointsNumericValuesInitializer::addValuesOfNumericStateVariablesToTimepoints(
        std::vector<mv::TimePoint> &timePoints
    ) {
        addValuesOfNumericStateVariablesAToTimepoints(timePoints);
        addValuesOfNumericStateVariablesBToTimepoints(timePoints);
        addValuesOfNumericStateVariablesCToTimepoints(timePoints);
        addValuesOfNumericStateVariablesDToTimepoints(timePoints);
    }

    void TimepointsNumericValuesInitializer::addValuesOfNumericStateVariablesAToTimepoints(
        std::vector<mv::TimePoint> &timePoints
    ) {
        std::size_t nrOfTimePoints = timePoints.size();

        // Add a numeric state variable "A" (without type) to the collection of timepoints
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

        // Add a numeric state variable "A" (with type) to the collection of timepoints
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

    void TimepointsNumericValuesInitializer::addValuesOfNumericStateVariablesBToTimepoints(
        std::vector<mv::TimePoint> &timePoints
    ) {
        std::size_t nrOfTimePoints = timePoints.size();

        // Add a numeric state variable "B" (without type) to the collection of timepoints
        for (std::size_t i = 0; i < nrOfTimePoints; i++) {
            timePoints[i].addNumericStateVariable(bNumericStateVariableId, bConstantValue);
        }

        // Add a numeric state variable "B" (with type) to the collection of timepoints
        for (std::size_t i = 0; i < nrOfTimePoints; i++) {
            timePoints[i].addNumericStateVariable(bWithTypeNumericStateVariableId, bConstantValue);
        }
    }

    void TimepointsNumericValuesInitializer::addValuesOfNumericStateVariablesCToTimepoints(
        std::vector<mv::TimePoint> &timePoints
    ) {
        std::size_t nrOfTimePoints = timePoints.size();

        // Add a numeric state variable "C" to the collection of timepoints
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

    void TimepointsNumericValuesInitializer::addValuesOfNumericStateVariablesDToTimepoints(
        std::vector<mv::TimePoint> &timePoints
    ) {
        std::size_t nrOfTimePoints = timePoints.size();

        // Add a numeric state variable "D" (with type) to the collection of timepoints
        for (std::size_t i = 0; i < nrOfTimePoints; i++) {
            timePoints[i].addNumericStateVariable(dNumericStateVariableId, dConstantValue);
        }
    }

}


#endif
