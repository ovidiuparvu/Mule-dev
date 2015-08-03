#ifndef NUMERICCSVMODELCHECKINGPERFORMANCETEST_HPP
#define NUMERICCSVMODELCHECKINGPERFORMANCETEST_HPP

#include "ModelCheckingPerformanceTest.hpp"

#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"


namespace multiscaletest {

    //! Class for representing a numeric csv model checking performance unit test
    class NumericCsvModelCheckingPerformanceTest : public ModelCheckingPerformanceTest {

        private:

            std::string logicPropertiesInputFilePath;   /*!< The path to the file containing the logic properties */
            std::string timeSeriesInputFilePath;        /*!< The path to the csv file containing time series data */

        public:

            //! Run the model checking performance test
            /*!
             * \param logicPropertiesInputFilePath  The path to the file containing the logic properties
             * \param timeSeriesInputFilePath       The path to the csv file containing the time series data
             */
            double RunNumericCsvModelCheckingPerformanceTest(const std::string &logicPropertiesInputFilePath,
                                                             const std::string &timeSeriesInputFilePath);

        protected:

            //! Run the test
            virtual void RunTest() override;

            //! Validate the results of the test
            virtual void ValidateTestResults() override;

        private:

            //! Evaluate the provided logic properties considering the given time series
            /*!
             * \param logicProperties   The provided logic properties
             * \param timeSeries        The time series data against which the logic properties are evaluated
             */
            void EvaluateLogicProperties(const std::vector<std::string> &logicProperties,
                                         multiscale::verification::SpatialTemporalTrace &timeSeries);

    };

};


#endif
