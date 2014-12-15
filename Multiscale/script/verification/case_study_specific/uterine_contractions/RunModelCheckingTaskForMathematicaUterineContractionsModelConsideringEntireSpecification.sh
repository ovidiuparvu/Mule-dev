# Constants initialisations
# (TODO: Update)
caseStudy="UterineContractions";
caseStudyTypeSemanticsTable="type_semantics_table_uterine_contractions.xml";

# Path initialisations
modelCheckerExecutionScript="/home/ovidiu/Repositories/git/multiscale/Multiscale/script/verification/ExecuteProbabilisticBlackBoxModelCheckingUsingMuleForEntireSpecificationNoExtraEvaluation.sh";
modelCheckerPath="/home/ovidiu/Repositories/git/multiscale/Multiscale/bin/Mule";
queriesInputFolder="/media/seagate3tb/ModelChecking/CaseStudies/${caseStudy}/ModelChecking/queries";
mstmlInputFolder="/media/seagate3tb/ModelChecking/CaseStudies/${caseStudy}/SpatioTemporalAnalysis/mstml/";
typeSemanticsTablePath="/media/seagate3tb/ModelChecking/CaseStudies/${caseStudy}/ModelChecking/type_semantics_table/${caseStudyTypeSemanticsTable}";
outputFolderPath="/media/seagate3tb/ModelChecking/CaseStudies/${caseStudy}/ModelChecking/results";

# Command used to run the model checking task
${modelCheckerExecutionScript} ${modelCheckerPath} ${queriesInputFolder} ${mstmlInputFolder} ${typeSemanticsTablePath} ${outputFolderPath}
