# Update the project modified date

function(UpdateProjectModifiedDate configurationFile)
    file(
        READ 
        ${configurationFile}
        PROJECT_CONFIGURATION_FILE
    )

    GetCurrentDate(CURRENT_DATE)

    string(
        REGEX REPLACE 
        "[*][*]Modified on:[*][*] [0-9]+[.][0-9]+[.][0-9]+" 
        "**Modified on:** ${CURRENT_DATE}"
        PROJECT_MODIFIED_CONFIGURATION_FILE
        ${PROJECT_CONFIGURATION_FILE}
    )
      
    file(
        WRITE
        ${configurationFile}
        ${PROJECT_MODIFIED_CONFIGURATION_FILE}    
    )
endfunction(UpdateProjectModifiedDate)