cmake_minimum_required(VERSION 3.15)

project(Zone VERSION 1.0 DESCRIPTION "Zone NN API")

set(TARGET zone)

# Set C standard
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Define compiler warnings in one place
set(C_WARNINGS "-Wall -Wextra -Wshadow -Wformat=2 -Wunused")

# Set flags for Debug and Release configurations
set(CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS_DEBUG} -ggdb3 -O0 -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS_RELEASE} -O3")

# Set version script
set(VERSION_SCRIPT ${CMAKE_SOURCE_DIR}/zone.map.txt)
if(EXISTS ${VERSION_SCRIPT})
  set(VERSION_SCRIPT_FLAGS "-Wl,--version-script,${VERSION_SCRIPT}" "-Wl,--no-undefined-version")
else()
  set(VERSION_SCRIPT_FLAGS "")
endif()

# Include source and header files
include(sources.cmake)
include(headers.cmake)


include(ExternalProject)

ExternalProject_Add(
  ZObject 
  SOURCE_DIR /sdcard/Jay/Projects/xab_laud_ubject/zobject/
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/
  BUILD_ALWAYS TRUE
)

ExternalProject_Add(
  Zot 
  SOURCE_DIR /sdcard/Jay/Projects/xab_laud_ubject/zot/
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/
  BUILD_ALWAYS TRUE
)

ExternalProject_Add(
  Zode 
  SOURCE_DIR /sdcard/Jay/Projects/xab_laud_ubject/zode/
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/
  BUILD_ALWAYS TRUE
)

# Create INTERFACE target for shared flags
add_library(zone_c_flags INTERFACE)
target_compile_features(zone_c_flags INTERFACE c_std_23)
target_compile_options(
  zone_c_flags
  INTERFACE
    "$<BUILD_INTERFACE:${C_WARNINGS}>"
)
target_link_options(
  zone_c_flags
  INTERFACE
    ${VERSION_SCRIPT_FLAGS}
)


# Main library setup
add_library(${TARGET} SHARED)
target_sources(${TARGET} PRIVATE ${SOURCE_FILES})
target_link_options(${TARGET} PRIVATE ${VERSION_SCRIPT_FLAGS})
set_target_properties(${TARGET} PROPERTIES LINK_DEPENDS ${VERSION_SCRIPT})
target_include_directories(${TARGET} PRIVATE ${CMAKE_BINARY_DIR}/include ${CMAKE_BINARY_DIR}/include ${CMAKE_BINARY_DIR}/include)
target_link_directories(${TARGET} PRIVATE ${CMAKE_BINARY_DIR}/bin/ ${CMAKE_BINARY_DIR}/lib/ ${CMAKE_BINARY_DIR}/lib)
target_link_libraries(${TARGET} PRIVATE zobject zot zode)
add_dependencies(${TARGET} ZObject Zot Zode)

set(ZOR_SRC /sdcard/Jay/Projects/xab_laud_ubject/zor)
ExternalProject_Add(
  Zor
  SOURCE_DIR ${ZOR_SRC}
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/
  BUILD_BYPRODUCTS ${CMAKE_BINARY_DIR}/bin/libzor.so
  BUILD_ALWAYS TRUE
)

add_executable(example-0 examples/example-0.c)
target_link_libraries(example-0 PRIVATE ${TARGET} zobject zode zor)
target_include_directories(example-0 PRIVATE ${CMAKE_BINARY_DIR}/include )
target_link_directories(example-0 PRIVATE ${CMAKE_BINARY_DIR}/bin/ ${CMAKE_BINARY_DIR}/lib/ ${CMAKE_BINARY_DIR}/lib/)
add_dependencies(${TARGET} Zor)

# Tests section
# Option to enable or disable tests
option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
  include(include_google_test.cmake)
  add_executable(zone_test tests/zonetest.cpp )
  target_link_libraries(zone_test PRIVATE ${TARGET} gtest gtest_main)
  enable_testing()

  include(GoogleTest)
  gtest_discover_tests(zone_test)
endif()

# Install targets
install(TARGETS ${TARGET} DESTINATION bin)
install(FILES ${HEADER_FILES} DESTINATION include)
install(FILES ./assets/sample_text.txt DESTINATION assets)