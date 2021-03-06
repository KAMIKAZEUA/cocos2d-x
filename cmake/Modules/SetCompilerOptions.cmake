macro (SetCompilerOptions)
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DCOCOS2D_DEBUG=1")
	set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})

    # definitions for chipmunk
	if (USE_CHIPMUNK)
		add_definitions(-DCC_ENABLE_CHIPMUNK_INTEGRATION=1)
		if (IOS OR MACOSX)
			# without this chipmunk will try to use apple defined geometry types, that conflicts with cocos
            add_definitions(-DCP_USE_CGPOINTS=0)
		endif()
	else()
		add_definitions(-DCC_USE_PHYSICS=0)
	endif()

    # definitions for box2d
	if (USE_BOX2D)
		add_definitions(-DCC_ENABLE_BOX2D_INTEGRATION=1)
	else()
		add_definitions(-DCC_ENABLE_BOX2D_INTEGRATION=0)
	endif()

    # definitions for bullet
	if (USE_BULLET)
		add_definitions(-DCC_ENABLE_BULLET_INTEGRATION=1)
        add_definitions(-DCC_USE_3D_PHYSICS=1)
	else()
		add_definitions(-DCC_ENABLE_BULLET_INTEGRATION=0)
        add_definitions(-DCC_USE_3D_PHYSICS=0)
	endif()

    # definitions for recast
	if (USE_RECAST)
		add_definitions(-DCC_USE_NAVMESH=1)
	else()
		add_definitions(-DCC_USE_NAVMESH=0)
	endif()

	# Compiler options
	if(MSVC)
	  add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS
	                  -wd4251 -wd4244 -wd4334 -wd4005 -wd4820 -wd4710
	                  -wd4514 -wd4056 -wd4996 -wd4099)

	  # Use inline debug info (/Z7) format. Or internal error may occur.
	  # Errors looks like: "xmemory0(592): error C3130: Internal Compiler Error: failed to write injected code block to PDB"
	  foreach(lang C CXX)
	    string(REGEX REPLACE "/Z[iI7]" "" CMAKE_${lang}_FLAGS_DEBUG "${CMAKE_${lang}_FLAGS_DEBUG}")
	    set(CMAKE_${lang}_FLAGS_DEBUG "${CMAKE_${lang}_FLAGS_DEBUG} /Z7")
	  endforeach()

	else()
	  set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
	  set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
	  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -fPIC")
	  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-declarations -Wno-reorder -Wno-invalid-offsetof -fPIC")
	  if(CLANG AND NOT ANDROID AND NOT EMSCRIPTEN)
	    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	  endif()
	endif(MSVC)

	# Some macro definitions
	if(WINDOWS)

	  if(BUILD_SHARED_LIBS)
	    add_definitions(-D_USRDLL -D_EXPORT_DLL_ -D_USEGUIDLL -D_USREXDLL -D_USRSTUDIODLL)
	  else()
	    add_definitions(-DCC_STATIC)
	  endif()

	  add_definitions(-DCOCOS2DXWIN32_EXPORTS -D_WINDOWS -DWIN32 -D_WIN32)
	  set(PLATFORM_FOLDER win32)
	elseif(MACOSX OR APPLE)
	  add_definitions(-DCC_TARGET_OS_MAC)
	  add_definitions(-DUSE_FILE32API)
	  set(PLATFORM_FOLDER mac)
	elseif(LINUX)
	  add_definitions(-DLINUX)
	  set(PLATFORM_FOLDER linux)
	elseif(ANDROID)
	  add_definitions(-DUSE_FILE32API)
	  set(PLATFORM_FOLDER android)
	  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexceptions")
	  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsigned-char -fexceptions")
	  set(CMAKE_CXX_CREATE_SHARED_LIBRARY "${CMAKE_CXX_CREATE_SHARED_LIBRARY} -latomic")
	  
	  if(CLANG AND ANDROID_ARM_MODE STREQUAL thumb AND ANDROID_ABI STREQUAL armeabi)
            string(REPLACE "-mthumb" "-marm" CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
            string(REPLACE "-mthumb" "-marm" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
	  endif()
	  
	elseif(EMSCRIPTEN)
	  set(PLATFORM_FOLDER emcc)
	  set(EMSCRIPTEN_FLAGS "-s NO_EXIT_RUNTIME=1 -s USE_ZLIB=1 -s USE_LIBPNG=1 -s USE_FREETYPE=1 -s FULL_ES2=1 -s PRECISE_F32=1")
	  if(USE_BULLET)
	    set(EMSCRIPTEN_FLAGS "${EMSCRIPTEN_FLAGS} -s USE_BULLET=1")
	  endif(USE_BULLET)
	  set(CMAKE_C_FLAGS             "${CMAKE_C_FLAGS} ${EMSCRIPTEN_FLAGS}")
	  set(CMAKE_CXX_FLAGS           "${CMAKE_CXX_FLAGS} ${EMSCRIPTEN_FLAGS}")
	  set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS} ${EMSCRIPTEN_FLAGS}")
	  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${EMSCRIPTEN_FLAGS}")
	  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${EMSCRIPTEN_FLAGS}")
	else()
	  message( FATAL_ERROR "Unsupported platform, CMake will exit" )
	  return()
	endif()

	if(MINGW)
	  add_definitions(-DGLEW_STATIC)
	  add_definitions(-DCURL_STATICLIB)
	  add_definitions(-DAL_LIBTYPE_STATIC)
	  add_definitions(-D__SSIZE_T)

	  if(CLANG)
	    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ")
	    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
	  endif()
	endif()

endmacro (SetCompilerOptions)
