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
* Function selection system
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

<pre>
    bin/Thoth --action solve --num-vars 1 --nodetree nodetree.0 --case-variables 10   
    bin/Thoth --action solve --num-vars 1 --nodetree nodetree.0 --case-variables -10
    bin/Thoth --action solve --num-vars 1 --nodetree nodetree.0 --case-variables 50
    bin/Thoth --action solve --num-vars 1 --nodetree nodetree.0 --case-variables 999
</pre>

You can find the real answers with sin x on a calculator. Google also has the answers!


Your program may or may not be good at solving these, but we can evolve a better program by using the extended sin test cases.

Run Thoth again, specifying these cases.  

    bin/Thoth --fitness-cases fitness_cases/testTwoSinx_20c
    
If the program scored very poorly with the extended cases, its likely to find a brand new member to fill its place, otherwise it will continue with the nodetree you have already grown. 


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
* Making the fitness case settings more verbose. ( Instead of the numbers at the top. )
* Genetic Islands -> Separating parts of the population into distinct islands so they may evolve with more diversity.
* Re-using threads to save on initialisation cost.
* Better profiling with saved structures
* A configure script
* Standardisation of string methods. There's a big mix of c & c++ styles in there.
* The test cases need a good clean up, and the recent changes to the configuration system are not covered.



Troubleshooting
===============

Program crash on launch
----------------------- 
    
* Check that you don't have any nodetrees not suitable for the chosen fitness cases. I'll be adding protection against this soon
    
    
Example Output
==============

<pre>
  _____ _           _   _     
 |_   _| |__   ___ | |_| |__  
   | | | '_ \ / _ \| __| '_ \ 
   | | | | | | (_) | |_| | | | 
   |_| |_| |_|\___/ \__|_| |_| 


   ____    
  / ___|   _     _                        
 | |     _| |_ _| |_                      
 | |___ |_   _|_   _|                     
  \____|  |_|   |_|                       
   ____                 _   _                                       
  / ___| ___ _ __   ___| |_(_) ___                                  
 | |  _ / _ \ '_ \ / _ \ __| |/ __|                                 
 | |_| |  __/ | | |  __/ |_| | (__                                  
  \____|\___|_| |_|\___|\__|_|\___|                                 
  ____                                                _             
 |  _ \ _ __ ___   __ _ _ __ __ _ _ __ ___  _ __ ___ (_)_ __   __ _ 
 | |_) | '__/ _ \ / _` | '__/ _` | '_ ` _ \| '_ ` _ \| | '_ \ / _` |
 |  __/| | | ( ) | ( | | | | ( | | | | | | | | | | | | | | | | ( | |
 |_|   |_|  \___/ \__, |_|  \__,_|_| |_| |_|_| |_| |_|_|_| |_|\__, |
                  |___/                                       |___/



 _.-/|o_0|\-._  Copyright (C) 2013-2014 Joe Butler _.-/|0_o|\-._
 Contact: joe_butler99@hotmail.com

Thoth CLI Settings:

 Action:		improve
 Nodetree:		
 Case Vars:		
 Fitness Cases:		
 Config File:		conf/config.json
 Num Vars:		0

Thoth Settings - (JSON & Defaults):

 FUNCTION_SET:			Basic+
 POPULATION:			8000
 KEEP_TOP_PERCENT:		25
 NODE_WEIGHT:			0.05
 GENERATIONS:			20
 INITIAL_MAX_DEPTH:		3
 USE_CUT_SCORING:		true
 EXIT_SCORE:			0
 SAVE_EVERY:			2
 SAVE_TOTAL:			5
 SAVE_AFTER_EACH_OPTIMISE:	true
 LOAD_SAVED:			true
 LOAD_TOTAL:			5
 SHOW_GUESSES:			true
 GUESSES_FILE:			program_guesses
 GUESSES_EVERY:			5
 OPTIMISE_CUTTER_EVERY:		20
 OPTIMISE_TERMINALS_EVERY:	40
 OPTIMISE_FUNCTIONS_EVERY:	30
 ITERATE_CUTTER:		false
 ITERATE_TERMINALS:		false
 ITERATE_FUNCTIONS:		false
 MUTATE_NODE_PERCENT:		5
 MUTATE_TREE_PERCENT:		30
 CUT_TREE_PERCENT:		25
 CROSSOVER_PERCENT:		30
 MUTATE_TREE_MAX_DEPTH:		2
 CROSSOVER_NEW_ROOT_PERCENT:	10
 SHOW_HEADINGS_EVERY:		30
 FITNESS_CASE_FILE:		fitness_cases/large_test_case

Fitness Case settings: - (fitness_cases/large_test_case) 

 TOTAL_CASES:			3000
 TERMINALS:			274
 NUM_VARS:			274
 NUM_CONSTS:			0
 CONST_LOWER:			0
 CONST_UPPER:			0
 TARGET_SCORE:			0
 SCALING_ENABLED:		true
 SCALING_LOWER:			0.5
 SCALING_UPPER:			1.5


Time      Gen     Pop     BestScore     CreatedBy   Tree Size   Cut Score     Total Cut   

16:48:07  1       8000    140494.964747 grow        15          258090.630104 0           
16:48:07  2       8000    140336.240219 Cut Tree    14          194084.507276 2067        
16:48:07  3       8000    140080.773347 Mut Tree    21          170583.448970 2633        
16:48:08  4       8000    140080.773347 Mut Tree    21          149147.789604 3306        
16:48:08  5       8000    139782.846192 Crossover   21          143219.319883 3304        
16:48:09  6       8000    139782.846192 Crossover   21          142345.211675 3376        
16:48:09  7       8000    139523.680732 Mut Tree    32          140919.889513 3180        
16:48:10  8       8000    139523.680732 Mut Tree    32          140414.814174 3134        
16:48:10  9       8000    139483.000249 Mut Node    24          140337.109547 3453        
16:48:11  10      8000    139433.158099 Crossover   38          140293.078029 3720        
16:48:11  11      8000    139245.459985 Crossover   46          140113.204735 3505        
16:48:12  12      8000    138834.090247 Crossover   24          139911.288064 3378        
16:48:12  13      8000    138710.633354 Cut Tree    20          139611.539001 3095        
16:48:13  14      8000    138707.350113 Crossover   20          139528.621386 2870        
16:48:14  15      8000    138640.546008 Cut Tree    71          139459.273042 2981        
16:48:15  16      8000    138535.787187 Mut Tree    35          139286.785688 3264        
16:48:16  17      8000    138106.602372 Mut Tree    78          139099.881641 3286        
16:48:16  18      8000    137888.567332 Crossover   73          138792.597824 3039        
16:48:17  19      8000    137888.567332 Crossover   73          138720.866829 2988        
16:48:18  20      8000    137888.567332 Crossover   73          138679.616891 3041        

Starting Branch Cutter - Tree size 73 - Started at: 16:48:18
Position  Was Func Now Term Old Score   New Score  
7         7        206      137888.567332 137888.467332
11        2        138      137888.467332 137888.267332
20        6        139      137888.267332 137452.845857
21        7        212      137452.845857 137289.615763
24        5        138      137289.615763 137270.102261
25        1        222      137270.102261 137256.593467
27        6        222      137256.593467 137214.110390
Finished Branch Cutter - Tree size 29

</pre>
