#------------------------------------------------------------
# Project global variables definitions
#------------------------------------------------------------

set(PACKAGE_PROJECT_NAME "Mule")
set(PACKAGE_PROJECT_DIR "mule")


#------------------------------------------------------------
# Operating system independent configurations
#------------------------------------------------------------

# OpenCV library
find_library(OPENCV_CVCORE_LIBRARY
    NAMES opencv_core
    PATHS ${OPENCV_POSSIBLE_LIBRARY_PATHS} 
    DOC "Location of the opencv_core lib"
)

find_library(OPENCV_IMGPROC_LIBRARY
    NAMES opencv_imgproc
    PATHS ${OPENCV_POSSIBLE_LIBRARY_PATHS} 
    DOC "Location of the opencv_imgproc lib"
)  

find_library(OPENCV_HIGHGUI_LIBRARY
    NAMES opencv_highgui
    PATHS ${OPENCV_POSSIBLE_LIBRARY_PATHS} 
    DOC "Location of the opencv_highgui lib"
)
    
install(
    FILES 
    ${OPENCV_CVCORE_LIBRARY}.${OpenCV_VERSION_MAJOR}.${OpenCV_VERSION_MINOR}.${OpenCV_VERSION_PATCH}
    ${OPENCV_IMGPROC_LIBRARY}.${OpenCV_VERSION_MAJOR}.${OpenCV_VERSION_MINOR}.${OpenCV_VERSION_PATCH} 
    ${OPENCV_HIGHGUI_LIBRARY}.${OpenCV_VERSION_MAJOR}.${OpenCV_VERSION_MINOR}.${OpenCV_VERSION_PATCH}
    DESTINATION lib
)

# Xerces C library
install(FILES ${XERCESC_LIBRARY} DESTINATION lib)


#------------------------------------------------------------
# Operating system dependent configurations
#------------------------------------------------------------

