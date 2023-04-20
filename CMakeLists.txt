cmake_minimum_required(VERSION 3.24)

project(WXTicTacToe)

set(wxWidgets_ROOT_DIR "C:/wxwidgets")
set(wxWidgets_LIB_DIR "C:/wxwidgets/lib/vc14x_x64_dll")
set(wxWidgets_DEFINITIONS WXUSINGDLL)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})

add_executable(WxTicTacToe WIN32
				"WxTicTacToe.h"
				"WxTicTacToe.cpp"
				"MainWindow.h" 
				"MainWindow.cpp" 
				"Utils.h" 
				"Utils.cpp"
				"AppIcon.rc"
)

set_target_properties(WxTicTacToe PROPERTIES CXX_STANDARD 17)

target_link_libraries(WxTicTacToe ${wxWidgets_LIBRARIES})
target_include_directories(WxTicTacToe PRIVATE ${wxWidgets_INCLUDE_DIRS})