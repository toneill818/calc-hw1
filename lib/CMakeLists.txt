add_library (lib ast.cpp parser.cpp evaluate.cpp postfix.cpp sexpr.cpp)
target_include_directories (lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})