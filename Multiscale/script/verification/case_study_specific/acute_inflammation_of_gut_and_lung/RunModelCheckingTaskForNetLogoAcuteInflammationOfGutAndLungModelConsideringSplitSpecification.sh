# Constants initialisations
# (TODO: Update)
caseStudy="AcuteInflammationOfGutAndLung";
caseStudyMultiscaleArchitectureGraph="multiscale_architecture_graph_acute_inflammation_of_gut_and_lung.xml";

# Path initialisations
modelCheckerExecutionScript="/home/ovidiu/Repositories/git/multiscale/Multiscale/script/verification/ExecuteStatisticalModelCheckingUsingMuleNoExtraEvaluation.sh";
modelCheckerPath="/home/ovidiu/Repositories/git/multiscale/Multiscale/bin/Mule";
queriesInputFolder="/media/seagate3tb/ModelChecking/CaseStudies/${caseStudy}/ModelChecking/queries/split";
mstmlInputFolder="/media/seagate3tb/ModelChecking/CaseStudies/${caseStudy}/SpatioTemporalAnalysis/mstml/";
multiscaleArchitectureGraphPath="/media/seagate3tb/ModelChecking/CaseStudies/${caseStudy}/ModelChecking/multiscale_architecture_graph/${caseStudyMultiscaleArchitectureGraph}";
outputFolderPath="/media/seagate3tb/ModelChecking/CaseStudies/${caseStudy}/ModelChecking/results";

# Command used to run the model checking task
${modelCheckerExecutionScript} ${modelCheckerPath} ${queriesInputFolder} ${mstmlInputFolder} ${multiscaleArchitectureGraphPath} ${outputFolderPath}
