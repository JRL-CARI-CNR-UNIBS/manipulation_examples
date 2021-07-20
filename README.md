# manipulation_examples #

[![Build Status](https://travis-ci.com/JRL-CARI-CNR-UNIBS/manipulation_examples.svg?branch=master)](https://travis-ci.com/JRL-CARI-CNR-UNIBS/manipulation_examples)


A collection of examples to test the functionalities of the CNR-STIIMA [manipulation](https://github.com/JRL-CARI-CNR-UNIBS/manipulation) package.
The available ROS packages are:

- [manipulation_skills](https://github.com/JRL-CARI-CNR-UNIBS/manipulation_examples/tree/enrico-devel/manipulation_skills): the package contains all the launchers to test each manipulation skill. The package contains also the configuration files for each manipulation skills.

- [manipulation_skills_example](https://github.com/JRL-CARI-CNR-UNIBS/manipulation_examples/tree/enrico-devel/multi_skills_example): the package contains a node to test a sequence of Skills as a "recipe". The node creates clients for every skill and execute a recipe as a sequence of Actions.

- [manipulation_cell_ur5_moveit_config](https://github.com/JRL-CARI-CNR-UNIBS/manipulation_examples/tree/enrico-devel/manipulation_cell_ur5_moveit_config): the package contains the MoveIt! configuration files for the demonstration cell.

- [manipulation_ur5_cell_configurations](https://github.com/JRL-CARI-CNR-UNIBS/manipulation_examples/tree/enrico-devel/manipulation_ur5_cell_configurations): the package contains the configuration files for the demonstration cell.

- [manipulation_ur5_cell_descriptions](https://github.com/JRL-CARI-CNR-UNIBS/manipulation_examples/tree/enrico-devel/manipulation_ur5_cell_descriptions): the package contains the description of the demonstration cell.

- [manipualtion_fake_tool](https://github.com/JRL-CARI-CNR-UNIBS/manipulation_examples/tree/enrico-devel/manipulation_fake_tool): the package contains a simulation of a fake tool for the robot.


## How to launch the base example

To launch the demonstration robotic cell:

`roslaunch manipulation_ur5_cell_configurations ur5.launch`

To launch the manipulation skills servers and load the objects in the scene:

`roslaunch manipulation_skills skills.launch`

To launch the node that execute a sequence of Actions as a recipe:

`roslaunch manipulation_skills test_recipe.launch`


## Installation and ROS-Version
This framework was developed using the ROS Noetic distribution.

The software can be installed with the following [rosinstall file](manipulation_examples.rosinstall).


## Work in progress
The manipulation framework package and its examples are continuosly evolving. If you find errors or if you have some suggestions, [please let us know](https://github.com/JRL-CARI-CNR-UNIBS/manipulation_examples/issues).

## Developer Contact
**Authors:**   
- Enrico Villagrossi (enrico.villagrossi@stiima.cnr.it)  
- Manuel Beschi (manuel.beschi@unibs.it)  


_Software License Agreement (BSD License)_    
_Copyright (c) 2021, National Research Council of Italy, Institute of Industrial Technologies and Automation_    
_All rights reserved._


## Acknowledgements
The manipualtion framework is developed by CNR-STIIMA (http://www.stiima.cnr.it/)

***

![EC-H2020](documentation/Sharework.png) [ShareWork webpage](https://sharework-project.eu/)

![EC-H2020](documentation/flag_yellow.jpg)

This project has received funding from the European Union’s Horizon 2020 research and innovation programme under grant agreement No. 820807.
This website reflects only the author’s view and the European Commission is not responsible for any use that may be made of the information it contains.
