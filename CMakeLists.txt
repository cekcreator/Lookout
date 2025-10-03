cmake_minimum_required(VERSION 3.25)  # newer CMake handles std flags better
project(Lookout LANGUAGES CXX)

# (Optional, but good hygiene)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set your project to C++23 (pick ONE style)
# A) Exact standard:
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# or B) Minimum standard on the target (comment A out if you use this):
# target_compile_features(MyAwesomeApp PUBLIC cxx_std_23)

# ---- Cinder ----
set(CINDER_PATH "/Users/calebkumar/Desktop/Desktop_Calebs_Pro/coding/graphics/Cinder")
add_subdirectory(${CINDER_PATH} ${CINDER_PATH}/build)

# ---- App target ----
include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )

get_filename_component( APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE )

ci_make_app(
        SOURCES     ${APP_PATH}/Lookout/app/Lookout.cc
        CINDER_PATH ${CINDER_PATH}
)
#target_link_libraries(Lookout PRIVATE cinder)
target_include_directories(Lookout PRIVATE ${CINDER_PATH}/include)

# --- Critical bit: clear Cinder's exported -std=c++17 so your setting applies ---
# (Do this AFTER add_subdirectory() so the 'cinder' target exists.)
get_property(_opts TARGET cinder PROPERTY INTERFACE_COMPILE_OPTIONS)
message(STATUS "cinder INTERFACE_COMPILE_OPTIONS before: ${_opts}")

# Let your app control the standard flag:
set_property(TARGET cinder PROPERTY INTERFACE_COMPILE_OPTIONS "")
