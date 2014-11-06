cmake_minimum_required(VERSION 2.8)
project(mugg_game)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

if(WIN32)
    #LIBRARY DIRECTORIES
	set(GLEW_LIB 		${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/glew/lib/libglew32.dll.a)
	set(FREETYPE_LIB 	${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/freetype/lib/libfreetype.dll.a)
	set(ZLIB_LIB		${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/zlib/lib/libzlibstatic.a) #Only needed for assimp
	set(ASSIMP_LIB		${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/assimp/lib/libassimp.a)
	set(SFML_LIB 		${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/sfml/lib/libsfml-main.a
						${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/sfml/lib/libsfml-system.a
						${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/sfml/lib/libsfml-window.a
						${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/sfml/lib/libsfml-network.a
						${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/sfml/lib/libsfml-audio.a)
	set(FREEIMAGE_LIB 	${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/freeimage/lib/FreeImage.lib)

    #INCLUDE DIRECTORIES
    set(SFML_INCLUDE        ${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/sfml/include)
	set(GLEW_INCLUDE 		${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/glew/include)
	set(FREETYPE_INCLUDE 	${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/freetype/include
							${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/freetype/include/freetype2)
	set(FREEIMAGE_INCLUDE 	${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/freeimage/include)
	set(ZLIB_INCLUDE		${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/zlib/include)
	set(ASSIMP_INCLUDE		${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/assimp/include)
	set(GLM_INCLUDE 		${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/glm)

	set(EXT_HEADERS  
		${GLEW_INCLUDE}
		${GLM_INCLUDE}
		${FREEIMAGE_INCLUDE}
		${FREETYPE_INCLUDE}
	    ${SFML_INCLUDE}
		${ASSIMP_INCLUDE}
		${ZLIB_INCLUDE}
		${CMAKE_CURRENT_SOURCE_DIR}/src
    )

	set(LIBRARIES
		${GLEW_LIB}
		${FREEIMAGE_LIB}
		${FREETYPE_LIB}
        ${SFML_LIB}
		${ASSIMP_LIB}
		${ZLIB_LIB}
	)
	
	include_directories(${EXT_HEADERS})

	add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${SOURCE})

	target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
endif(WIN32)

if(UNIX)
	set(LIBRARIES
	    GLEW
	    freeimage
	    assimp
	    GL
	    GLU
        sfml-system
        sfml-window
        sfml-network
        sfml-audio
    )
	
	INCLUDE(FindPkgConfig)
	
	find_package(Freetype REQUIRED)
	
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	
	include_directories(${FREETYPE_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/headers ${CMAKE_CURRENT_SOURCE_DIR}/src)
	
	add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${SOURCE})
	
	target_link_libraries(${PROJECT_NAME} ${FREETYPE_LIBRARIES})
	target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

endif(UNIX)
