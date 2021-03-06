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
# The Original Code is Copyright (C) 2016, Blender Foundation
# All rights reserved.
#
# The Original Code is: all of this file.
#
# Contributor(s): Blender Institute
#
# ***** END GPL LICENSE BLOCK *****

set(INC
	.
	intern
	modes

	../blenfont
	../blenkernel
	../blenlib
	../blentranslation
	../bmesh
	../depsgraph
	../editors/include
	../editors/space_view3d
	../gpu
	../imbuf
	../makesdna
	../makesrna
	../render/extern/include
	../render/intern/include
	../windowmanager

	../../../intern/glew-mx
	../../../intern/guardedalloc
)

set(INC_SYS
	${GLEW_INCLUDE_PATH}
)

set(SRC
	intern/draw_armature.c
	intern/draw_cache.c
	intern/draw_cache_impl_curve.c
	intern/draw_cache_impl_displist.c
	intern/draw_cache_impl_lattice.c
	intern/draw_cache_impl_mesh.c
	intern/draw_cache_impl_particles.c
	intern/draw_common.c
	intern/draw_manager.c
	intern/draw_manager_text.c
	intern/draw_view.c
	modes/edit_armature_mode.c
	modes/edit_curve_mode.c
	modes/edit_lattice_mode.c
	modes/edit_mesh_mode.c
	modes/edit_metaball_mode.c
	modes/edit_surface_mode.c
	modes/edit_text_mode.c
	modes/object_mode.c
	modes/paint_texture_mode.c
	modes/paint_vertex_mode.c
	modes/paint_weight_mode.c
	modes/particle_mode.c
	modes/pose_mode.c
	modes/sculpt_mode.c
	engines/basic/basic_engine.c
	engines/clay/clay_engine.c
	engines/eevee/eevee_data.c
	engines/eevee/eevee_engine.c
	engines/eevee/eevee_lights.c
	engines/eevee/eevee_materials.c
	engines/eevee/eevee_probes.c
	engines/eevee/eevee_effects.c
	engines/external/external_engine.c

	DRW_engine.h
	intern/DRW_render.h
	intern/draw_cache.h
	intern/draw_cache_impl.h
	intern/draw_common.h
	intern/draw_manager_text.h
	intern/draw_view.h
	modes/draw_mode_engines.h
	engines/basic/basic_engine.h
	engines/clay/clay_engine.h
	engines/eevee/eevee_engine.h
	engines/eevee/eevee_private.h
	engines/external/external_engine.h
)

if(WITH_CLAY_ENGINE)
	add_definitions(-DWITH_CLAY_ENGINE)
endif()

data_to_c_simple(engines/clay/shaders/clay_frag.glsl SRC)
data_to_c_simple(engines/clay/shaders/clay_vert.glsl SRC)
data_to_c_simple(engines/clay/shaders/clay_particle_vert.glsl SRC)
data_to_c_simple(engines/clay/shaders/clay_particle_strand_frag.glsl SRC)
data_to_c_simple(engines/clay/shaders/ssao_alchemy.glsl SRC)
data_to_c_simple(engines/clay/shaders/ssao_groundtruth.glsl SRC)

data_to_c_simple(engines/eevee/shaders/default_frag.glsl SRC)
data_to_c_simple(engines/eevee/shaders/default_world_frag.glsl SRC)
data_to_c_simple(engines/eevee/shaders/background_vert.glsl SRC)
data_to_c_simple(engines/eevee/shaders/lit_surface_frag.glsl SRC)
data_to_c_simple(engines/eevee/shaders/lit_surface_vert.glsl SRC)
data_to_c_simple(engines/eevee/shaders/effect_bloom_frag.glsl SRC)
data_to_c_simple(engines/eevee/shaders/effect_dof_vert.glsl SRC)
data_to_c_simple(engines/eevee/shaders/effect_dof_geom.glsl SRC)
data_to_c_simple(engines/eevee/shaders/effect_dof_frag.glsl SRC)
data_to_c_simple(engines/eevee/shaders/effect_motion_blur_frag.glsl SRC)
data_to_c_simple(engines/eevee/shaders/probe_filter_frag.glsl SRC)
data_to_c_simple(engines/eevee/shaders/probe_sh_frag.glsl SRC)
data_to_c_simple(engines/eevee/shaders/probe_geom.glsl SRC)
data_to_c_simple(engines/eevee/shaders/probe_vert.glsl SRC)
data_to_c_simple(engines/eevee/shaders/shadow_frag.glsl SRC)
data_to_c_simple(engines/eevee/shaders/shadow_geom.glsl SRC)
data_to_c_simple(engines/eevee/shaders/shadow_vert.glsl SRC)
data_to_c_simple(engines/eevee/shaders/shadow_store_frag.glsl SRC)
data_to_c_simple(engines/eevee/shaders/shadow_store_geom.glsl SRC)
data_to_c_simple(engines/eevee/shaders/shadow_store_vert.glsl SRC)
data_to_c_simple(engines/eevee/shaders/bsdf_lut_frag.glsl SRC)
data_to_c_simple(engines/eevee/shaders/bsdf_direct_lib.glsl SRC)
data_to_c_simple(engines/eevee/shaders/bsdf_common_lib.glsl SRC)
data_to_c_simple(engines/eevee/shaders/bsdf_sampling_lib.glsl SRC)
data_to_c_simple(engines/eevee/shaders/ltc_lib.glsl SRC)

