cmake_minimum_required(VERSION 3.23)

project(AiZOProjekt2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_CXX_COMPILER "g++")

file(GLOB SOURCES "*.cpp")
add_executable(AiZOProjekt2 ${SOURCES})

target_include_directories(AiZOProjekt2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_directories(AiZOProjekt2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_link_libraries(AiZOProjekt2 PRIVATE parameters)

if(WIN32)
    set(LIB_FILE ${CMAKE_SOURCE_DIR}/lib/libparameters.dll)

    add_custom_command(TARGET AiZOProjekt2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${LIB_FILE}
        $<TARGET_FILE_DIR:AiZOProjekt2>
    )

elseif(UNIX)
    set(LIB_FILE ${CMAKE_SOURCE_DIR}/lib/libparameters.so)

    add_custom_command(TARGET AiZOProjekt2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${LIB_FILE}
        $<TARGET_FILE_DIR:AiZOProjekt2>
    )
endif()