cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_definitions(-Wall -Wextra)

# L'exécutable principal
project(ReachabilityGame)

set(TARGET_NAME "ReachabilityGame")
set(LIBRARY_NAME ${TARGET_NAME}-lib)

set(SOURCES
    src/Vertex.cpp
    src/Graph.cpp
    src/Player.cpp
    src/Path.cpp
    src/Game.cpp
    src/ReachabilityGame.cpp
    src/MinMaxGame.cpp

    src/types/Long.cpp

    src/exploration/BestFirstSearch.cpp
    src/exploration/RandomPaths.cpp

    src/algorithms/Tarjan.cpp

    src/generators/GenerateWeights.cpp
    src/generators/RandomGenerator.cpp
    src/generators/RandomTreeLikeGenerator.cpp
    src/generators/RandomStronglyConnectedGenerator.cpp
)

add_library(${LIBRARY_NAME} ${SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC include)

add_executable(${TARGET_NAME} src/main.cpp)
target_link_libraries(${TARGET_NAME} ${LIBRARY_NAME})

# Générateur aléatoire naïf
add_executable(random_generator generators/randomGenerator.cpp)
target_link_libraries(random_generator ${LIBRARY_NAME})
target_include_directories(random_generator PUBLIC include)

# Générateur arbre
add_executable(tree_like_generator generators/treeLikeGenerator.cpp)
target_link_libraries(tree_like_generator ${LIBRARY_NAME})
target_include_directories(tree_like_generator PUBLIC include)

# Générateur fortement connexe
add_executable(strongly_connected_generator generators/stronglyConnectedGraph.cpp)
target_link_libraries(strongly_connected_generator ${LIBRARY_NAME})
target_include_directories(strongly_connected_generator PUBLIC include)

# Pour essayer de trouver un EN tel que pas tout le monde voit une cible sur un graphe fortement connexe
add_executable(find_EN generators/findEN.cpp)
target_link_libraries(find_EN ${LIBRARY_NAME})
target_include_directories(find_EN PUBLIC include)

# Documentation
set(BUILD_DOC FALSE CACHE BOOL "S'il faut construire la documentation ou pas")
if(BUILD_DOC)
    add_subdirectory(docs)
endif(BUILD_DOC)

# Tests unitaires
set(BUILD_TESTS FALSE CACHE BOOL "S'il faut construire les tests ou pas")
if(BUILD_TESTS)
    add_subdirectory(tests)
endif(BUILD_TESTS)

# Tests de performance
set(BUILD_PERFORMANCE FALSE CACHE BOOL "S'il faut construire les tests de performance ou pas")
if(BUILD_PERFORMANCE)
    add_subdirectory(performance)
endif(BUILD_PERFORMANCE)