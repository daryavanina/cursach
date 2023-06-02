cmake_minimum_required (VERSION 3.8)
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
project ("coursework")

add_library(coursework coursework.cpp coursework.hpp)

set_property(TARGET coursework PROPERTY CXX_STANDARD 20)

target_include_directories(coursework PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS coursework)

add_executable (test_app "console.cpp")
target_link_libraries(test_app coursework)
