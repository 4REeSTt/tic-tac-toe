#add_library(secondory secondoryfuncs.cpp)
#target_link_libraries(gameStructure PUBLIC sfml-graphics sfml-window sfml-system)
#
#add_library(gameStructure game_structure.cpp)
#target_link_libraries(gameStructure PUBLIC secondory)


add_executable(${PROJECT_NAME} main.cpp secondoryfuncs.cpp game_structure.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC  sfml-graphics sfml-window sfml-system)

