######################################
#        SPHINX DOCUMENTATION        #
######################################

find_package(Sphinx REQUIRED)

set(IMAGES "${CMAKE_CURRENT_SOURCE_DIR}/")

if(NOT DEFINED SPHINX_THEME)
    set(SPHINX_THEME default)
endif()
 
if(NOT DEFINED SPHINX_THEME_DIR)
    set(SPHINX_THEME_DIR)
endif()
 
# configured documentation tools and intermediate build results
set(BINARY_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/sphinx/_build")
 
# Sphinx cache with pickled ReST documents
set(SPHINX_CACHE_DIR "${CMAKE_CURRENT_BINARY_DIR}/sphinx/_doctrees")
 
# HTML output directory
set(SPHINX_HTML_DIR "${CMAKE_CURRENT_BINARY_DIR}/sphinx/html")

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/sphinx/images" DESTINATION "${BINARY_BUILD_DIR}")

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/sphinx/conf.py"
    "${BINARY_BUILD_DIR}/conf.py"
    @ONLY)
    
add_custom_target(sphinx_doc
    ${SPHINX_EXECUTABLE}
        -b html
        -c "${BINARY_BUILD_DIR}"
        -d "${SPHINX_CACHE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/sphinx"
        "${SPHINX_HTML_DIR}"
    COMMENT "Building HTML documentation with Sphinx")
    
######################################
#       DOXYGEN DOCUMENTATION        #
######################################
# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/doxygen_config_file.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/doxygen/Doxyfile)
    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/doxygen/images" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/doxygen")
    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/doxygen/README.md" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/doxygen")
    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/doxygen/hardware.md" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/doxygen")
    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/doxygen/firmware.md" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/doxygen")

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target(doxygen_doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)