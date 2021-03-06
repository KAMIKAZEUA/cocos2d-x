#/****************************************************************************
# Copyright (c) 2015-2017 Chukong Technologies Inc.

# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

set(APP_NAME cpp_empty_test)

if(ANDROID)
  set(PLATFORM_SRC proj.android/jni/main.cpp)
  set(RES_PREFIX "/Resources")
elseif(WINDOWS)
  set(PLATFORM_SRC proj.win32/main.cpp)
  set(RES_PREFIX "")
elseif(IOS)
  set(PLATFORM_SRC
    proj.ios/main.m
    proj.ios/AppController.mm
    proj.ios/RootViewController.mm
  )

elseif(MACOSX OR APPLE)
  set(PLATFORM_SRC proj.mac/main.cpp)

  file(GLOB_RECURSE RES_FILES Resources/*)
  cocos_mark_resources(FILES ${RES_FILES} BASEDIR Resources)
  list(APPEND PLATFORM_SRC ${RES_FILES})

elseif(LINUX)
  set(PLATFORM_SRC proj.linux/main.cpp)
  set(RES_PREFIX "/Resources")
elseif(EMSCRIPTEN)
  set(PLATFORM_SRC proj.emscripten/main.cpp)
  set(RES_PREFIX "/Resources")
else()
  message( FATAL_ERROR "Unsupported platform, CMake will exit" )

endif()

include_directories(Classes)

set(SAMPLE_SRC
  ${PLATFORM_SRC}
  Classes/AppDelegate.cpp
  Classes/HelloWorldScene.cpp
)

if(ANDROID)
    add_library(${APP_NAME} SHARED ${SAMPLE_SRC})
    IF(CMAKE_BUILD_TYPE MATCHES RELEASE)
        ADD_CUSTOM_COMMAND(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} lib${APP_NAME}.so)
    ENDIF()
else()
    # add the executable
    add_executable(${APP_NAME} ${SAMPLE_SRC})
endif()

target_link_libraries(${APP_NAME} cocos2d)


if(MSVC)

  #get our resources
  add_custom_command(TARGET ${APP_NAME} PRE_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_directory
                         ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${CMAKE_CURRENT_BINARY_DIR})
  #get our dlls
  add_custom_command(TARGET ${APP_NAME} PRE_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy
                     ${CMAKE_CURRENT_SOURCE_DIR}/../../external/win32-specific/gles/prebuilt/glew32.dll 
					 ${CMAKE_CURRENT_BINARY_DIR})

  add_custom_command(TARGET ${APP_NAME} PRE_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy
                     ${CMAKE_CURRENT_SOURCE_DIR}/../../external/win32-specific/zlib/prebuilt/zlib1.dll 
					 ${CMAKE_CURRENT_BINARY_DIR}/Debug)

  #Visual Studio Defaults to wrong type
  set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
  set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")

elseif(MACOSX OR APPLE)
  set_target_properties(${APP_NAME} PROPERTIES
      MACOSX_BUNDLE 1
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
      )
elseif(ANDROID)
else()

  set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")

  set_target_properties(${APP_NAME} PROPERTIES
       RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")
       
  if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s NO_EXIT_RUNTIME=1 -s TOTAL_MEMORY=67108864 --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/Resources@/")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -s DEMANGLE_SUPPORT=1 -s ASSERTIONS=2 -s SAFE_HEAP=1")
    set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} -s DEMANGLE_SUPPORT=1 -s ASSERTIONS=2 -s SAFE_HEAP=1")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s DEMANGLE_SUPPORT=0 -s ELIMINATE_DUPLICATE_FUNCTIONS=1 --llvm-lto 1")
    set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} -s DEMANGLE_SUPPORT=0 -s ELIMINATE_DUPLICATE_FUNCTIONS=1 --llvm-lto 1")
  else()
    add_custom_command(TARGET ${APP_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:${APP_NAME}>${RES_PREFIX}
      )
  endif()
endif()

