cmake_minimum_required(VERSION 3.20)
project(shell)

set(CMAKE_CXX_STANDARD 17)

# Set to C++ 11 if you are using cpr <= 1.9.x
# More: https://github.com/libcpr/cpr#supported-releases
# set(CMAKE_CXX_STANDARD 11)

# Add your source files and header files
set(SOURCES
    main.cpp
    manager.cpp 
    parser.cpp 
    cmd.cpp 
    cmdtypes.cpp 
    helper.cpp
)

set(HEADERS
    jsonhandler.h
    requests.h
    manager.h 
    parser.h 
    cmd.h 
    cmdtypes.h 
    helper.h
)

# Specify any additional include directories
# include_directories(include)

# Create the executable and link against the external libraries
add_executable(shell ${SOURCES} ${HEADERS})

# Optionally, set compiler flags
target_compile_options(shell PRIVATE -Wall -Wextra)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 3020c34ae2b732121f37433e61599c34535e68a8) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

target_link_libraries(shell PRIVATE cpr::cpr)

# FetchContent_Declare(
#     rapidjson
#     GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
#     GIT_TAG master  # Or use a specific tag or commit hash
# )

# Include the directories
target_include_directories(shell PRIVATE
    # ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/rapidjson
)
