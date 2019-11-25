cmake_minimum_required (VERSION 3.8)
project ("SanaeBulletEngine")
find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_path(LUA_INCLUDE_DIR lua.h PATH_SUFFIXES lua)
find_library(LUA_LIBRARY lua)
file(GLOB_RECURSE SOURCE_CODE *.cpp *.hpp)
file(GLOB_RECURSE GAME_FOLDER ../game/*.*)
file(GLOB_RECURSE DATA_FOLDER ../data/*.*)
# Add source to this project's executable.
add_executable (SBE ${SOURCE_CODE})
add_custom_command(TARGET SBE POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/game/ $<TARGET_FILE_DIR:SBE>/game)
add_custom_command(TARGET SBE POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/data/ $<TARGET_FILE_DIR:SBE>/data)
foreach(fi ${GAME_FOLDER})
    add_custom_command(TARGET SBE POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/game/${f}
            $<TARGET_FILE_DIR:SBE>/game/${f} )
endforeach()
foreach(fi ${DATA_FOLDER})
    add_custom_command(TARGET SBE POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/data/${f}
            $<TARGET_FILE_DIR:SBE>/data/${f} )
endforeach()
target_include_directories(SBE PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(SBE PRIVATE SDL2::SDL2 SDL2::SDL2_image ${LUA_LIBRARY})
set_property(TARGET SBE PROPERTY CXX_STANDARD 20)