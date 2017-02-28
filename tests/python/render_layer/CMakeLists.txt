# ***** BEGIN GPL LICENSE BLOCK *****
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#
# Contributor(s): Jacques Beaurain, Dalai Felinto.
#
# ***** END GPL LICENSE BLOCK *****

# --env-system-scripts allows to run without the install target. 

# Use '--write-blend=/tmp/test.blend' to view output

set(TEST_SRC_DIR ${CMAKE_SOURCE_DIR}/../lib/tests)
set(TEST_OUT_DIR ${CMAKE_BINARY_DIR}/tests)

# ugh, any better way to do this on testing only?
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${TEST_OUT_DIR})

#~	if(NOT IS_DIRECTORY ${TEST_SRC_DIR})
#~		message(FATAL_ERROR "CMake test directory not found!")
#~	endif()

# all calls to blender use this
if(APPLE)
	if(${CMAKE_GENERATOR} MATCHES "Xcode")
		set(TEST_BLENDER_EXE ${EXECUTABLE_OUTPUT_PATH}/Debug/blender.app/Contents/MacOS/blender)
	else()
		set(TEST_BLENDER_EXE ${EXECUTABLE_OUTPUT_PATH}/blender.app/Contents/MacOS/blender)
	endif()
else()
	set(TEST_BLENDER_EXE ${EXECUTABLE_OUTPUT_PATH}/blender)
endif()

# for testing with valgrind prefix: valgrind --track-origins=yes --error-limit=no 
set(TEST_BLENDER_EXE ${TEST_BLENDER_EXE} --background -noaudio --factory-startup --env-system-scripts ${CMAKE_SOURCE_DIR}/release/scripts)


# ------------------------------------------------------------------------------

macro(RENDER_LAYER_TEST test_name)
	add_test(render_layer_${test_name} ${TEST_BLENDER_EXE}
		--python ${CMAKE_CURRENT_LIST_DIR}/test_${test_name}.py --
		--testdir="${TEST_SRC_DIR}/layers"
	)
endmacro()

RENDER_LAYER_TEST(scene_write_read)
RENDER_LAYER_TEST(scene_copy)
RENDER_LAYER_TEST(layer_syncinc)
RENDER_LAYER_TEST(layer_linking)
RENDER_LAYER_TEST(active_collection)
RENDER_LAYER_TEST(object_delete)
RENDER_LAYER_TEST(link)
RENDER_LAYER_TEST(operator_context)
RENDER_LAYER_TEST(object_add_cylinder)
RENDER_LAYER_TEST(object_add_empty)
RENDER_LAYER_TEST(object_add_torus)
RENDER_LAYER_TEST(object_add_no_collection_cylinder)
RENDER_LAYER_TEST(object_add_no_collection_empty)
RENDER_LAYER_TEST(object_add_no_collection_torus)
RENDER_LAYER_TEST(object_copy)
RENDER_LAYER_TEST(evaluation_visibility_a)
RENDER_LAYER_TEST(evaluation_visibility_b)