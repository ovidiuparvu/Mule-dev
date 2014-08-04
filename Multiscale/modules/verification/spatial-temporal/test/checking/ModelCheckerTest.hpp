#ifndef MODELCHECKINGTEST_HPP
#define MODELCHECKINGTEST_HPP

#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/exception/TestException.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/model/Region.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <string>

namespace mv = multiscale::verification;

const std::string INPUT_LOGIC_PROPERTY = "P > 0.6 [F [0, 3] (avg(regions, density) > 20)]";


namespace multiscaletest {

    //! Class for testing model checkers
    class ModelCheckerTest : public MultiscaleTest {

        protected:

            std::vector<mv::SpatialTemporalTrace> traces;               /*!< The collection of spatio-temporal traces */

            mv::AbstractSyntaxTree                abstractSyntaxTree;   /*!< The abstract syntax tree corresponding to the logic property */
            std::shared_ptr<mv::ModelChecker>     modelChecker;         /*!< The specific type of model checker employed */

            bool                                  evaluationResult;     /*!< The result of the model checking evaluation */

        public:

           //! Run the test for the given logic property
           bool RunModelCheckingTest();

        protected:

           //! Run the test
           virtual void RunTest() override;

           //! Validate the results of the test
           virtual void ValidateTestResults() override;

           //! Initialise the model checker
           virtual void InitialiseModelChecker() = 0;

        private:

           //! Initialisation function
           void Initialise();

           //! Initialise the collection of spatio-temporal traces
           void InitialiseSpatioTemporalTraces();

           //! Initialise the abstract syntax tree
           void InitialiseAbstractSyntaxTree();

           //! Initialise the collection of spatio-temporal traces with the given spatial entity area values
           /*!
            * The assumption is that each timepoint contains only one spatial entity of the same time.
            * Therefore each area value corresponds to a different timepoint and spatial entity.
            *
            * \param areaValues The values of the areas
            */
           void InitialiseSpatioTemporalTraceWithAreaValues(const std::vector<double> densityValues);

           //! Initialise the globally increasing area spatio-temporal trace
           void InitialiseIncreasingSpatioTemporalTrace();

           //! Initialise the globally decreasing area spatio-temporal trace
           void InitialiseDecreasingSpatioTemporalTrace();

           //! Initialise the increasing and then decreasing area spatio-temporal trace
           void InitialiseIncreasingDecreasingSpatioTemporalTrace();

           //! Initialise the decreasing and then increasing area spatio-temporal trace
           void InitialiseDecreasingIncreasingSpatioTemporalTrace();

           //! Initialise the constant area spatio-temporal trace
           void InitialiseConstantSpatioTemporalTrace();

           //! Initialise the increasing and then constant area spatio-temporal trace
           void InitialiseIncreasingConstantSpatioTemporalTrace();

           //! Initialise the decreasing and then constant area spatio-temporal trace
           void InitialiseDecreasingConstantSpatioTemporalTrace();

           //! Initialise the constant and then increasing area spatio-temporal trace
           void InitialiseConstantIncreasingSpatioTemporalTrace();

           //! Initialise the constant and then decreasing area spatio-temporal trace
           void InitialiseConstantDecreasingSpatioTemporalTrace();

           //! Initialise the increasing, constant and then decreasing area spatio-temporal trace
           void InitialiseIncreasingConstantDecreasingSpatioTemporalTrace();

           //! Initialise the decreasing, constant and increasing area spatio-temporal trace
           void InitialiseDecreasingConstantIncreasingSpatioTemporalTrace();

           //! Initialise the increasing, constant and then increasing area spatio-temporal trace
           void InitialiseIncreasingConstantIncreasingSpatioTemporalTrace();

    };

    bool ModelCheckerTest::RunModelCheckingTest() {
        Initialise();

        RunTest();
        ValidateTestResults();

        return evaluationResult;
    }

    void ModelCheckerTest::RunTest() {
        size_t traceIndex = 0;

        while ((traceIndex < traces.size()) && (modelChecker->acceptsMoreTraces())) {
            modelChecker->evaluate(traces[traceIndex++]);
        }

        evaluationResult = modelChecker->doesPropertyHold();
    }

    void ModelCheckerTest::ValidateTestResults() {}

    void ModelCheckerTest::Initialise() {
        InitialiseSpatioTemporalTraces();
        InitialiseAbstractSyntaxTree();
        InitialiseModelChecker();
    }

    void ModelCheckerTest::InitialiseSpatioTemporalTraces() {
        traces.clear();

        InitialiseSpatioTemporalTraceWithAreaValues(std::vector<double>{10, 20, 30});
        InitialiseSpatioTemporalTraceWithAreaValues(std::vector<double>{30, 20, 10});
        InitialiseSpatioTemporalTraceWithAreaValues(std::vector<double>{10, 20, 10});
        InitialiseSpatioTemporalTraceWithAreaValues(std::vector<double>{30, 20, 30});
        InitialiseSpatioTemporalTraceWithAreaValues(std::vector<double>{20, 20, 20});
        InitialiseSpatioTemporalTraceWithAreaValues(std::vector<double>{10, 20, 20});
        InitialiseSpatioTemporalTraceWithAreaValues(std::vector<double>{30, 20, 20});
        InitialiseSpatioTemporalTraceWithAreaValues(std::vector<double>{20, 20, 30});
        InitialiseSpatioTemporalTraceWithAreaValues(std::vector<double>{20, 20, 10});
        InitialiseSpatioTemporalTraceWithAreaValues(std::vector<double>{10, 20, 20, 10});
        InitialiseSpatioTemporalTraceWithAreaValues(std::vector<double>{30, 20, 20, 30});
        InitialiseSpatioTemporalTraceWithAreaValues(std::vector<double>{10, 20, 20, 30});
    }

    void ModelCheckerTest::InitialiseAbstractSyntaxTree() {
        mv::Parser parser(INPUT_LOGIC_PROPERTY);

        parser.parse(abstractSyntaxTree);
    }

    void ModelCheckerTest::InitialiseSpatioTemporalTraceWithAreaValues(const std::vector<double> densityValues) {
        mv::SpatialTemporalTrace                            trace;
        mv::TimePoint                                       timePoint;
        std::shared_ptr<SpatialEntity>                      region;
        std::list<std::shared_ptr<SpatialEntity>>::iterator iterator;

        timePoint.setConsideredSpatialEntityType(mv::SubsetSpecificType::Regions);

        for (std::size_t i = 0; i < densityValues.size(); i++) {
            std::shared_ptr<SpatialEntity> region = std::make_shared<Region>();

            region->setSpatialMeasureValue(SpatialMeasureType::Density, densityValues[i]);
            timePoint.addSpatialEntity(region, mv::SubsetSpecificType::Regions);
            trace.addTimePoint(timePoint);

            iterator = timePoint.getSpatialEntitiesBeginIterator(SubsetSpecificType::Regions);

            timePoint.removeSpatialEntity(iterator, SubsetSpecificType::Regions);
        }

        traces.push_back(trace);
    }

};


#endif
