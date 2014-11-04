cmake_minimum_required(VERSION 2.8)
project(mugg_game)

if(WIN32)
    #LIBRARY DIRECTORIES
	set(FREETYPE_LIB 	${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/freetype/lib/libfreetype.dll.a)
	set(GLEW_LIB 		${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/glew/lib/libglew32s.a)
	set(ASSIMP_LIB		${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/assimp/lib/assimp.lib)
	set(SFML_LIB 		${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/sfml/lib/libsfml-main.a
						${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/sfml/lib/libsfml-system-s.a
						${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/sfml/lib/libsfml-window-s.a
						${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/sfml/lib/libsfml-network-s.a
						${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/sfml/lib/libsfml-audio-s.a)

	set(FREEIMAGE_LIB 	${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/freeimage/lib/FreeImage.lib)

    #INCLUDE DIRECTORIES
    set(SFML_INCLUDE        ${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/sfml/include)
	set(GLEW_INCLUDE 		${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/glew/include)
	set(FREETYPE_INCLUDE 	${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/freetype/include)
	set(FREEIMAGE_INCLUDE 	${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/freeimage/include)
	set(GLM_INCLUDE 		${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/glm)
	
	file(GLOB GLB_SRC 
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.cpp
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/*.cpp
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/*.cpp
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/net/*.cpp
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/scene/*.cpp
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/audio/*.cpp
	)

	file(GLOB GLB_HEADERS
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.hpp
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/*.hpp
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/*.hpp
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/net/*.hpp
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/scene/*.hpp
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/audio/*.hpp
	)

	set(EXT_HEADERS  
		${GLEW_INCLUDE}
		${GLM_INCLUDE}
		${FREEIMAGE_INCLUDE}
		${FREETYPE_INCLUDE}
	    ${SFML_INCLUDE}
    )

	set(LIBRARIES
		${GLEW_LIB}
		${FREEIMAGE_LIB}
		${FREETYPE_LIB}
        ${SFML_LIB}
	)

	include_directories(${EXT_HEADERS})

	add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${GLB_SRC} ${GLB_HEADERS})

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
	
	set(CMAKE_CXX_FLAGS " -std=c++11")
	
	include_directories(${FREETYPE_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/headers ${CMAKE_CURRENT_SOURCE_DIR}/src)
	
	file(GLOB SOURCES
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.cpp
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/*.cpp
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/*.cpp
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/net/*.cpp
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/scene/*.cpp
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/audio/*.cpp
	)
	
	file(GLOB HEADERS
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.hpp
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/*.hpp
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/*.hpp
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/net/*.hpp
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/scene/*.hpp
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/audio/*.hpp
    )
	
	add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${SOURCES} ${HEADERS})
	
	target_link_libraries(${PROJECT_NAME} ${FREETYPE_LIBRARIES})
	target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

endif(UNIX)
