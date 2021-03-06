/*
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * Contributor(s): none yet.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

/** \file blender/windowmanager/manipulators/intern/wm_manipulator_intern.h
 *  \ingroup wm
 */


#ifndef __WM_MANIPULATOR_INTERN_H__
#define __WM_MANIPULATOR_INTERN_H__

struct wmKeyConfig;
struct wmManipulatorMap;
struct ManipulatorGeomInfo;
struct GHashIterator;

#include "wm_manipulator_fn.h"

/* -------------------------------------------------------------------- */
/* wmManipulator */

bool wm_manipulator_deselect(struct wmManipulatorMap *mmap, struct wmManipulator *manipulator);
bool wm_manipulator_select(bContext *C, struct wmManipulatorMap *mmap, struct wmManipulator *manipulator);

void wm_manipulator_calculate_scale(struct wmManipulator *manipulator, const bContext *C);
void wm_manipulator_update(struct wmManipulator *manipulator, const bContext *C, const bool refresh_map);
bool wm_manipulator_is_visible(struct wmManipulator *manipulator);

/* -------------------------------------------------------------------- */
/* wmManipulatorGroup */

enum {
	TWEAK_MODAL_CANCEL = 1,
	TWEAK_MODAL_CONFIRM,
	TWEAK_MODAL_PRECISION_ON,
	TWEAK_MODAL_PRECISION_OFF,
};

struct wmManipulatorGroup *wm_manipulatorgroup_new_from_type(
        struct wmManipulatorMap *mmap, struct wmManipulatorGroupType *mgrouptype);
void wm_manipulatorgroup_free(bContext *C, struct wmManipulatorGroup *mgroup);
void wm_manipulatorgroup_manipulator_register(struct wmManipulatorGroup *mgroup, struct wmManipulator *manipulator);
struct wmManipulator *wm_manipulatorgroup_find_intersected_mainpulator(
        const struct wmManipulatorGroup *mgroup, struct bContext *C, const struct wmEvent *event,
        unsigned char *part);
void wm_manipulatorgroup_intersectable_manipulators_to_list(
        const struct wmManipulatorGroup *mgroup, struct ListBase *listbase);
void wm_manipulatorgroup_ensure_initialized(struct wmManipulatorGroup *mgroup, const struct bContext *C);
bool wm_manipulatorgroup_is_visible(const struct wmManipulatorGroup *mgroup, const struct bContext *C);
bool wm_manipulatorgroup_is_visible_in_drawstep(const struct wmManipulatorGroup *mgroup, const int drawstep);

void wm_manipulatorgrouptype_keymap_init(struct wmManipulatorGroupType *mgrouptype, struct wmKeyConfig *keyconf);


/* -------------------------------------------------------------------- */
/* wmManipulatorMap */

struct wmManipulatorMap {
	struct wmManipulatorMap *next, *prev;

	struct wmManipulatorMapType *type;
	ListBase manipulator_groups;

	char update_flag; /* private, update tagging */

	/**
	 * \brief Manipulator map runtime context
	 *
	 * Contains information about this manipulator-map. Currently
	 * highlighted manipulator, currently selected manipulators, ...
	 */
	struct {
		/* we redraw the manipulator-map when this changes */
		struct wmManipulator *highlighted_manipulator;
		/* user has clicked this manipulator and it gets all input */
		struct wmManipulator *active_manipulator;
		/* array for all selected manipulators
		 * TODO  check on using BLI_array */
		struct wmManipulator **selected_manipulator;
		int tot_selected;
	} mmap_context;
};

/**
 * This is a container for all manipulator types that can be instantiated in a region.
 * (similar to dropboxes).
 *
 * \note There is only ever one of these for every (area, region) combination.
 */
struct wmManipulatorMapType {
	struct wmManipulatorMapType *next, *prev;
	char idname[64];
	short spaceid, regionid;
	/* types of manipulator-groups for this manipulator-map type */
	ListBase manipulator_grouptypes;
};

void wm_manipulatormap_selected_delete(struct wmManipulatorMap *mmap);
bool wm_manipulatormap_deselect_all(struct wmManipulatorMap *mmap, struct wmManipulator ***sel);

#endif