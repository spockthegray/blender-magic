# ############################################################
# Importing - Same For All Render Layer Tests
# ############################################################

import unittest
import os
import sys

from render_layer_common import *


# ############################################################
# Testing
# ############################################################

class UnitTesting(MoveLayerCollectionTesting):
    def get_reference_scene_tree_map(self):
        reference_tree_map = [
                ['A', [
                    ['i', None],
                    ['ii', None],
                    ['iii', None],
                    ]],
                ['B', None],
                ['C', [
                    ['1', None],
                    ['2', None],
                    ['3', [
                        ['cat', None],
                        ['dog', None],
                        ]],
                    ]],
                ]
        return reference_tree_map

    def get_reference_layers_tree_map(self):
        # original tree, no changes
        return self.get_initial_layers_tree_map()

    def test_layer_collection_move_a(self):
        """
        Test outliner operations
        """
        self.setup_tree()
        self.assertTrue(self.move_above('Layer 2.C.3.cat', 'Layer 2.3.dog'))
        self.compare_tree_maps()

    def test_layer_collection_move_b(self):
        """
        Test outliner operations
        """
        self.setup_tree()

        # collection that will be moved
        collection_original = self.parse_move('Layer 2.C.3.cat')
        collection_original.hide = False
        collection_original.hide_select = True

        # collection that will disappear
        collection_old = self.parse_move('Layer 2.3.cat')
        collection_old.hide = True
        collection_old.hide_select = False

        # move
        self.assertTrue(self.move_above('Layer 2.C.3.cat', 'Layer 2.3.dog'))
        self.compare_tree_maps()

        # we expect the settings to be carried along from the
        # original layer collection
        collection_new = self.parse_move('Layer 2.3.cat')
        self.assertEqual(collection_new.hide, False)
        self.assertEqual(collection_new.hide_select, True)


# ############################################################
# Main - Same For All Render Layer Tests
# ############################################################

if __name__ == '__main__':
    import sys

    extra_arguments = sys.argv[sys.argv.index("--") + 1:] if "--" in sys.argv else []
    sys.argv = [__file__] + (sys.argv[sys.argv.index("--") + 2:] if "--" in sys.argv else [])

    UnitTesting._extra_arguments = extra_arguments
    unittest.main()
