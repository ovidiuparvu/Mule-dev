# Path initialisations
modelCheckerExecutionScript="/home/ovidiu/Repositories/git/multiscale/Multiscale/script/verificationExecuteProbabilisticBlackBoxModelCheckingUsingMuleNoExtraEvaluation.sh";
queriesInputFolder="/media/seagate3tb/ModelChecking/CaseStudies/CardiovascularVPR/ModelChecking/queries/split";
mstmlInputFolder="/media/seagate3tb/ModelChecking/CaseStudies/CardiovascularVPR/SpatioTemporalAnalysis/mstml/";
typeSemanticsTablePath="/media/seagate3tb/ModelChecking/CaseStudies/CardiovascularVPR/ModelChecking/type_semantics_table/type_semantics_table_cardiovascular_vpr.xml";
outputFolderPath="/media/seagate3tb/ModelChecking/CaseStudies/CardiovascularVPR/ModelChecking/results";

# Command used to run the model checking task
${modelCheckerExecutionScript} ${queriesInputFolder} ${mstmlInputFolder} ${typeSemanticsTablePath} ${outputFolderPath}
