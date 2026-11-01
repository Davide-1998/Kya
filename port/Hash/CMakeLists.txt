set(TargetName "Hash")

set(SOURCES 
	"hash.h" 
)

add_library(${TargetName} INTERFACE ${SOURCES})

set_target_properties(${TargetName} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${TargetName} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")