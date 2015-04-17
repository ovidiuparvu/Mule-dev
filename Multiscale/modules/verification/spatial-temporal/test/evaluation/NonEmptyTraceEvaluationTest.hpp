#ifndef NONEMPTYTRACEEVALUATIONTEST_HPP
#define NONEMPTYTRACEEVALUATIONTEST_HPP

#include "TraceEvaluationTest.hpp"


namespace multiscaletest {

    //! Class for testing evaluation of non-empty traces
    class NonEmptyTraceEvaluationTest : public TraceEvaluationTest {

        protected:

            std::size_t
                nrOfTimePoints;                 /*!< The number of timepoints in the trace */
            std::vector<mv::TimePoint>
                timePoints;                     /*! The collection of timepoints which will be added to
                                                    the trace */

        public:

            NonEmptyTraceEvaluationTest();

        protected:

           //! Add values to timepoints
           virtual void AddValuesToTimepoints() = 0;

        private:

           //! Initialize the multiscale architecture graph
           virtual void InitializeMultiscaleArchitectureGraph() override;

           //! Initialize the trace
           virtual void InitializeTrace() override;

           //! Initialize timepoints
           void InitializeTimepoints();

           //! Add timepoints to trace
           void AddTimepointsToTrace();

        public:

           // Constants
           static const std::string SCALE_AND_SUBSYSTEM_ORGANISM_HUMAN;
           static const std::string SCALE_AND_SUBSYSTEM_ORGAN_HEART;
           static const std::string SCALE_AND_SUBSYSTEM_ORGAN_KIDNEY;
           static const std::string SCALE_AND_SUBSYSTEM_ORGAN_LIVER;

    };

};


#endif
