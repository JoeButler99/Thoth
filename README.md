Thoth
=====

Thoth is a C++ genetic programming system. It was created to find patterns and make predictions from large quantities of real numbers.
Thoth is highly configurable and has several available methods for creating and combining members, population size, optimisation and bloat.

It can save and load its results and has an inbuilt graphing system for displaying the program structure and its performance. Once saved, population members can be used to solve new cases.
See the 'Tutorial' and 'Graphs and visualisation' sections for more information


Features
========

* Threaded with OMP
* Optimisation loops
* Constant generation, load and save
* Population and Bloat control systems
* Reverse Polish Notation solving loop ( Instead of tree recursion )
* Graphing of results with matplotlib
* Unit testing and a basic profiler
* Highly configurable


License
=======

Thoth is licensed under GPL 2.0. 
Please contact me if this is not suitable for your purpose.


Contact
=======

I'm happy to receive any and all feedback, please contact me via: Joe_butler99@hotmail.com 


Dependencies
============

Thoth requires at least the following to run on an Ubuntu system, there may be more i've missed. Please let me know to include them if you find any.

Ubuntu
------

    # Main Binary
    sudo apt-get install make g++ libboost-random-dev libcppunit-dev 
    # Graphing Tools (Not required for main functionality)
    sudo apt-get install python-pydot python-matplotlib python-pip python-dev imagemagick python-imaging
    sudo pip install PIL


Red Hat
-------

    # Main Binary
    yum install boost-devel cppunit-devel make gcc-c++
    # Graphing Tools
    yum install pydot python-matplotlib python-pip python-devel ImageMagick python-imaging
    pip install PIL



For other Linux distributions check your package manager, these should be pretty common packages. I'll add instructions for other distributions as I find time to test. (Feel free to help out here)
The same requirements 


Installation
============

Checkout the project from github and cd into the directory. Once you have satisfied the dependencies, you should be able to build all the binaries with:

    make clean Thoth
    make test
    make profiler

You can change the flags by un-commenting CCFLAGS settings of your choice in the Makefile

Currently all binaries should be accessed from the root directory, that is - once compiled run with

    bin/Thoth
    bin/test_cases
    bin/profiler <num_reps>
    bin/Thoth -h # Displays help



Configuration
=============

The main configuration has recently moved into a JSON structure. These where previously held in globals which were be compiled into the program. You are now able to edit the values, but there is little checking in place to make sure the values are suitable. ( More checking is planned in the future.)
The default file loaded is "conf/config.json". This can be overridden with the CLI argument --config-file "your-config-filename".

Example:

    bin/Thoth --config-file conf/myconfig.json --fitness-cases fitness_cases/gp_test



Tutorial
========

Make sure you've compiled successfully first. 
Thoths going to run very fast with these settings - You can slow it down a bit by compiling with the debug settings. 

* Using a text editor, look at the conf/config.json file.
 * check that the FITNESS_CASE_FILE is "fitness_cases/testSinx_20c"
 * check that the POPULATION is set to 1000
 * check that the NODE_WEIGHT equals 0.5 - Its probably smaller, but we'll to examine changing this.
 * check that the GENERATIONS number is small, something in the range 40-100 is fine

* Now run Thoth through a couple of times

    bin/Thoth


After a couple of loops you will notice this 'gets stuck'. It also kept a small Tree size, so lets look at what it produced


    cat nodetree.0                        # View the raw nodetree structure
    cat program_guesses                   # View the targets and results
    
    bin/graphtool.py -a nodetreeGraphviz  # Draw the nodetree with Graphviz
    bin/graphtool.py -a plotAllLines      # Plot the targets and results lines
    bin/graphtool.py -a  depthBarChart    # View the programs nodes per depth



* Now using the editor again, lets 'loosen' the node weight in conf/config.json so it may grow more freely
 * check that the NODE_WEIGHT equals 0.0005
 * Now run Thoth through a couple of times  "bin/Thoth"
 * If you now repeat the graphing and output steps above, you should see that the program has grown considerably and is much better at solving
 * Now is a good time to play with the settings and run it through some more
 
 
 Making a prediction outside of the test cases
 
 * Thoth can now use the generated structure to make guesses outside of the test case range. Try the following to see how it scores

    bin/Thoth --action solve --num-vars 1 --nodetree nodetree.0 --case-variables 10
    bin/Thoth --action solve --num-vars 1 --nodetree nodetree.0 --case-variables -10
    bin/Thoth --action solve --num-vars 1 --nodetree nodetree.0 --case-variables 50
    bin/Thoth --action solve --num-vars 1 --nodetree nodetree.0 --case-variables 999

You can find the real answers with sin x on a calculator. Google also has the answers!


Test Cases
==========

Thoth comes with unit testing tools. You can run these from the root directory with

    make clean test && bin/test_cases



Profiler
========

Thoth has a crude profiler which you can run with

    make clean profiler && bin/profiler 50


Depending on how many repetitions you specify, this may take a long time. Due to the very random nature of genetic programming. Profiling should be run through a few times before making decisions based on its outcome.


Graphs and visualisation
========================

Features
-------------
* GraphViz drawings of a nodetree
* Target and result line charts
* Function & Terminal use bar charts
* Node depth bar charts


Examples
--------

Before you can graph anything, you'll need to run Thoth to generate some nodetrees and guesses. See the tutorial for examples.

    bin/graphtool.py -h                       # Usage
    bin/graphtool.py -a plotResultsLine       # Plot the programs results
    bin/graphtool.py -a plotTargetsLine       # Plot the targets from the fitness cases
    bin/graphtool.py -a plotAllLines          # Plot the results against the targets
    
    bin/graphtool.py -a plotResultsPoints     # Plot the results using points
    bin/graphtool.py -a plotTargetsPoints     # Plot the targets using points
    bin/graphtool.py -a plotAllPoints         # Plot the points for targets and results
    
    bin/graphtool.py -a functionsBarChart     # Plot a bar chart of function usage
    bin/graphtool.py -a terminalsBarChart     # Plot a bar chart of terminal usage
    bin/graphtool.py -a depthBarChart         # Plot a bar chart of the number of nodes at each depth
    
    bin/graphtool.py -a nodetreeGraphviz	  # Draw the nodetrees structure with GraphViz



Planned Improvements
====================

* Constant optimisation -> Its something I'd like to have in place very soon
* Dynamic selection of functions. Probably the feature I'd like to see most, I'm currently unsure how to setup this up without compromising on speed.
* Making the fitness case settings more verbose. ( Instead of the numbers at the top. )
* Genetic Islands -> Separating parts of the population into distinct islands so they may evolve with more diversity.
* Re-using threads to save on initialisation cost.
* Better profiling with saved structures
* A configure script
* Standardisation of string methods. There's a big mix of c & c++ styles in there.
* The test cases need a good clean up, and the recent changes to the config system are not covered.



Troubleshooting
===============

Program crash on launch
----------------------- 
    
* Check that you don't have any nodetrees not suitable for these fitness cases
    
    
    