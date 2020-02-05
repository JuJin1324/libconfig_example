cmake_minimum_required(VERSION 3.15)
project(libconfig_example C)

set(CMAKE_C_STANDARD 99)

################### 사용자 지정 ####################
### ARM_LINUX 전용 컴파일 옵션
#set(ARM_LINUX_COMPILE ON)

#################################################
#################### Macro ######################
### external 디렉터리 아래 OS이름으로 된 디렉터리 명에 따라서 해당 OS에서 사용할 라이브러리를 선택하는 매크로
macro(set_external_library os_name)
    set(EXTERNAL_LIB_OS_DIR external/${os_name})
    set(EXTERNAL_LIB_ROOT ${CMAKE_SOURCE_DIR}/external/${os_name})
    set(EXTERNAL_LIB_DLL ${EXTERNAL_LIB_ROOT}/bin)
    set(EXTERNAL_INCLUDE_DIR ${EXTERNAL_LIB_ROOT}/include)
    set(EXTERNAL_LIB_DIR ${EXTERNAL_LIB_ROOT}/lib)

    include_directories(${EXTERNAL_INCLUDE_DIR})
endmacro()

macro(arm_linux_options_for_macOS)
    set(ARM_LINUX_TOOLCHAIN_DIR /usr/local/arm-unknown-linux-gnueabi)
    set(CMAKE_C_COMPILER ${ARM_LINUX_TOOLCHAIN_DIR}/bin/arm-unknown-linux-gnueabi-gcc)
    set(CMAKE_LINKER ${ARM_LINUX_TOOLCHAIN_DIR}/bin/arm-unknown-linux-gnueabi-ld)
    set(CMAKE_NM ${ARM_LINUX_TOOLCHAIN_DIR}/bin/arm-unknown-linux-gnueabi-nm)
    set(CMAKE_OBJCOPY ${ARM_LINUX_TOOLCHAIN_DIR}/bin/arm-unknown-linux-gnueabi-objcopy)
    set(CMAKE_OBJDUMP ${ARM_LINUX_TOOLCHAIN_DIR}/bin/arm-unknown-linux-gnueabi-objdump)
    set(CMAKE_RANLIB ${ARM_LINUX_TOOLCHAIN_DIR}/bin/arm-unknown-linux-gnueabi-ranlib)
    include_directories(${ARM_LINUX_TOOLCHAIN_DIR}/arm-unknown-linux-gnueabi/sysroot/usr/include)

    ## Darwin : warning: cannot find entry symbol arch_paths_first; 에러 대처
    set(HAVE_FLAG_SEARCH_PATHS_FIRST 0)
    set(CMAKE_C_LINK_FLAGS "")
    set(CMAKE_CXX_LINK_FLAGS "")
endmacro()

### CMake의 예약변수들에 대한 내용을 모두 출력하도록 하는 매크로
macro(print_all_variables)
    message(STATUS "print_all_variables------------------------------------------{")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach ()
    message(STATUS "print_all_variables------------------------------------------}")
endmacro()
#print_all_variables()

##########################################
## 운영체제에 따른 빌드 옵션 설정
if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin")
    ### Darwin
    message("BUILD OS : macOS(${CMAKE_HOST_SYSTEM_NAME})")

elseif (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    ### X86_64 Linux
    message("BUILD OS : ${CMAKE_HOST_SYSTEM_NAME}")
elseif (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    ### Microsoft Windows
    message("BUILD OS : ${CMAKE_HOST_SYSTEM_NAME}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexec-charset=CP949")         # 윈도우에서 CLion을 통해 생성한 .exe 파일 실행 시 한글 깨짐 현상 방지
endif ()

if (${ARM_LINUX_COMPILE})
    ### ARM-LINUX(텔라딘)
    message("TARGET OS : ARM-LINUX")
    arm_linux_options_for_macOS()
    set_external_library(ARM-Linux)
else ()
    ### Local OS 컴파일
    message("TARGET OS : LOCAL")
    set_external_library(${CMAKE_HOST_SYSTEM_NAME})
endif ()

### Make Application
add_executable(libconfig_example src/main.c)
target_link_libraries(libconfig_example -L${EXTERNAL_LIB_DIR} config)