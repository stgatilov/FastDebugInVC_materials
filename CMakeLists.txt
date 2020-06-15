# Disable "Basic Runtime Checks"
string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

# Enable "level 1 inlining"
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Ob1")

# Switch to "release CRT"
string(REPLACE "/MDd" "/MD" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

set(sources
    MeasurePerformance.cpp
    VectorOutOfBounds.cpp
    StackCorruption.cpp
    HeapCorruption.cpp
)
add_executable(FastDebugDemo ${sources})


# Enable "level 1 inlining" on individual files
# set_source_files_properties(${sources} PROPERTIES COMPILE_FLAGS "/Ob1")

# Switch to "release CRT": does not work
# set_property(TARGET FastDebugDemo PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
