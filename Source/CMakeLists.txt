find_package(BISON)
find_package(FLEX)

FLEX_TARGET(LuaScanner LuaTokenizer.l ${CMAKE_CURRENT_BINARY_DIR}/LuaTokenizer.cpp)
BISON_TARGET(LuaParser LuaParser.y ${CMAKE_CURRENT_BINARY_DIR}/LuaParser.cpp)
ADD_FLEX_BISON_DEPENDENCY(LuaScanner LuaParser)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(Lua
	LookupTable.cpp
	LuaFloat.cpp
	LuaFunction.cpp
	LuaObject.cpp
	LuaString.cpp
	${BISON_LuaParser_OUTPUTS}
	${FLEX_LuaScanner_OUTPUTS}
)