cmake_minimum_required(VERSION 3.17)
project(MathExprLang)

# Set constants
set(CMAKE_CXX_STANDARD 20)
set(LLVM_DIR $ENV{LLVM_DIR})

# Find LLVM
find_package(LLVM REQUIRED CONFIG)
message(STATUS "MathExpr: Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "MathExpr: Using LLVMConfig.cmake from ${LLVM_DIR}")
message(STATUS "MathExpr: LLVM include dirs: ${LLVM_INCLUDE_DIRS}")
include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

# Map LLVM components to lib names
llvm_map_components_to_libnames(LLVM_LIBS aarch64codegen amdgpucodegen armcodegen avrcodegen bpfcodegen hexagoncodegen
        lanaicodegen loongarchcodegen mcjit mipscodegen msp430codegen nativecodegen nvptxcodegen powerpccodegen riscvcodegen
        sparccodegen systemzcodegen target vecodegen webassemblycodegen x86codegen xcorecodegen)

# Include main module
include_directories(src)
add_subdirectory(src)