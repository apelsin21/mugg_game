set(SOURCE
	${SOURCE}

	#Core	
	${CMAKE_CURRENT_SOURCE_DIR}/core/contentmanager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/engine.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/fileutils.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/keyboard.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/mouse.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/window.cpp

	#Graphics
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/color.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/mesh.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/shader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/shaderprogram.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/texture.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/vertexarray.cpp
	
	#GUI
	${CMAKE_CURRENT_SOURCE_DIR}/gui/font.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gui/guimanager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gui/guiobject.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gui/sprite.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gui/spritebatch.cpp

	#Scene
	${CMAKE_CURRENT_SOURCE_DIR}/scene/scenemanager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/scene/scenenode.cpp

   	PARENT_SCOPE
)
set(HEADERS
   	${HEADERS}
	
	#Core
	${CMAKE_CURRENT_SOURCE_DIR}/core/contentmanager.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/engine.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/fileutils.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/keyboard.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/mouse.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/window.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/logger.hpp
	
	#Graphics
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/color.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/mesh.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/shader.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/shaderprogram.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/texture.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/vertexarray.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/graphicsdefs.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/globject.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/camera.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/textureatlas.hpp
	
	#GUI
	${CMAKE_CURRENT_SOURCE_DIR}/gui/font.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/gui/guimanager.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/gui/guiobject.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/gui/sprite.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/gui/spritebatch.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/gui/glyph.hpp
	
	#Scene
	${CMAKE_CURRENT_SOURCE_DIR}/scene/scenemanager.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/scene/scenenode.hpp
   	
	PARENT_SCOPE
)
