project(pss
	LANGUAGES C
)

set(SOURCES 
	"src/decode.c"
	"src/pss.c" 
)

set(HEADERS 
	"${CMAKE_CURRENT_SOURCE_DIR}/include/decode.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/pss.h"
)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

add_subdirectory("ext/libmpeg2")
add_subdirectory("ext/libfmemopen")

target_link_libraries(${PROJECT_NAME} PUBLIC libmpeg2 libfmemopen)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")