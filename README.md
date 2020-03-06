# libconfig
C언어 외부 파일 (.cfg)에서 key, value 를 읽어 config_t 구조체 변수에 넣어서 접근할 수 있도록 해주는 라이브러리

[공식 페이지](https://hyperrealm.github.io/libconfig/)

[GitHub](https://github.com/hyperrealm/libconfig)

라이센스(license) 정보
* LGPL(GNU Lesser General Public License)
* 동적 링크 사용시 상업에 사용하는 소스 공개 의무 없음
* 정적 링크 사용시 상업에 사용하는 소스 공개 의무 <b>있음</b>
* [오픈소스SW 라이선스 LGPL 바로알기](https://openbee.kr/422)

## 설치 : Microsoft Windows
<b>MSYS2 / MinGW 사용</b>   

* 라이브러리 설치를 위한 패키지 설치 : `pacman -S isl autoconf automake-wrapper libtool make`
* MSYS2/MinGW를 사용하여 CLion 환경 구축하기 : [참조 사이트](https://github.com/JuJin1324/CLion_stater#microsoft-windows)

### 라이브러리 생성
* --host : 산출될 라이브러리가 구동될 툴체인의 prefix(gcc 앞에 붙는 prefix)
* --prefix : 산출물을 담을 디렉터리 경로(사용자 지정)
```bash
$ wget https://hyperrealm.github.io/libconfig/dist/libconfig-1.7.2.tar.gz
$ tar -xvf libconfig-1.7.2.tar.gz
$ cd libconfig-1.7.2
$ ./configure --host=x86_64-w64-mingw32 --prefix=$HOME/Documents/dev/external
$ make clean
$ make
$ make install
```

## 설치 : macOS / Ubuntu(Linux)
### 라이브러리 생성 
* --host : gcc 앞에 따로 prefix가 붙지 않음으로 사용 안함.
* --prefix : 산출물을 담을 디렉터리 경로(사용자 지정)
```bash
$ wget https://hyperrealm.github.io/libconfig/dist/libconfig-1.7.2.tar.gz
$ tar -xvf libconfig-1.7.2.tar.gz
$ cd libconfig-1.7.2
$ ./configure --prefix=$HOME/Documents/dev/external
$ make clean
$ sudo make
$ sudo make install
```

## 실행 환경(Target OS)이 arm-linux인 라이브러리 생성
ARM-Linux 컴파일용 라이브러리를 설치하기 위해서는 ARM-Linux 전용 GCC가 필요하다. 
해당 파일의 설치 및 CMake 선언에 관해서는 [참조사이트](https://github.com/JuJin1324/cmake-starter#arm-linux-toolchain-%EC%82%AC%EC%9A%A9%ED%95%98%EA%B8%B0--macos)
에서 OS에 맞는 <b>ARM-Linux Toolchain 사용하기</b>를 통해서 따라하기
 
### 라이브러리 생성 
* --prefix : 산출물을 담을 디렉터리 경로(여기서는 ~/Documents/dev/external/ARM-Linux 아래 설치)
```bash
$ wget https://hyperrealm.github.io/libconfig/dist/libconfig-1.7.2.tar.gz
$ tar -xvf libconfig-1.7.2.tar.gz
$ cd libconfig-1.7.2
$ ./autogen.sh
```
macOS에서 생성하는 경우 : `CC=arm-unknown-linux-gnueabi-gcc CXX=arm-unknown-linux-gnueabi-c++ ./configure --host=arm-unknown-linux-gnueabi --prefix=$HOME/Documents/dev/external/ARM-Linux`

Ubuntu에서 생성하는 경우 : `CC=arm-linux-gnueabi-gcc CXX=arm-linux-gnueabi-c++ ./configure --host=arm-linux --prefix=$HOME/Documents/dev/external/ARM-Linux`

Windows(MinGW)에서 생성하는 경우 : `CC=arm-linux-gnueabihf-gcc CXX=arm-linux-gnueabihf-c++ ./configure --host=arm-linux-gnueabihf --prefix=$HOME/Documents/dev/external/ARM-Linux`

```bash
$ make clean
$ sudo make
$ sudo make install
```

## CMake : 동적 라이브러리 링크 
add_executable 실행파일명 예시 : `application`   
* ${CMAKE_SOURCE_DIR} : 현재 프로젝트 디렉터리
* ${CMAKE_HOST_SYSTEM_NAME} : 현재 CMake가 동작하는 운영체제 명(예시 : Darwin, Linux, Windows), (Darwin = macOS)
* target_link_libraries()는 add_executable() 아래에 위치 시킨다.

```cmake
set(EXTERNAL_LIB_ROOT ${CMAKE_SOURCE_DIR}/external/${CMAKE_HOST_SYSTEM_NAME})
set(EXTERNAL_INCLUDE_DIR ${EXTERNAL_LIB_ROOT}/include)
set(EXTERNAL_LIB_DIR ${EXTERNAL_LIB_ROOT}/lib)

include_directories(${EXTERNAL_INCLUDE_DIR})

find_library(
            LIBCONFIG
            NAMES config
            PATHS ${EXTERNAL_LIB_DIR} NO_DEFAULT_PATH REQUIRED)

## target_link_libraries()는 add_executable() 아래에 위치 시킨다.
target_link_libraries(application ${LIBCONFIG})
```

### ARM-Linux 기기에서 동적 라이브러리 사용시 주의
external/ARM-Linux/lib 아래 3개의 파일(<b>libconfig.so, libconfig.so.11, libconfig.so.11.0.2</b>)을 
해당 기기의 `/usr/lib`로 복붙 필요함.


## CMake 정적 라이브러리 링크
<b>[주의!] libconfig 정적 라이브러리로 사용하여 개발된 상용 프로그램 배포시 소스코드 공개가 의무화됨으로 소스코드 공개가 꺼려지면 
동적 라이브러리 링크 사용을 추천</b>   

<b>[주의!] Windows에서 libconfig 정적 라이브러리 사용 불가능!</b>

add_executable 실행파일명 예시 : `application`   
* ${CMAKE_SOURCE_DIR} : 현재 프로젝트 디렉터리
* ${CMAKE_HOST_SYSTEM_NAME} : 현재 CMake가 동작하는 운영체제 명(예시 : Darwin, Linux, Windows), (Darwin = macOS)
* target_link_libraries()는 add_executable() 아래에 위치 시킨다.

```cmake
set(EXTERNAL_LIB_ROOT ${CMAKE_SOURCE_DIR}/external/${CMAKE_HOST_SYSTEM_NAME})
set(EXTERNAL_INCLUDE_DIR ${EXTERNAL_LIB_ROOT}/include)
set(EXTERNAL_LIB_DIR ${EXTERNAL_LIB_ROOT}/lib)

include_directories(${EXTERNAL_INCLUDE_DIR})

find_library(
        LIBCONFIG
        NAMES libconfig.a
        PATHS ${EXTERNAL_LIB_DIR} NO_DEFAULT_PATH REQUIRED)

## target_link_libraries()는 add_executable() 아래에 위치 시킨다.
target_link_libraries(application ${LIBCONFIG})
```

## 라이브러리 변경 시 주의 사항
CMakeLists.txt 파일에서 라이브러리 관련 변경 후 상단 메뉴바 Tools -> CMake -> <b>Reset Cache and Reload Project</b> 
및 Build -> Build Project 를 통한 재빌드 실행
