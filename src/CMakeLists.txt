set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(example
    PRIVATE
        "${DIR}/game.cpp"
        "${DIR}/main.cpp"
        "${DIR}/cube.cpp"
        "${DIR}/gamecamera.cpp"
)
target_include_directories(example PRIVATE "${example_SOURCE_DIR}/include")
target_include_directories(example PRIVATE "${madd_SOURCE_DIR}/include/engine")
MESSAGE(STATUS "${example_SOURCE_DIR}/include/game")