data_to_c_simple(modes/shaders/common_globals_lib.glsl SRC)
data_to_c_simple(modes/shaders/edit_mesh_overlay_frag.glsl SRC)
data_to_c_simple(modes/shaders/edit_mesh_overlay_vert.glsl SRC)
data_to_c_simple(modes/shaders/edit_mesh_overlay_geom_tri.glsl SRC)
data_to_c_simple(modes/shaders/edit_mesh_overlay_geom_edge.glsl SRC)
data_to_c_simple(modes/shaders/edit_mesh_overlay_loosevert_vert.glsl SRC)
data_to_c_simple(modes/shaders/edit_mesh_overlay_facedot_frag.glsl SRC)
data_to_c_simple(modes/shaders/edit_mesh_overlay_facedot_vert.glsl SRC)
data_to_c_simple(modes/shaders/edit_mesh_overlay_mix_frag.glsl SRC)
data_to_c_simple(modes/shaders/edit_mesh_overlay_facefill_vert.glsl SRC)
data_to_c_simple(modes/shaders/edit_mesh_overlay_facefill_frag.glsl SRC)
data_to_c_simple(modes/shaders/edit_curve_overlay_frag.glsl SRC)
data_to_c_simple(modes/shaders/edit_curve_overlay_loosevert_vert.glsl SRC)
data_to_c_simple(modes/shaders/edit_lattice_overlay_frag.glsl SRC)
data_to_c_simple(modes/shaders/edit_lattice_overlay_loosevert_vert.glsl SRC)
data_to_c_simple(modes/shaders/edit_normals_vert.glsl SRC)
data_to_c_simple(modes/shaders/edit_normals_geom.glsl SRC)
data_to_c_simple(modes/shaders/object_empty_image_frag.glsl SRC)
data_to_c_simple(modes/shaders/object_empty_image_vert.glsl SRC)
data_to_c_simple(modes/shaders/object_outline_resolve_frag.glsl SRC)
data_to_c_simple(modes/shaders/object_outline_expand_frag.glsl SRC)
data_to_c_simple(modes/shaders/object_outline_detect_frag.glsl SRC)
data_to_c_simple(modes/shaders/object_grid_frag.glsl SRC)
data_to_c_simple(modes/shaders/object_grid_vert.glsl SRC)
data_to_c_simple(modes/shaders/object_particle_prim_vert.glsl SRC)
data_to_c_simple(modes/shaders/object_particle_prim_frag.glsl SRC)
data_to_c_simple(modes/shaders/object_particle_dot_vert.glsl SRC)
data_to_c_simple(modes/shaders/object_particle_dot_frag.glsl SRC)
data_to_c_simple(modes/shaders/paint_texture_frag.glsl SRC)
data_to_c_simple(modes/shaders/paint_texture_vert.glsl SRC)
data_to_c_simple(modes/shaders/paint_wire_frag.glsl SRC)
data_to_c_simple(modes/shaders/paint_wire_vert.glsl SRC)
data_to_c_simple(modes/shaders/paint_vert_frag.glsl SRC)

list(APPEND INC
)

blender_add_lib(bf_draw "${SRC}" "${INC}" "${INC_SYS}")
