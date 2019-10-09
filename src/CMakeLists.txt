set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(miner1.5
    PRIVATE
        "${DIR}/game.cpp"
        "${DIR}/main.cpp"
        "${DIR}/gamecamera.cpp"
        "${DIR}/blockmanager.cpp"
        "${DIR}/generator.cpp"
)
target_include_directories(miner1.5 PRIVATE "${miner1.5_SOURCE_DIR}/include")
target_include_directories(miner1.5 PRIVATE "${madd_SOURCE_DIR}/include")
