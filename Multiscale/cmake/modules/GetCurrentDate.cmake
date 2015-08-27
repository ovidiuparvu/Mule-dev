# Get the current year

function(GetCurrentYear RESULT)
    IF (WIN32)
        EXECUTE_PROCESS(COMMAND "cmd" " /C date /T" OUTPUT_VARIABLE DATE)
        string(REGEX REPLACE "(..)/(..)/(....).*" "\\3" FORMATTED_YEAR ${DATE})
    ELSEIF(UNIX)
        EXECUTE_PROCESS(COMMAND "date" "+%d/%m/%Y" OUTPUT_VARIABLE DATE)
        string(REGEX REPLACE "(..)/(..)/(....).*" "\\3" FORMATTED_YEAR ${DATE})
    ELSE (WIN32)
        MESSAGE(SEND_ERROR "Date function not implemented.")
        SET(${FORMATTED_YEAR} 0000)
    ENDIF (WIN32)
    
    SET(${RESULT} ${FORMATTED_YEAR} PARENT_SCOPE)
endfunction(GetCurrentYear)


# Get the current date

function(GetCurrentDate RESULT)
    IF (WIN32)
        EXECUTE_PROCESS(COMMAND "cmd" " /C date /T" OUTPUT_VARIABLE DATE)
        string(REGEX REPLACE "(..)/(..)/(....).*" "\\1.\\2.\\3" FORMATTED_DATE ${DATE})
    ELSEIF(UNIX)
        EXECUTE_PROCESS(COMMAND "date" "+%d/%m/%Y" OUTPUT_VARIABLE DATE)
        string(REGEX REPLACE "(..)/(..)/(....).*" "\\1.\\2.\\3" FORMATTED_DATE ${DATE})
    ELSE (WIN32)
        MESSAGE(SEND_ERROR "Date function not implemented.")
        SET(${FORMATTED_DATE} 000000)
    ENDIF (WIN32)
    
    SET(${RESULT} ${FORMATTED_DATE} PARENT_SCOPE)
endfunction(GetCurrentDate)