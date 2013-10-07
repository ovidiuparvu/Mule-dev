# Increment doxygen documentation build number

function(IncrementDoxygenBuildNumber buildType inputFile outputFile)
    if(CMAKE_BUILD_TYPE STREQUAL ${buildType})
        file(
            STRINGS 
            ${outputFile}
            PROJECT_NUMBER_STRING
            REGEX "^PROJECT_NUMBER = [0-9]+[.][0-9]+[.][0-9]+"
        )
           
        string(REGEX MATCH " [0-9]+[.]" MAJOR ${PROJECT_NUMBER_STRING})
        string(REGEX REPLACE "[ .]+" "" PROJECT_VERSION_MAJOR ${MAJOR})
            
        string(REGEX MATCH "[.][0-9]+[.]" MINOR ${PROJECT_NUMBER_STRING})
        string(REGEX REPLACE "[.]+" "" PROJECT_VERSION_MINOR ${MINOR})
        
        string(REGEX MATCH "[.][0-9]+$" BUILD ${PROJECT_NUMBER_STRING})
        string(REGEX REPLACE "[.]+" "" PROJECT_VERSION_BUILD ${BUILD})
        math(EXPR PROJECT_VERSION_BUILD "${PROJECT_VERSION_BUILD} + 1")
        
        configure_file(
            ${inputFile} ${outputFile}
        )
    endif(CMAKE_BUILD_TYPE STREQUAL ${buildType})       
endfunction(IncrementDoxygenBuildNumber)

