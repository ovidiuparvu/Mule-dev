# Add a sample

function(AddSample sampleName)
    set_target_properties(${sampleName}
        PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/sample
    )        
endfunction(AddSample)

