enable_language(ASM_MASM)

set(MINHOOK_DIR ${CMAKE_SOURCE_DIR}/third_party/minhook)

set(HEADERS
    OrbitAsm.h
    include/hijk/hijk.h
)

set(SOURCES 
    Orbit.asm
    OrbitAsm.cpp
    hijk.cpp
)

set(HDE_FILES
    ${MINHOOK_DIR}/src/HDE/hde32.h
    ${MINHOOK_DIR}/src/HDE/hde32.c
    ${MINHOOK_DIR}/src/HDE/hde64.h
    ${MINHOOK_DIR}/src/HDE/hde64.c
    ${MINHOOK_DIR}/src/HDE/table32.h
    ${MINHOOK_DIR}/src/HDE/table64.h
    ${MINHOOK_DIR}/src/HDE/pstdint.h
)

set(MINHOOK_FILES
    ${MINHOOK_DIR}/include/MinHook.h
    ${MINHOOK_DIR}/src/buffer.h
    ${MINHOOK_DIR}/src/buffer.c
    ${MINHOOK_DIR}/src/hook.c
    ${MINHOOK_DIR}/src/trampoline.h
    ${MINHOOK_DIR}/src/trampoline.c
)

source_group("HDE"          FILES ${HDE_FILES})
source_group("MinHook"      FILES ${MINHOOK_FILES})
source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})

add_library(hijk SHARED 
	${SOURCES} 
    ${HEADERS} 
    ${HDE_FILES} 
    ${MINHOOK_FILES}
)

target_include_directories(hijk PRIVATE
    ${MINHOOK_DIR}/include
    ${MINHOOK_DIR}/src
)

target_include_directories(hijk PUBLIC 
    "include"
)

add_executable(hijk_example main.cpp)
target_link_libraries(hijk_example hijk)