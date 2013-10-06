# Add a unit test

function(AddUnitTest testName)
    set_target_properties(${testName}
        PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/test
        DEBUG_POSTFIX _d
    )        
    
    add_test(${testName} ${testName})
endfunction(AddUnitTest)

