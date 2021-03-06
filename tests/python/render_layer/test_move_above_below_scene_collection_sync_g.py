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

class UnitTesting(MoveSceneCollectionSyncTesting):
    def get_reference_scene_tree_map(self):
        # original tree, no changes
        return self.get_initial_scene_tree_map()

    def test_scene_collection_move_a(self):
        """
        Test outliner operations
        """
        tree = self.setup_tree()
        self.assertFalse(tree['dog'].move_above(tree['cat']))
        self.compare_tree_maps()

    def test_scene_collection_move_b(self):
        """
        Test outliner operations
        """
        tree = self.setup_tree()
        self.assertFalse(tree['cat'].move_below(tree['dog']))
        self.compare_tree_maps()


# ############################################################
# Main - Same For All Render Layer Tests
# ############################################################

if __name__ == '__main__':
    import sys

    extra_arguments = sys.argv[sys.argv.index("--") + 1:] if "--" in sys.argv else []
    sys.argv = [__file__] + (sys.argv[sys.argv.index("--") + 2:] if "--" in sys.argv else [])

    UnitTesting._extra_arguments = extra_arguments
    unittest.main()
