#ifndef MODELCHECKINGTEST_HPP
#define MODELCHECKINGTEST_HPP

/******************************************************************************
 *
 * WARNING! AUTO-GENERATED FILE.
 *
 * PLEASE DO NOT UPDATE THIS FILE MANUALLY. 
 * USE THE PYTHON GENERATOR SCRIPTS FOR ANY MODIFICATIONS.
 *
 *****************************************************************************/
 
#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/exception/TestException.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/model/Cluster.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <string>

namespace mv = multiscale::verification;

const std::string INPUT_LOGIC_PROPERTY = "P > 0.6 [F [0, 3] (avg(clusteredness(clusters)) > 0.333333333333)]";


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

           //! Initialize the collection of spatio-temporal traces with the given spatial entity clusteredness values
           /*!
            * The assumption is that each timepoint contains only one spatial entity of the same type.
            * Therefore each clusteredness value corresponds to a different timepoint and spatial entity.
            *
            * \param clusterednessValues The collection of clusteredness values
            */
           void InitializeSpatioTemporalTraceWithClusterednessValues(const std::vector<double> clusterednessValues);

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

        InitializeSpatioTemporalTraceWithClusterednessValues(std::vector<double>{0.166666666667, 0.333333333333, 0.5});
        InitializeSpatioTemporalTraceWithClusterednessValues(std::vector<double>{0.5, 0.333333333333, 0.166666666667});
        InitializeSpatioTemporalTraceWithClusterednessValues(std::vector<double>{0.166666666667, 0.333333333333, 0.166666666667});
        InitializeSpatioTemporalTraceWithClusterednessValues(std::vector<double>{0.5, 0.333333333333, 0.5});
        InitializeSpatioTemporalTraceWithClusterednessValues(std::vector<double>{0.333333333333, 0.333333333333, 0.333333333333});
        InitializeSpatioTemporalTraceWithClusterednessValues(std::vector<double>{0.166666666667, 0.333333333333, 0.333333333333});
        InitializeSpatioTemporalTraceWithClusterednessValues(std::vector<double>{0.5, 0.333333333333, 0.333333333333});
        InitializeSpatioTemporalTraceWithClusterednessValues(std::vector<double>{0.333333333333, 0.333333333333, 0.5});
        InitializeSpatioTemporalTraceWithClusterednessValues(std::vector<double>{0.333333333333, 0.333333333333, 0.166666666667});
        InitializeSpatioTemporalTraceWithClusterednessValues(std::vector<double>{0.166666666667, 0.333333333333, 0.333333333333, 0.166666666667});
        InitializeSpatioTemporalTraceWithClusterednessValues(std::vector<double>{0.5, 0.333333333333, 0.333333333333, 0.5});
        InitializeSpatioTemporalTraceWithClusterednessValues(std::vector<double>{0.166666666667, 0.333333333333, 0.333333333333, 0.5});
    }

    void ModelCheckerTest::InitializeMultiscaleArchitectureGraph() {
        // Do nothing
    }
    
    void ModelCheckerTest::InitializeAbstractSyntaxTree() {
        mv::Parser parser(INPUT_LOGIC_PROPERTY);

        parser.parse(abstractSyntaxTree);
    }

    void ModelCheckerTest::InitializeSpatioTemporalTraceWithClusterednessValues(const std::vector<double> clusterednessValues) {
        mv::SpatialTemporalTrace                            trace;
        mv::TimePoint                                       timePoint;
        std::list<std::shared_ptr<SpatialEntity>>::iterator iterator;

        timePoint.setConsideredSpatialEntityType(mv::SubsetSpecificType::Clusters);

        for (std::size_t i = 0; i < clusterednessValues.size(); i++) {
            std::shared_ptr<SpatialEntity> cluster = std::make_shared<Cluster>();

            cluster->setSpatialMeasureValue(SpatialMeasureType::Clusteredness, clusterednessValues[i]);
            timePoint.addSpatialEntityAndType(cluster, mv::SubsetSpecificType::Clusters);
            trace.addTimePoint(timePoint);

            iterator = timePoint.getSpatialEntitiesBeginIterator(SubsetSpecificType::Clusters);

            timePoint.removeSpatialEntity(iterator, SubsetSpecificType::Clusters);
        }

        traces.push_back(trace);
    }

};


#endif