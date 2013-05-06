cmake_minimum_required(VERSION 2.8)
#message("Hello CMake !")

# Name of the project, now accessible by ${PROJECT_NAME}
project(zCraft)

# We want C++2011
add_definitions(-std=c++11)

# Note : some variables concerning libraries must be defined into
# CMakeCache.txt after generation in your build folder.
# This is specific to your building environnment, so you must set them
# manually for those who don't have a predefined CMake module.

include_directories(
	"src/"
	${sfml_include_dir}
	${glew_include_dir}
)

link_directories(
	${sfml_lib_dir}
	${glew_lib_dir}
)

# Recursively finds file names and puts them into src_all.
# Note : this command seems automatic, but when we just add files to the
# filesystem without modifying CMakeLists, the generated build system will not
# be aware of this, so rerun cmake will be needed to re-genererate it
# (see CMake documentation), so it is unusued, but still here just in case.
#file(GLOB_RECURSE src_all src/*.cpp)

# GAME ENGINE ==================================================================

set(src_engine_bmfont
	src/engine/bmfont/Font.hpp
	src/engine/bmfont/Font.cpp
)

set(src_engine_core
	src/engine/core/AABB.hpp
	src/engine/core/AABB.cpp
	src/engine/core/Area3D.hpp
	src/engine/core/Area3D.cpp
	src/engine/core/Array.hpp
	src/engine/core/Color.hpp
	src/engine/core/Color.cpp
	src/engine/core/Colorf.hpp
	src/engine/core/Colorf.cpp
	src/engine/core/Exception.hpp
	src/engine/core/interpolation.hpp
	src/engine/core/interpolation.cpp
	src/engine/core/math.hpp
	src/engine/core/Matrix4.hpp
	src/engine/core/Matrix4.cpp
	src/engine/core/NonCopyable.hpp
	src/engine/core/raycast.hpp
	src/engine/core/raycast.cpp
	src/engine/core/Rect.hpp
	src/engine/core/serialization.hpp
	src/engine/core/ShiftArray3D.hpp
	src/engine/core/Singleton.hpp
	src/engine/core/stringutils.hpp
	src/engine/core/stringutils.cpp
	src/engine/core/types.hpp
	src/engine/core/Vector2.hpp
	src/engine/core/Vector3.hpp
)

set(src_engine_game
	src/engine/game/BasicGame.hpp
	src/engine/game/BasicGame.cpp
	src/engine/game/Component.hpp
	src/engine/game/Drawable.hpp
	src/engine/game/Entity.hpp
	src/engine/game/Entity.cpp
	src/engine/game/EntityRenderer.hpp
	src/engine/game/Game.cpp
	src/engine/game/Game.hpp
	src/engine/game/GameContainer.hpp
	src/engine/game/GameContainer.cpp
	src/engine/game/GameObject.hpp
	src/engine/game/GameObjectList.hpp
	src/engine/game/InternalComponentType.hpp
	src/engine/game/InternalEntityType.hpp
	src/engine/game/Scene.cpp
	src/engine/game/Scene.hpp
	src/engine/game/SFML2GameContainer.hpp
	src/engine/game/SFML2GameContainer.cpp
)

set(src_engine_gui
	src/engine/gui/Color.hpp
	src/engine/gui/Composite.hpp
	src/engine/gui/Composite.cpp
	src/engine/gui/Font.hpp
	src/engine/gui/Input.hpp
	src/engine/gui/InputListener.hpp
	src/engine/gui/InputListener.cpp
	src/engine/gui/Rect.hpp
	src/engine/gui/Renderer.hpp
	src/engine/gui/Root.hpp
	src/engine/gui/Root.cpp
	src/engine/gui/Signal.hpp
	src/engine/gui/Skin.hpp
	src/engine/gui/Texture.hpp
	src/engine/gui/Vector2.hpp
	src/engine/gui/Widget.hpp
	src/engine/gui/Widget.cpp
	src/engine/gui/WidgetType.hpp
	src/engine/gui/WidgetType.cpp
	src/engine/gui/inputs/SFMLInputAdapter.hpp
	src/engine/gui/inputs/SFMLInputAdapter.cpp
	src/engine/gui/renderers/OGLGuiRenderer.hpp
	src/engine/gui/renderers/OGLGuiRenderer.cpp
	src/engine/gui/skins/BasicSkin.hpp
	src/engine/gui/skins/BasicSkin.cpp
	src/engine/gui/widgets/CheckBox.hpp
	src/engine/gui/widgets/CheckBox.cpp
	src/engine/gui/widgets/DragZone.hpp
	src/engine/gui/widgets/ListLayout.hpp
	src/engine/gui/widgets/ListLayout.cpp
	src/engine/gui/widgets/Panel.hpp
	src/engine/gui/widgets/ProgressBar.hpp
	src/engine/gui/widgets/PushButton.hpp
	src/engine/gui/widgets/PushButton.cpp
	src/engine/gui/widgets/Slider.hpp
	src/engine/gui/widgets/Slider.cpp
	src/engine/gui/widgets/Text.hpp
	src/engine/gui/widgets/Text.cpp
	src/engine/gui/widgets/TextField.hpp
	src/engine/gui/widgets/TextField.cpp
)

set(src_engine_noise
	src/engine/noise/noise.hpp
	src/engine/noise/noise.cpp
	src/engine/noise/SimplexNoise.hpp
	src/engine/noise/SimplexNoise.cpp
)

