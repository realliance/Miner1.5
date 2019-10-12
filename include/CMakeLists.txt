set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(miner1.5
    PRIVATE
		"${DIR}/game.h"
        "${DIR}/main.h"
        "${DIR}/block.h"
        "${DIR}/placedblock.h"
        "${DIR}/blockregistrysystem.h"
        "${DIR}/blockplacesystem.h"
        "${DIR}/gamecamera.h"
        "${DIR}/generator.h"
        "${DIR}/systems.h"
        "${DIR}/blockdistribution.h"
)
target_include_directories(miner1.5 PRIVATE "${miner1.5_SOURCE_DIR}/include")