if(UNIX)
    # Install application icon
    install(FILES "${PROJECT_SOURCE_DIR}/cmake/package/desktop/Mule.desktop" DESTINATION /usr/share/applications)
    install(FILES "${PROJECT_SOURCE_DIR}/cmake/package/ico/Mule.png" DESTINATION /usr/share/icons)

    # Add postinst script to debian package
    set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${PROJECT_SOURCE_DIR}/cmake/package/postinstall/postinst")

    set(CPACK_GENERATOR "DEB")

    set(CPACK_SYSTEM_NAME "Linux-${CPACK_SYSTEM_NAME}")
    
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Ovidiu Parvu")
    set(CPACK_DEBIAN_PACKAGE_SECTION "Science")
    
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
    
    set(CPACK_PACKAGING_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
elseif(WIN32)
    # Install application icon
    install(FILES "${PROJECT_SOURCE_DIR}/cmake/package/ico\\\\Mule.ico" DESTINATION ico)

    set(CPACK_GENERATOR "NSIS")
    
    set(CPACK_NSIS_MUI_ICON "${PROJECT_SOURCE_DIR}/cmake/package/ico\\\\Mule.ico")
    set(CPACK_NSIS_MUI_UNIICON "${CPACK_NSIS_MUI_ICON}")
    set(CPACK_PACKAGE_ICON "${CPACK_NSIS_MUI_ICON}")
    
    set(CPACK_NSIS_CREATE_ICONS_EXTRA "
        CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\${PACKAGE_PROJECT_NAME}.lnk\\\" \\\"$INSTDIR\\\\bin\\\\${PACKAGE_PROJECT_NAME}.exe\\\" \\\"\\\" \\\"$INSTDIR\\\\ico\\\\${PACKAGE_PROJECT_NAME}.ico\\\"
        StrCmp \\\"$INSTALL_DESKTOP\\\" \\\"1\\\" 0 +2
        CreateShortCut \\\"$DESKTOP\\\\${PACKAGE_PROJECT_NAME}.lnk\\\" \\\"$INSTDIR\\\\bin\\\\${PACKAGE_PROJECT_NAME}.exe\\\" \\\"\\\" \\\"$INSTDIR\\\\ico\\\\${PACKAGE_PROJECT_NAME}.ico\\\"
    ")
    
    set(CPACK_NSIS_DELETE_ICONS_EXTRA "
        Delete \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\${PACKAGE_PROJECT_NAME}.lnk\\\"
        StrCmp \\\"$INSTALL_DESKTOP\\\" \\\"1\\\" 0 +2
        Delete \\\"$DESKTOP\\\\${PACKAGE_PROJECT_NAME}.lnk\\\"
    ")
    
    set(CPACK_SYSTEM_NAME "Windows-${CPACK_SYSTEM_NAME}")
    
    set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
    
    set(CPACK_NSIS_MODIFY_PATH ON)
    
    set(CPACK_NSIS_DISPLAY_NAME ${PACKAGE_PROJECT_NAME})
    set(CPACK_NSIS_PACKAGE_NAME ${PACKAGE_PROJECT_NAME})
    
    set(CPACK_NSIS_HELP_LINK "http://mule.modelchecking.org")
    set(CPACK_NSIS_URL_INFO_ABOUT "http://mule.modelchecking.org")
    set(CPACK_NSIS_CONTACT "ovidiu.parvu@gmail.com")
endif(UNIX)


#------------------------------------------------------------
# General package description
#------------------------------------------------------------

set(CPACK_PACKAGE_NAME "${PACKAGE_PROJECT_NAME}")

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PACKAGE_PROJECT_NAME} - multiscale multidimensional meta model checking")
set(CPACK_PACKAGE_DESCRIPTION "${PACKAGE_PROJECT_NAME} is a multiscale multidimensional spatio-temporal meta model checker employed for the formal validation of computational models")

set(CPACK_PACKAGE_FILE_NAME "${PACKAGE_PROJECT_NAME}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PACKAGE_PROJECT_NAME}")

set(CPACK_PACKAGE_VENDOR "Ovidiu Parvu")

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_BUILD "${PROJECT_VERSION_BUILD}")
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_BUILD}")

set(CPACK_PACKAGE_EXECUTABLES "Mule;Mule")
set(CPACK_CREATE_DESKTOP_LINKS "Mule")

# Set the CPack system name to either "x86" or "x64"
string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" CMAKE_SYSTEM_PROCESSOR_LOWERCASE)
if(
    CMAKE_SYSTEM_PROCESSOR_LOWERCASE STREQUAL "x86_64" OR 
    CMAKE_SYSTEM_PROCESSOR_LOWERCASE STREQUAL "x64" OR
    CMAKE_SYSTEM_PROCESSOR_LOWERCASE STREQUAL "ia64" OR
    CMAKE_SYSTEM_PROCESSOR_LOWERCASE STREQUAL "amd64" 
)
    set(CPACK_SYSTEM_NAME "x64")
else(
    CMAKE_SYSTEM_PROCESSOR_LOWERCASE STREQUAL "x86_64" OR 
    CMAKE_SYSTEM_PROCESSOR_LOWERCASE STREQUAL "x64" OR
    CMAKE_SYSTEM_PROCESSOR_LOWERCASE STREQUAL "ia64" OR
    CMAKE_SYSTEM_PROCESSOR_LOWERCASE STREQUAL "amd64" 
)
    set(CPACK_SYSTEM_NAME "x86")
endif(
    CMAKE_SYSTEM_PROCESSOR_LOWERCASE STREQUAL "x86_64" OR 
    CMAKE_SYSTEM_PROCESSOR_LOWERCASE STREQUAL "x64" OR
    CMAKE_SYSTEM_PROCESSOR_LOWERCASE STREQUAL "ia64" OR
    CMAKE_SYSTEM_PROCESSOR_LOWERCASE STREQUAL "amd64" 
)

 
#------------------------------------------------------------
# Include CPack
#------------------------------------------------------------

include(CPack)