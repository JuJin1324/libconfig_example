cmake_minimum_required(VERSION 3.15)
project(libconfig_example C)

set(CMAKE_C_STANDARD 99)

#set(ARM_LINUX_COMPILE ON)

## 크로스 컴파일(Cross Compile) 옵션 셋팅
if (${ARM_LINUX_COMPILE})
    message("BUILD ARCH : ARM-LINUX")

    ## arm-linux Cross Compile Options for macOS(Ubuntu dosen't need below options)
    set(ARM_LINUX_TOOLCHAIN_DIR /usr/local/arm-unknown-linux-gnueabi)
    set(CMAKE_C_COMPILER    ${ARM_LINUX_TOOLCHAIN_DIR}/bin/arm-unknown-linux-gnueabi-gcc)
    set(CMAKE_LINKER        ${ARM_LINUX_TOOLCHAIN_DIR}/bin/arm-unknown-linux-gnueabi-ld)
    set(CMAKE_NM            ${ARM_LINUX_TOOLCHAIN_DIR}/bin/arm-unknown-linux-gnueabi-nm)
    set(CMAKE_OBJCOPY       ${ARM_LINUX_TOOLCHAIN_DIR}/bin/arm-unknown-linux-gnueabi-objcopy)
    set(CMAKE_OBJDUMP       ${ARM_LINUX_TOOLCHAIN_DIR}/bin/arm-unknown-linux-gnueabi-objdump)
    set(CMAKE_RANLIB        ${ARM_LINUX_TOOLCHAIN_DIR}/bin/arm-unknown-linux-gnueabi-ranlib)
    include_directories(${ARM_LINUX_TOOLCHAIN_DIR}/arm-unknown-linux-gnueabi/sysroot/usr/include)

    ### ARM 컴파일용 log4c 라이브러리 디렉토리 설정
    set(CONFIG_LIB_DIR /usr/local/arm-linux-libconfig)

    ## macOS : warning: cannot find entry symbol arch_paths_first; 에러 대처
    set(HAVE_FLAG_SEARCH_PATHS_FIRST 0)
    set(CMAKE_C_LINK_FLAGS "")
    set(CMAKE_CXX_LINK_FLAGS "")
else () # LOCAL
    message("BUILD ARCH : i386(LOCAL)")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D__LOCAL__")
    set(CMAKE_C_COMPILER gcc)

    ### x86_64 컴파일용 log4c 라이브러리 디렉토리 설정
    set(CONFIG_LIB_DIR /usr/local)
endif ()
### 공통 설정
include_directories(${CONFIG_LIB_DIR}/include)
##########################################
## Macro
### CMake의 예약변수들에 대한 내용을 모두 출력하도록 하는 매크로
macro(print_all_variables)
    message(STATUS "print_all_variables------------------------------------------{")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
    message(STATUS "print_all_variables------------------------------------------}")
endmacro()

#print_all_variables()

add_executable(libconfig_example src/main.c)
target_link_libraries(libconfig_example -L${CONFIG_LIB_DIR}/lib config)