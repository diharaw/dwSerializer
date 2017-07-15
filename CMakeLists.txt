cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# -----------------------------------------------------------------------------------------------------------------------------
# PROJECT
# -----------------------------------------------------------------------------------------------------------------------------

project("dwSerializer")

# -----------------------------------------------------------------------------------------------------------------------------
# INCLUDES
# -----------------------------------------------------------------------------------------------------------------------------

# Setup library include paths
set(DW_INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include")

# Setup external include paths
set(JSON_INCLUDE_PATH "${PROJECT_SOURCE_DIR}/external/json/src")
set(TINYXML2_INCLUDE_PATH "${PROJECT_SOURCE_DIR}/external/tinyxml2")

# Set includes
include_directories("${DW_INCLUDE_PATH}"
                    "${JSON_INCLUDE_PATH}"
                    "${TINYXML2_INCLUDE_PATH}")

# -----------------------------------------------------------------------------------------------------------------------------
# SUB-DIRECTORIES
# -----------------------------------------------------------------------------------------------------------------------------                    

add_subdirectory("external/tinyxml2")

add_subdirectory("test")
add_subdirectory("example")

