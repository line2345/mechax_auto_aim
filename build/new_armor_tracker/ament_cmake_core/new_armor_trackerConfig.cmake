# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_new_armor_tracker_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED new_armor_tracker_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(new_armor_tracker_FOUND FALSE)
  elseif(NOT new_armor_tracker_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(new_armor_tracker_FOUND FALSE)
  endif()
  return()
endif()
set(_new_armor_tracker_CONFIG_INCLUDED TRUE)

# output package information
if(NOT new_armor_tracker_FIND_QUIETLY)
  message(STATUS "Found new_armor_tracker: 0.1.0 (${new_armor_tracker_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'new_armor_tracker' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${new_armor_tracker_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(new_armor_tracker_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "ament_cmake_export_dependencies-extras.cmake;ament_cmake_export_include_directories-extras.cmake;ament_cmake_export_libraries-extras.cmake")
foreach(_extra ${_extras})
  include("${new_armor_tracker_DIR}/${_extra}")
endforeach()
