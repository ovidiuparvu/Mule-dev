#ifndef MODELCHECKINGTEST_HPP
#define MODELCHECKINGTEST_HPP

#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/exception/TestException.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <string>

namespace mv = multiscale::verification;

const std::string INPUT_LOGIC_PROPERTY = "P > 0.6 [F [0, 3] (avg(regions, area) > 20)]";


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

        InitialiseIncreasingSpatioTemporalTrace();
        InitialiseDecreasingSpatioTemporalTrace();
        InitialiseIncreasingDecreasingSpatioTemporalTrace();
        InitialiseDecreasingIncreasingSpatioTemporalTrace();
        InitialiseConstantSpatioTemporalTrace();
        InitialiseIncreasingConstantSpatioTemporalTrace();
        InitialiseDecreasingConstantSpatioTemporalTrace();
        InitialiseConstantIncreasingSpatioTemporalTrace();
        InitialiseConstantDecreasingSpatioTemporalTrace();
        InitialiseIncreasingConstantDecreasingSpatioTemporalTrace();
        InitialiseDecreasingConstantIncreasingSpatioTemporalTrace();
        InitialiseIncreasingConstantIncreasingSpatioTemporalTrace();
    }

    void ModelCheckerTest::InitialiseAbstractSyntaxTree() {
        mv::Parser parser(INPUT_LOGIC_PROPERTY);

        parser.parse(abstractSyntaxTree);
    }

    void ModelCheckerTest::InitialiseIncreasingSpatioTemporalTrace() {
        mv::SpatialTemporalTrace        trace;
        mv::TimePoint                   timePoint;
        mv::Region                      region;
        std::list<mv::Region>::iterator regionsIterator;

        timePoint.setConsideredSpatialEntityType(mv::ConsideredSpatialEntityType::Regions);

        region.setArea(10);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(20);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(30);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        traces.push_back(trace);
    }

    void ModelCheckerTest::InitialiseDecreasingSpatioTemporalTrace() {
        mv::SpatialTemporalTrace        trace;
        mv::TimePoint                   timePoint;
        mv::Region                      region;
        std::list<mv::Region>::iterator regionsIterator;

        timePoint.setConsideredSpatialEntityType(mv::ConsideredSpatialEntityType::Regions);

        region.setArea(30);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(20);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(10);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        traces.push_back(trace);
    }

    void ModelCheckerTest::InitialiseIncreasingDecreasingSpatioTemporalTrace() {
        mv::SpatialTemporalTrace        trace;
        mv::TimePoint                   timePoint;
        mv::Region                      region;
        std::list<mv::Region>::iterator regionsIterator;

        timePoint.setConsideredSpatialEntityType(mv::ConsideredSpatialEntityType::Regions);

        region.setArea(10);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(20);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(10);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        traces.push_back(trace);
    }

    void ModelCheckerTest::InitialiseDecreasingIncreasingSpatioTemporalTrace() {
        mv::SpatialTemporalTrace        trace;
        mv::TimePoint                   timePoint;
        mv::Region                      region;
        std::list<mv::Region>::iterator regionsIterator;

        timePoint.setConsideredSpatialEntityType(mv::ConsideredSpatialEntityType::Regions);

        region.setArea(30);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(20);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(30);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        traces.push_back(trace);
    }

    void ModelCheckerTest::InitialiseConstantSpatioTemporalTrace() {
        mv::SpatialTemporalTrace        trace;
        mv::TimePoint                   timePoint;
        mv::Region                      region;
        std::list<mv::Region>::iterator regionsIterator;

        timePoint.setConsideredSpatialEntityType(mv::ConsideredSpatialEntityType::Regions);

        region.setArea(20);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(20);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(20);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        traces.push_back(trace);
    }

    void ModelCheckerTest::InitialiseIncreasingConstantSpatioTemporalTrace() {
        mv::SpatialTemporalTrace        trace;
        mv::TimePoint                   timePoint;
        mv::Region                      region;
        std::list<mv::Region>::iterator regionsIterator;

        timePoint.setConsideredSpatialEntityType(mv::ConsideredSpatialEntityType::Regions);

        region.setArea(10);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(20);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(20);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        traces.push_back(trace);
    }

    void ModelCheckerTest::InitialiseDecreasingConstantSpatioTemporalTrace() {
        mv::SpatialTemporalTrace        trace;
        mv::TimePoint                   timePoint;
        mv::Region                      region;
        std::list<mv::Region>::iterator regionsIterator;

        timePoint.setConsideredSpatialEntityType(mv::ConsideredSpatialEntityType::Regions);

        region.setArea(30);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(20);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(20);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        traces.push_back(trace);
    }

    void ModelCheckerTest::InitialiseConstantIncreasingSpatioTemporalTrace() {
        mv::SpatialTemporalTrace        trace;
        mv::TimePoint                   timePoint;
        mv::Region                      region;
        std::list<mv::Region>::iterator regionsIterator;

        timePoint.setConsideredSpatialEntityType(mv::ConsideredSpatialEntityType::Regions);

        region.setArea(20);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(20);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(30);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        traces.push_back(trace);
    }

    void ModelCheckerTest::InitialiseConstantDecreasingSpatioTemporalTrace() {
        mv::SpatialTemporalTrace        trace;
        mv::TimePoint                   timePoint;
        mv::Region                      region;
        std::list<mv::Region>::iterator regionsIterator;

        timePoint.setConsideredSpatialEntityType(mv::ConsideredSpatialEntityType::Regions);

        region.setArea(20);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(20);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(10);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        traces.push_back(trace);
    }

    void ModelCheckerTest::InitialiseIncreasingConstantDecreasingSpatioTemporalTrace() {
        mv::SpatialTemporalTrace        trace;
        mv::TimePoint                   timePoint;
        mv::Region                      region;
        std::list<mv::Region>::iterator regionsIterator;

        timePoint.setConsideredSpatialEntityType(mv::ConsideredSpatialEntityType::Regions);

        region.setArea(10);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(20);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(20);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(10);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        traces.push_back(trace);
    }

    void ModelCheckerTest::InitialiseDecreasingConstantIncreasingSpatioTemporalTrace() {
        mv::SpatialTemporalTrace        trace;
        mv::TimePoint                   timePoint;
        mv::Region                      region;
        std::list<mv::Region>::iterator regionsIterator;

        timePoint.setConsideredSpatialEntityType(mv::ConsideredSpatialEntityType::Regions);

        region.setArea(30);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(20);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(20);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(30);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        traces.push_back(trace);
    }

    void ModelCheckerTest::InitialiseIncreasingConstantIncreasingSpatioTemporalTrace() {
        mv::SpatialTemporalTrace        trace;
        mv::TimePoint                   timePoint;
        mv::Region                      region;
        std::list<mv::Region>::iterator regionsIterator;

        timePoint.setConsideredSpatialEntityType(mv::ConsideredSpatialEntityType::Regions);

        region.setArea(10);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(20);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(20);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        regionsIterator = timePoint.getRegionsBeginIterator();

        timePoint.removeSpatialEntity(regionsIterator);
        region.setArea(30);
        timePoint.addRegion(region);
        trace.addTimePoint(timePoint);

        traces.push_back(trace);
    }

};


#endif
