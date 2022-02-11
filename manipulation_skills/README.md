# manipulation_skills #

The package contains all the launchers to test each manipulation skill. The package contains also the configuration files for each manipulation skills.

## Luanchers

- [goto.launch](https://github.com/JRL-CARI-CNR-UNIBS/manipulation_examples/blob/master/manipulation_skills/launch/goto.launch): to launch the [go_to_location_server_node](https://github.com/JRL-CARI-CNR-UNIBS/manipulation/tree/master/go_to_location/src).

- [pick.launch](https://github.com/JRL-CARI-CNR-UNIBS/manipulation_examples/blob/master/manipulation_skills/launch/pick.launch): to launch the [inbound_pick_server_node](https://github.com/JRL-CARI-CNR-UNIBS/manipulation/tree/master/inbound_pick/src).

- [place.launch](https://github.com/JRL-CARI-CNR-UNIBS/manipulation_examples/blob/master/manipulation_skills/launch/place.launch): to launch the [þoutbound_place_server_node](https://github.com/JRL-CARI-CNR-UNIBS/manipulation/tree/master/outbound_place/src).

- [skills.launch](https://github.com/JRL-CARI-CNR-UNIBS/manipulation_examples/blob/master/manipulation_skills/launch/skills.launch): to launch the three skills pick, place, goto location.

- [scene_spawner.launch](https://github.com/JRL-CARI-CNR-UNIBS/manipulation_examples/blob/master/manipulation_skills/launch/scene_spawner.launch): to launch the scene spawner.

- [test_recipe.launch](https://github.com/JRL-CARI-CNR-UNIBS/manipulation_examples/blob/master/manipulation_skills/launch/test_recipe.launch): to launch the node that test a complete recipe.


## Configuration files

- [go_to_location_server.yaml](https://github.com/JRL-CARI-CNR-UNIBS/manipulation_examples/blob/master/manipulation_skills/config/go_to_location_server.yaml): the file contains the configurations of the go_to_location_server and the description of the locations for the go_to_location skill.

- [inbound_server.yaml](https://github.com/JRL-CARI-CNR-UNIBS/manipulation_examples/blob/master/manipulation_skills/config/inbound_server.yaml): the file contains the configurations of the inbound_pick_server and the description of the locations for the pick skill.

- [object_description.yaml](https://github.com/JRL-CARI-CNR-UNIBS/manipulation_examples/blob/master/manipulation_skills/config/objects_description.yaml): the file contains the descriptions and the grasping poses of the objects to be manipulated (e.g. the L shape objects).

- [object_distribution.yaml](https://github.com/JRL-CARI-CNR-UNIBS/manipulation_examples/blob/master/manipulation_skills/config/objects_distribution.yaml): the file contains the locations of the objects to be manipulated (e.g. the L shape objects).

- [outbound_server.yaml](https://github.com/JRL-CARI-CNR-UNIBS/manipulation_examples/blob/master/manipulation_skills/config/outbound_server.yaml): the file contains the configurations of the object_place_server and the description of the locations for the place skill.

- [recipe.yaml](https://github.com/JRL-CARI-CNR-UNIBS/manipulation_examples/blob/master/manipulation_skills/config/recipe.yaml): the file contains recipe that combine several skills.

- [slot_distribution.yaml](https://github.com/JRL-CARI-CNR-UNIBS/manipulation_examples/blob/master/manipulation_skills/config/slots_distribution.yaml): the file contains the locations of the slots.

- [static_scene.yaml](https://github.com/JRL-CARI-CNR-UNIBS/manipulation_examples/blob/master/manipulation_skills/config/static_scene.yaml): the file contains the descriptions and the locations of the fixed objects in the scene (e.g. the outbound boxes).
