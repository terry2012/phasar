file(GLOB_RECURSE UTILS_SRC *.h *.cpp)

if(PHASAR_ENABLE_PAMM STREQUAL "Off" AND NOT PHASAR_BUILD_UNITTESTS)
  message("Not compiling PAMM.cpp since PAMM and Unittests are disabled.")
  get_filename_component(pamm_src PAMM.cpp ABSOLUTE)
  list(REMOVE_ITEM UTILS_SRC ${pamm_src})
endif()

set(PHASAR_LINK_LIBS
  phasar_config
)

set(LLVM_LINK_COMPONENTS
  Core
  Support
  BitWriter
)


if(BUILD_SHARED_LIBS)
  add_phasar_library(phasar_utils
    SHARED
    ${UTILS_SRC}
  )
else()
  add_phasar_library(phasar_utils
    STATIC
    ${UTILS_SRC}
  )
endif()

find_package(Boost COMPONENTS log REQUIRED)
target_link_libraries(phasar_utils
  LINK_PUBLIC
  ${Boost_LIBRARIES}
  ${CMAKE_DL_LIBS}
)

set_target_properties(phasar_utils
  PROPERTIES
  LINKER_LANGUAGE CXX
  PREFIX "lib"
)
