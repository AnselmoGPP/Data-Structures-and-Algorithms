CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

PROJECT( design_patterns
	 VERSION 1.0
	 DESCRIPTION "Project sample"
	 LANGUAGES CXX
)

MESSAGE(STATUS "Project: " ${PROJECT_NAME})
MESSAGE(STATUS "Project source dir: " ${PROJECT_SOURCE_DIR})

SET(CMAKE_CXX_STANDARD 17)

ADD_DEFINITIONS(
	-std=c++17
	#-O2
	#-O3
)
#ADD_COMPILE_DEFINITIONS( IMGUI_IMPL_OPENGL_LOADER_GLEW=1 )
#ADD_COMPILE_DEFINITIONS( IMGUI_IMPL_OPENGL_LOADER_GLAD=1 )

ADD_EXECUTABLE(${PROJECT_NAME}
	src/main.cpp

	src/factory_method.cpp
	src/abstract_factory.cpp
	src/builder.cpp
	src/prototype.cpp
	src/singleton.cpp
	src/object_pool.cpp

	src/adapter_class.cpp
	src/adapter_object.cpp
	src/bridge.cpp
	src/composite.cpp
	src/decorator.cpp
	src/facade.cpp
	src/flyweight.cpp
	src/proxy.cpp

	src/interpreter.cpp
	src/template_method.cpp
	src/chain_of_responsability.cpp
	src/command.cpp
	src/iterator.cpp
	src/mediator.cpp
	src/memento.cpp
	src/observer.cpp
	src/state.cpp
	src/strategy.cpp
	src/visitor.cpp
	src/null_object.cpp

	include/factory_method.hpp
	include/abstract_factory.hpp
	include/builder.hpp
	include/prototype.hpp
	include/singleton.hpp
	include/object_pool.hpp

	include/adapter_class.hpp
	include/adapter_object.hpp
	include/bridge.hpp
	include/composite.hpp
	include/decorator.hpp
	include/facade.hpp
	include/flyweight.hpp
	include/proxy.hpp

	include/interpreter.hpp
	include/template_method.hpp
	include/chain_of_responsability.hpp
	include/command.hpp
	include/iterator.hpp
	include/mediator.hpp
	include/memento.hpp
	include/observer.hpp
	include/state.hpp
	include/strategy.hpp
	include/visitor.hpp
	include/null_object.hpp

	CMakeLists.txt
)

TARGET_SOURCES(${PROJECT_NAME} PRIVATE
)

TARGET_INCLUDE_DIRECTORIES( ${PROJECT_NAME} PUBLIC
	include
)

if( UNIX )
	TARGET_LINK_LIBRARIES( ${PROJECT_NAME} 
	)
elseif( WIN32 )
	TARGET_LINK_LIBRARIES( ${PROJECT_NAME} 
	)
endif()