set(src_engine_opengl
	src/engine/opengl/Camera2D.hpp
	src/engine/opengl/Camera2D.cpp
	src/engine/opengl/Camera3D.hpp
	src/engine/opengl/Camera3D.cpp
	src/engine/opengl/opengl.hpp
	src/engine/opengl/opengl.cpp
	src/engine/opengl/ShaderProgram.hpp
	src/engine/opengl/ShaderProgram.cpp
	src/engine/opengl/Vertex.hpp
	src/engine/opengl/VertexColorArray.hpp
	src/engine/opengl/VertexColorArray.cpp
)

set(src_engine_system
	src/engine/system/Mutex.hpp
	src/engine/system/Thread.hpp
	src/engine/system/Time.hpp
	src/engine/system/osdefines.hpp
	src/engine/system/files/filesystem.hpp
	src/engine/system/files/filesystem.cpp
	src/engine/system/files/Path.hpp
	src/engine/system/files/Path.cpp
	src/engine/system/files/Node.hpp
	src/engine/system/files/DirContent.hpp
)

set(src_engine_utf8
	src/engine/utf8/checked.hpp
	src/engine/utf8/core.hpp
	src/engine/utf8/unchecked.hpp
)

set(src_engine_xml
	src/engine/xml/tinyxml2.hpp
	src/engine/xml/tinyxml2.cpp
)

set(src_engine
	${src_engine_bmfont}
	${src_engine_core}
	${src_engine_game}
	${src_engine_gui}
	${src_engine_noise}
	${src_engine_opengl}
	${src_engine_system}
	${src_engine_utf8}
	${src_engine_xml}
	src/engine/config.hpp
	src/engine/utf8.hpp
)

# EXPERIMENTAL =================================================================

set(src_experimental
	src/experimental/gui/GuiTest.hpp
	src/experimental/gui/GuiTest.cpp
	src/experimental/opengl33/AxesSceneNode.hpp
	src/experimental/opengl33/AxesSceneNode.cpp
	src/experimental/opengl33/GScene.hpp
	src/experimental/opengl33/GScene.cpp
	src/experimental/opengl33/ogl33game.hpp
	src/experimental/opengl33/ogl33game.cpp
	src/experimental/opengl33/opengl3.hpp
	src/experimental/opengl33/opengl3.cpp
	src/experimental/opengl33/TransformStack.hpp
	src/experimental/opengl33/TransformStack.cpp
	src/experimental/opengl33/VertexColorArray2.hpp
	src/experimental/opengl33/VertexColorArray2.cpp
	src/experimental/tween/TweenTest.hpp
	src/experimental/tween/TweenTest.cpp
)

# VOXEL ENGINE =================================================================

set(src_zcraft
	src/zcraft/Block.hpp
	src/zcraft/Block.cpp
	src/zcraft/BlockMap.hpp
	src/zcraft/BlockMap.cpp
	src/zcraft/BlockMesh.hpp
	src/zcraft/BlockMesh.cpp
	src/zcraft/BlockMeshMap.hpp
	src/zcraft/BlockMeshMap.cpp
	src/zcraft/FreeCamera.hpp
	src/zcraft/FreeCamera.cpp
	src/zcraft/MapLoader.hpp
	src/zcraft/MapLoader.cpp
	src/zcraft/MapStreamer.hpp
	src/zcraft/MapStreamer.cpp
	src/zcraft/MapStreamThread.hpp
	src/zcraft/MapStreamThread.cpp
	src/zcraft/Voxel.hpp
	src/zcraft/Voxel.cpp
	src/zcraft/VoxelBuffer.hpp
	src/zcraft/VoxelBuffer.cpp
	src/zcraft/VoxelProperties.hpp
	src/zcraft/VoxelProperties.cpp
	src/zcraft/zcraft.hpp
	src/zcraft/zcraft.cpp
	src/zcraft/cartographer/Cartographer.hpp
	src/zcraft/cartographer/Cartographer.cpp
	src/zcraft/cartographer/Cartography.hpp
	src/zcraft/cartographer/Cartography.cpp
	src/zcraft/demos/FlatMapViewer.hpp
	src/zcraft/demos/FlatMapViewer.cpp
	src/zcraft/demos/PerspectiveMapViewer.hpp
	src/zcraft/demos/PerspectiveMapViewer.cpp
	src/zcraft/mapgen/MapGeneratorCanyons.hpp
	src/zcraft/mapgen/MapGeneratorCanyons.cpp
	src/zcraft/mapgen/MapGeneratorGrid.hpp
	src/zcraft/mapgen/MapGeneratorGrid.cpp
	src/zcraft/mapgen/MapGeneratorHeightmap.hpp
	src/zcraft/mapgen/MapGeneratorHeightmap.cpp
)

set(src_all
	${src_engine}
	${src_experimental}
	${src_zcraft}
	src/main.cpp
	src/version.hpp
)

# The executable will have the same name as the project.
# This command requires a list of source files.
add_executable(${PROJECT_NAME} ${src_all})

# Note : the order is important
target_link_libraries(
	${PROJECT_NAME}
	"opengl32"
	"glu32"
	${glew_lib_name}
	${sfml_graphics_lib_name}
	${sfml_audio_lib_name}
	${sfml_network_lib_name}
	${sfml_window_lib_name}
	${sfml_system_lib_name}
)




