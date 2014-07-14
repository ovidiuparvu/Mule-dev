#ifndef MODELCHECKINGTEST_HPP
#define MODELCHECKINGTEST_HPP

#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/exception/TestException.hpp"
#include "multiscale/verification/spatial-temporal/checking/ApproximateBayesianModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <string>

using namespace multiscale;
using namespace multiscaletest;

namespace mv = multiscale::verification;

const std::string INPUT_LOGIC_PROPERTY = "P > 0.6 [F [0, 3] (avg(regions, area) > 20)]";


namespace multiscaletest {

    //! Class for testing model checkers
    class ModelCheckingTest : public MultiscaleTest {

        protected:

            std::vector<mv::SpatialTemporalTrace> traces;           /*!< The collection of spatio-temporal traces */

            std::shared_ptr<mv::ModelChecker>     modelChecker;     /*!< The specific type of model checker employed */

            bool                                  evaluationResult; /*!< The result of the model checking evaluation */

        public:

           //! Run the test for the given logic property
            /*!
             * \param modelChecker  The specific type of model checker employed
             */
           bool RunModelCheckingTest(const std::shared_ptr<mv::ModelChecker> &modelChecker);

        protected:

           //! Run the test
           virtual void RunTest() override;

           //! Validate the results of the test
           virtual void ValidateTestResults() override;

        private:

           //! Initialise the model checker
           void InitialiseModelChecker(const std::shared_ptr<mv::ModelChecker> &modelChecker);

           //! Initialise the collection of spatio-temporal traces
           void InitialiseSpatioTemporalTraces();

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

    bool ModelCheckingTest::RunModelCheckingTest(const std::shared_ptr<mv::ModelChecker> &modelChecker) {
        InitialiseSpatioTemporalTraces();
        InitialiseModelChecker(modelChecker);

        RunTest();
        ValidateTestResults();

        return evaluationResult;
    }

    void ModelCheckingTest::RunTest() {
        size_t traceIndex = 0;

        while ((traceIndex < traces.size()) && (modelChecker->requiresMoreTraces())) {
            modelChecker->evaluate(traces[traceIndex++]);
        }

        evaluationResult = modelChecker->doesPropertyHold();
    }

    void ModelCheckingTest::ValidateTestResults() {}

    void ModelCheckingTest::InitialiseModelChecker(const std::shared_ptr<mv::ModelChecker> &modelChecker) {
        this->modelChecker = modelChecker;
    }

    void ModelCheckingTest::InitialiseSpatioTemporalTraces() {
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

    void ModelCheckingTest::InitialiseIncreasingSpatioTemporalTrace() {
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

    void ModelCheckingTest::InitialiseDecreasingSpatioTemporalTrace() {
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

    void ModelCheckingTest::InitialiseIncreasingDecreasingSpatioTemporalTrace() {
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

    void ModelCheckingTest::InitialiseDecreasingIncreasingSpatioTemporalTrace() {
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

    void ModelCheckingTest::InitialiseConstantSpatioTemporalTrace() {
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

    void ModelCheckingTest::InitialiseIncreasingConstantSpatioTemporalTrace() {
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

    void ModelCheckingTest::InitialiseDecreasingConstantSpatioTemporalTrace() {
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

    void ModelCheckingTest::InitialiseConstantIncreasingSpatioTemporalTrace() {
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

    void ModelCheckingTest::InitialiseConstantDecreasingSpatioTemporalTrace() {
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

    void ModelCheckingTest::InitialiseIncreasingConstantDecreasingSpatioTemporalTrace() {
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

    void ModelCheckingTest::InitialiseDecreasingConstantIncreasingSpatioTemporalTrace() {
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

    void ModelCheckingTest::InitialiseIncreasingConstantIncreasingSpatioTemporalTrace() {
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


/////////////////////////////////////////////////////////////////
//
// Helper functions
//
/////////////////////////////////////////////////////////////////

//! Parse the given input string and return the corresponding abstract syntax tree
/*!
 * \param inputString The input string
 */
mv::AbstractSyntaxTree parseInputString(const std::string &inputString) {
    mv::AbstractSyntaxTree parseResult;
    mv::Parser parser(inputString);

    parser.parse(parseResult);

    return parseResult;
}


/////////////////////////////////////////////////////////////////
//
// Test functions
//
// The expected output for each test was computed manually
// considering the model checking type specific parameters.
//
/////////////////////////////////////////////////////////////////

TEST_F(ModelCheckingTest, ApproximateBayesianModelChecking) {
    std::shared_ptr<mv::ApproximateBayesianModelChecker> modelChecker;

    mv::AbstractSyntaxTree abstractSyntaxTree = parseInputString(INPUT_LOGIC_PROPERTY);

    double alphaParamBetaPrior  = 1;
    double betaParamBetaPrior   = 1;
    double varianceThreshold    = 0.035;

    modelChecker = std::make_shared<mv::ApproximateBayesianModelChecker>(abstractSyntaxTree, alphaParamBetaPrior,
                                                                         betaParamBetaPrior, varianceThreshold);

    EXPECT_TRUE(RunModelCheckingTest(modelChecker));
}


#endif
