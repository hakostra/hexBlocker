PROJECT("HexBlocker")
cmake_minimum_required(VERSION 2.8)
 
IF(NOT VTK_DIR)
  MESSAGE("VTK_DIR is not set it with export VTK_DIR=/path/to/vtk/build, trying default settings")
  SET(VTK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../build/VTK)
ENDIF(NOT VTK_DIR)
IF(NOT VTK_BINARY_DIR)
    FIND_PACKAGE(VTK)
    INCLUDE(${VTK_USE_FILE})
ENDIF(NOT VTK_BINARY_DIR)

# use what QVTK built with

SET(QT_MOC_EXECUTABLE ${VTK_QT_MOC_EXECUTABLE} CACHE FILEPATH "")
SET(QT_UIC_EXECUTABLE ${VTK_QT_UIC_EXECUTABLE} CACHE FILEPATH "")
SET(QT_QMAKE_EXECUTABLE ${VTK_QT_QMAKE_EXECUTABLE} CACHE FILEPATH "")
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})


# Use the include path and library for Qt that is used by VTK.
INCLUDE_DIRECTORIES(
  ${QT_INCLUDE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# Set your files and resources here  
SET(HexBlockerSrcs
    main.cpp MainWindow.cpp HexBlock.cpp HexBlocker.cpp
    HexPatch.cpp InteractorStyleVertPick.cpp
    MoveVerticesWidget.cpp CreateBlockWidget.cpp
    HexBC.cpp ToolBoxWidget.cpp
    SetBCsWidget.cpp SetBCsItem.cpp HexExporter.cpp HexEdge.cpp
    HexReader.cpp EdgePropsWidget.cpp
    TEdgeSpace.cpp GradingCalculatorDialog.cpp InteractorStyleActorPick.cpp
    )
SET(HexBlockerUI
    MainWindow.ui ToolBoxWidget.ui
    MoveVerticesWidget.ui CreateBlockWidget.ui
    SetBCsWidget.ui EdgePropsWidget.ui
    GradingCalculatorDialog.ui
    )
SET(HexBlockerHeaders
    MainWindow.h HexBlock.h HexBlocker.h HexPatch.h
    InteractorStyleVertPick.h MoveVerticesWidget.h
    CreateBlockWidget.h HexBC.h ToolBoxWidget.h
    SetBCsWidget.h SetBCsItem.h HexExporter.h HexEdge.h
    HexReader.h EdgePropsWidget.h TEdgeSpace.h
    GradingCalculatorDialog.h InteractorStyleActorPick.h
    )
SET(HexBlockerResources Icons/icons.qrc)

# The rest should just work (sure...)
QT4_WRAP_UI(UISrcs ${HexBlockerUI})
QT4_WRAP_CPP(MOCSrcs ${HexBlockerHeaders} )
QT4_ADD_RESOURCES(ResourceSrcs ${HexBlockerResources})

SOURCE_GROUP("Resources" FILES
  ${HexBlockerUI}
  ${HexBlockerResources}
  ${EXE_ICON}
)

SOURCE_GROUP("Generated" FILES
  ${UISrcs}
  ${MOCSrcs}
  ${ResourceSrcs}
  ${RCS_SOURCES}
)

ADD_DEFINITIONS(-DQT_GUI_LIBS -DQT_CORE_LIB -DQT3_SUPPORT)
SET_SOURCE_FILES_PROPERTIES(${HexBlockerSrcs} PROPERTIES
                            OBJECT_DEPENDS "${UISrcs}")

# It's nice to have the ui in the windows project file...just double click on it
# and designer comes up on that ui file :)
IF (${CMAKE_BUILD_TOOL} MATCHES "msdev")
  SET (HexBlockerSrcs ${HexBlockerSrcs} ${HexBlockerUI})
ENDIF (${CMAKE_BUILD_TOOL} MATCHES "msdev")
IF (${CMAKE_BUILD_TOOL} MATCHES "devenv")
  SET (HexBlockerSrcs ${HexBlockerSrcs} ${HexBlockerUI})
ENDIF (${CMAKE_BUILD_TOOL} MATCHES "devenv")

# Add install time link to vtk libraries
SET( CMAKE_INSTALL_RPATH "\$ORIGIN/../vtk/lib/vtk-5.10" )
ADD_EXECUTABLE( HexBlocker MACOSX_BUNDLE ${HexBlockerSrcs} ${UISrcs} ${MOCSrcs} ${ResourceSrcs})

TARGET_LINK_LIBRARIES(HexBlocker
  QVTK
  ${QT_LIBRARIES}
  vtkRendering
  vtkGraphics
  vtkIO
  vtkCommon
  vtkInfovis
  vtkViews
)


get_cmake_property(CacheVars CACHE_VARIABLES)
foreach(CacheVar ${CacheVars})
  get_property(CacheVarHelpString CACHE ${CacheVar} PROPERTY HELPSTRING)
  if(CacheVarHelpString STREQUAL "No help, variable specified on the command line.")
    get_property(CacheVarType CACHE ${CacheVar} PROPERTY TYPE)
    if(CacheVarType STREQUAL "UNINITIALIZED")
      set(CacheVarType)
    else()
      set(CacheVarType :${CacheVarType})
    endif()
    set(CMakeArgs "${CMakeArgs} -D${CacheVar}${CacheVarType}=\"${${CacheVar}}\"")
  endif()
endforeach()
message("CMakeArgs: ${CMakeArgs}")

INSTALL( TARGETS HexBlocker DESTINATION ${CMAKE_INSTALL_PREFIX} )
