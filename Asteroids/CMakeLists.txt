#add_custom_target(copy_resources)

file(GLOB_RECURSE PROJ_SRC_FILES
	CONFIGURE_DEPENDS
	src/*.cpp _Interfaces/*.cpp
)

add_executable(asteroid_game
	${PROJ_SRC_FILES}
)

include_directories(headers)
include_directories(data)
include_directories(_Interfaces)
include_directories(sounds)
include_directories(structs)
 

target_link_libraries(asteroid_game PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_image SDL2::SDL2_mixer SDL2::SDL2_gfx SDL2::SDL2_ttf)



add_custom_command(
        TARGET asteroid_game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/data/
                ${CMAKE_CURRENT_BINARY_DIR}/data/
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/sounds/
                ${CMAKE_CURRENT_BINARY_DIR}/sounds/
)

#add_dependencies(textures copy_resources)
#
# 
#target_link_libraries(textures PRIVATE ${Gettingstarted_libs})
#
##to remove console and still have function main as entrypoint 
##target_link_options(textures PRIVATE "/SUBSYSTEM:WINDOWS" "/ENTRY:mainCRTStartup")
#
#add_custom_command(
#        TARGET copy_resources POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#                ${CMAKE_CURRENT_SOURCE_DIR}/resources/
#                ${CMAKE_CURRENT_BINARY_DIR}/resources/
#)
#
#add_subdirectory(Exercises)