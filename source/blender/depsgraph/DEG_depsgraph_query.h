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
 * The Original Code is Copyright (C) 2013 Blender Foundation.
 * All rights reserved.
 *
 * Original Author: Joshua Leung
 * Contributor(s): Sergey Sharybin
 *
 * ***** END GPL LICENSE BLOCK *****
 */

/** \file blender/depsgraph/DEG_depsgraph_query.h
 *  \ingroup depsgraph
 *
 * Public API for Querying and Filtering Depsgraph.
 */

#ifndef __DEG_DEPSGRAPH_QUERY_H__
#define __DEG_DEPSGRAPH_QUERY_H__

#include "DEG_depsgraph.h"

struct ID;

struct Base;
struct BLI_Iterator;
struct Depsgraph;
struct DupliObject;
struct ListBase;
struct Scene;
struct SceneLayer;

#ifdef __cplusplus
extern "C" {
#endif

/* Check if given ID type was tagged for update. */
bool DEG_id_type_tagged(struct Main *bmain, short idtype);

/* Get additional evaluation flags for the given ID. */
short DEG_get_eval_flags_for_id(struct Depsgraph *graph, struct ID *id);

/* Get scene the despgraph is created for. */
struct Scene *DEG_get_scene(struct Depsgraph *graph);

/* Get scene layer the despgraph is created for. */
struct SceneLayer *DEG_get_scene_layer(struct Depsgraph *graph);

/* Get the object as properly evaluated by depsgraph. */
struct Object *DEG_get_object(struct Depsgraph *depsgraph, struct Object *ob);

/* ************************ DAG iterators ********************* */

enum {
	DEG_OBJECT_ITER_FLAG_SET = (1 << 0),
	DEG_OBJECT_ITER_FLAG_DUPLI = (1 << 1),
};

#define DEG_OBJECT_ITER_FLAG_ALL (DEG_OBJECT_ITER_FLAG_SET | DEG_OBJECT_ITER_FLAG_DUPLI)

typedef struct DEGObjectsIteratorData {
	struct Depsgraph *graph;
	struct Scene *scene;
	struct EvaluationContext eval_ctx;

	/* TODO(sergey): Base should never be a thing coming FROM depsgraph. */
	struct Base *base;
	int base_flag;
	int flag;

	/* **** Iteration over dupli-list. *** */

	/* Object which created the dupli-list. */
	struct Object *dupli_parent;
	/* List of duplicated objects. */
	struct ListBase *dupli_list;
	/* Next duplicated object to step into. */
	struct DupliObject *dupli_object_next;
	/* Corresponds to current object: current iterator object is evaluated from
	 * this duplicated object.
	 */
	struct DupliObject *dupli_object_current;
	/* Temporary storage to report fully populated DNA to the render engine or
	 * other users of the iterator.
	 */
	struct Object temp_dupli_object;
} DEGObjectsIteratorData;

void DEG_objects_iterator_begin(struct BLI_Iterator *iter, DEGObjectsIteratorData *data);
void DEG_objects_iterator_next(struct BLI_Iterator *iter);
void DEG_objects_iterator_end(struct BLI_Iterator *iter);

/* Temporary hacky solution waiting for cow depsgraph implementation. */
#define DEG_OBJECT_ITER(graph_, instance_, flag_)                                 \
	{                                                                             \
		DEGObjectsIteratorData data_ = {                                          \
			.graph = (graph_),                                                    \
			.flag = (flag_),                                                      \
		};                                                                        \
                                                                                  \
		ITER_BEGIN(DEG_objects_iterator_begin,                                    \
		           DEG_objects_iterator_next,                                     \
		           DEG_objects_iterator_end,                                      \
		           &data_, Object *, instance_)

#define DEG_OBJECT_ITER_END                                                       \
		ITER_END                                                                  \
	}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* __DEG_DEPSGRAPH_QUERY_H__ */
