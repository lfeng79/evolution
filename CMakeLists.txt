cmake_minimum_required( VERSION 2.8.10 )

project( Evolution )
#find_package( Qt4 REQUIRED QtCore )
#include( ${QT_USE_FILE} )

set( Evolution_SOURCES
	INode.h
	Nodes.h
	Nodes.cpp
	Variant.h
	Variant.cpp
	main.cpp
)

add_executable( Evolution ${Evolution_SOURCES} )

#target_link_libraries( Evolution
#	${QT_LIBRARIES}
#)

#set_target_properties( Evolution PROPERTIES
#	VS_SCC_PROJECTNAME "SAK" VS_SCC_LOCALPATH "SAK" VS_SCC_PROVIDER "SAK" VS_SCC_AUXPATH "SAK"
#)
