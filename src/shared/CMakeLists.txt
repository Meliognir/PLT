
set(lib_shared_target shared_static)

# Generate header files from dia UML files
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../state.dia")
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../engine.dia")
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../ai.dia")

# Find all source files to compile into a library
file(GLOB_RECURSE shared_sources *.cpp)

# Build the "shared" library and add required includes
add_library(${lib_shared_target} STATIC ${shared_sources} ${jsoncpp_sources}
        #state/Tile.cpp
        #state/Canon.cpp
        #state/Gold.cpp
        #state/Food.cpp
        #state/PlayingState.cpp
        #state/GameConfigState.cpp
        #state/Player.cpp
        #ai/RandomAI.cpp
        #ai/HeuristicAI.cpp
        #ai/DeepAI.cpp
        #ai/AI.cpp
        #state/Observable.cpp
        ../client/client/InputHandler.cpp
        engine/GameEngine.cpp
        state/GameOverState.cpp
        engine/CombatManager.cpp
        state/CardActionState.cpp)

add_dependencies(${lib_shared_target} generate-headers)
target_include_directories(${lib_shared_target} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${jsoncpp_include_dir}
  ${CMAKE_CURRENT_SOURCE_DIR}/../server
  )

# vim: set sw=2 sts=2 et:

