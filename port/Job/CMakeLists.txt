set(TargetName "Job")

set(SOURCES 
	"thread-pool/include/BS_thread_pool.hpp" 
)

add_library(${TargetName} INTERFACE ${SOURCES})

set_target_properties(${TargetName} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${TargetName} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/thread-pool/include")