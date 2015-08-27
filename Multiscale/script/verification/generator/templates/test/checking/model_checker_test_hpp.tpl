#ifndef MODELCHECKINGTEST_HPP
#define MODELCHECKINGTEST_HPP

/******************************************************************************
/*{% for line in auto_generated_warning %}*/
 /*{{ line }}*/
/*{% endfor %}*/
 *****************************************************************************/
 
#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/exception/TestException.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/model//*{{ spatial_entities[0].name|first_to_upper }}*/.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <string>

namespace mv = multiscale::verification;

const std::string INPUT_LOGIC_PROPERTY = "P > 0.6 [F [0, 3] (avg(/*{{ spatial_measures[0].name }}*/(/*{{ spatial_entities[0].name }}*/s)) > /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/)]";


namespace multiscaletest {

    //! Class for testing model checkers
    class ModelCheckerTest : public MultiscaleTest {

        protected:

            std::vector<mv::SpatialTemporalTrace> 
                traces;                         /*!< The collection of spatio-temporal traces */

            MultiscaleArchitectureGraph
                multiscaleArchitectureGraph;    /*!< The multiscale architecture graph encoding the hierarchical 
                                                     organization of the scales and subsystems */
            
            mv::AbstractSyntaxTree                
                abstractSyntaxTree;             /*!< The abstract syntax tree corresponding to the logic property */
            std::shared_ptr<mv::ModelChecker>     
                modelChecker;                   /*!< The specific type of model checker employed */

            bool                                  
                evaluationResult;               /*!< The result of the model checking evaluation */

        public:

           //! Run the test for the given logic property
           bool RunModelCheckingTest();

        protected:

           //! Run the test
           virtual void RunTest() override;

           //! Validate the results of the test
           virtual void ValidateTestResults() override;

           //! Initialize the model checker
           virtual void InitializeModelChecker() = 0;

        private:

           //! Initialisation function
           void Initialize();

           //! Initialize the collection of spatio-temporal traces
           void InitializeSpatioTemporalTraces();

           //! Initialize the multiscale architecture graph
           void InitializeMultiscaleArchitectureGraph();
           
           //! Initialize the abstract syntax tree
           void InitializeAbstractSyntaxTree();

           //! Initialize the collection of spatio-temporal traces with the given spatial entity /*{{ spatial_measures[0].name }}*/ values
           /*!
            * The assumption is that each time point contains only one spatial entity of the same type.
            * Therefore each /*{{ spatial_measures[0].name }}*/ value corresponds to a different time point and spatial entity.
            *
            * \param /*{{ spatial_measures[0].name }}*/Values The collection of /*{{ spatial_measures[0].name }}*/ values
            */
           void InitializeSpatioTemporalTraceWith/*{{ spatial_measures[0].name|first_to_upper }}*/Values(const std::vector<double> /*{{ spatial_measures[0].name }}*/Values);

    };

    bool ModelCheckerTest::RunModelCheckingTest() {
        Initialize();

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

    void ModelCheckerTest::Initialize() {
        InitializeSpatioTemporalTraces();
        InitializeMultiscaleArchitectureGraph();
        InitializeAbstractSyntaxTree();
        InitializeModelChecker();
    }

    void ModelCheckerTest::InitializeSpatioTemporalTraces() {
        traces.clear();

        InitializeSpatioTemporalTraceWith/*{{ spatial_measures[0].name|first_to_upper }}*/Values(std::vector<double>{/*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 6 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 2 }}*/});
        InitializeSpatioTemporalTraceWith/*{{ spatial_measures[0].name|first_to_upper }}*/Values(std::vector<double>{/*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 2 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 6 }}*/});
        InitializeSpatioTemporalTraceWith/*{{ spatial_measures[0].name|first_to_upper }}*/Values(std::vector<double>{/*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 6 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 6 }}*/});
        InitializeSpatioTemporalTraceWith/*{{ spatial_measures[0].name|first_to_upper }}*/Values(std::vector<double>{/*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 2 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 2 }}*/});
        InitializeSpatioTemporalTraceWith/*{{ spatial_measures[0].name|first_to_upper }}*/Values(std::vector<double>{/*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/});
        InitializeSpatioTemporalTraceWith/*{{ spatial_measures[0].name|first_to_upper }}*/Values(std::vector<double>{/*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 6 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/});
        InitializeSpatioTemporalTraceWith/*{{ spatial_measures[0].name|first_to_upper }}*/Values(std::vector<double>{/*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 2 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/});
        InitializeSpatioTemporalTraceWith/*{{ spatial_measures[0].name|first_to_upper }}*/Values(std::vector<double>{/*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 2 }}*/});
        InitializeSpatioTemporalTraceWith/*{{ spatial_measures[0].name|first_to_upper }}*/Values(std::vector<double>{/*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 6 }}*/});
        InitializeSpatioTemporalTraceWith/*{{ spatial_measures[0].name|first_to_upper }}*/Values(std::vector<double>{/*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 6 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 6 }}*/});
        InitializeSpatioTemporalTraceWith/*{{ spatial_measures[0].name|first_to_upper }}*/Values(std::vector<double>{/*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 2 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 2 }}*/});
        InitializeSpatioTemporalTraceWith/*{{ spatial_measures[0].name|first_to_upper }}*/Values(std::vector<double>{/*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 6 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 3 }}*/, /*{{ spatial_measures[0].min_value|float + (spatial_measures[0].max_value|float - spatial_measures[0].min_value|float) / 2 }}*/});
    }

    void ModelCheckerTest::InitializeMultiscaleArchitectureGraph() {
        // Do nothing
    }
    
    void ModelCheckerTest::InitializeAbstractSyntaxTree() {
        mv::Parser parser(INPUT_LOGIC_PROPERTY);

        parser.parse(abstractSyntaxTree);
    }

    void ModelCheckerTest::InitializeSpatioTemporalTraceWith/*{{ spatial_measures[0].name|first_to_upper }}*/Values(const std::vector<double> /*{{ spatial_measures[0].name }}*/Values) {
        mv::SpatialTemporalTrace                            trace;
        mv::TimePoint                                       timePoint;
        std::list<std::shared_ptr<SpatialEntity>>::iterator iterator;

        timePoint.setConsideredSpatialEntityType(mv::SubsetSpecificType::/*{{ spatial_entities[0].name|first_to_upper }}*/s);

        for (std::size_t i = 0; i < /*{{ spatial_measures[0].name }}*/Values.size(); i++) {
            std::shared_ptr<SpatialEntity> /*{{ spatial_entities[0].name }}*/ = std::make_shared</*{{ spatial_entities[0].name|first_to_upper }}*/>();

            /*{{ spatial_entities[0].name }}*/->setSpatialMeasureValue(SpatialMeasureType::/*{{ spatial_measures[0].name|first_to_upper }}*/, /*{{ spatial_measures[0].name }}*/Values[i]);
            timePoint.addSpatialEntityAndType(/*{{ spatial_entities[0].name }}*/, mv::SubsetSpecificType::/*{{ spatial_entities[0].name|first_to_upper }}*/s);
            trace.addTimePoint(timePoint);

            iterator = timePoint.getSpatialEntitiesBeginIterator(SubsetSpecificType::/*{{ spatial_entities[0].name|first_to_upper }}*/s);

            timePoint.removeSpatialEntity(iterator, SubsetSpecificType::/*{{ spatial_entities[0].name|first_to_upper }}*/s);
        }

        traces.push_back(trace);
    }

};


#endif