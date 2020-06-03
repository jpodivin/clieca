# clieca 
## Command Line Elementary Cellular Automata
Elementary cellular automata for your command line

Elementary cellular automata are one dimensional, binary cellular automata where next state of each cell 
depends only on its current state and on a state of its two closest neighbors.

As such it is a nice fit for traditional CLI since it too operates in one-dimensional lines. 
Sadly, I couldn't find one that would fit my needs, so I made it.

# How to compile it?

Since there is only one file, the compilation is simply matter of running:

		gcc main.c

in the cliautomata folder. 
One should customize the result using gcc options, at very least name of the compiled binary might be a good idea. Calling a.out isn't exactly convenient.

Those who are not used to bash, which is unlikely since this is cli based program, might want to use included Visual Studio projects, which should run with any version of VS2017.

# How to use it?

Usage is trivial, for the sake of demonstration the compiled programs name is clieca, but it can be anything else you need/want.

		clieca rulenumber 

-s size													sets the size of the automaton, between 0 and 200000 if you need more you have to edit 'WORLD_SIZE' in                                     main.c, default size is 200000

-r															sets random initial state, otherwise only one cell is set to 1 and all others to zero

-t runtime												limits number of generations to runtime and prints only last state on the screen															
Please note that the rulenumber must be between 0 and 255. The program will just print an error message otherwise. 

The standard output of the program is series of lines, consisting of stars '*' and spaces ' ' representing ones and zeros.
The output can and should be piped, because the program doesn't allow for limited runtime, yet. 
I would recommend 'head' command, which you can find in almost all Linux distributions and other Unix-likes.

For example: clieca 30 -s 100 | head -n 20
Gives us:

                  																*
																									
                                                 ***
																								 
                                                **  *
																								
                                               ** ****
																							 
                                              **  *   *
																							
                                             ** **** ***
																						 
                                            **  *    *  *
																						
                                           ** ****  ******
																					 
                                          **  *   ***     *
																					
                                         ** **** **  *   ***
																				 
                                        **  *    * **** **  *
																				
                                       ** ****  ** *    * ****
																			 
                                      **  *   ***  **  ** *   *
																			
                                     ** **** **  *** ***  ** ***
																		 
                                    **  *    * ***   *  ***  *  *
																		
                                   ** ****  ** *  * *****  *******
																	 
                                  **  *   ***  **** *    ***      *
																	
                                 ** **** **  ***    **  **  *    ***
																 
                                **  *    * ***  *  ** *** ****  **  *
																
                               ** ****  ** *  ******  *   *   *** ****



With the time specified, the output is only last state of the automaton. Again composed of stars '*' and spaces ' '. 

Following command: clieca 30 -s 100 -t 7
Provides this result:

                                          **  *   ***     *

This output can be easily piped to other programs such as awk in this example.

clieca 30 -s 100 -t 7 | awk -F"*" '{print NF-1}'

Giving us: 

		7
		

# How does it work?
The implementation is trivial and depends only on two header files and standard utilities found on any sensible machine.

I tried to make the code readable, but alas I probably failed. Thankfully modern IDEs and even humble vim can do wonders for you. 
Don't hesitate to use them. That being said, I am going to rewrite the code to meet at least basic standards. 
But I have a rather lot of work to do on other projects.

However, pretty much all functions are self-explanatory, if you have problems with understanding them you might want to try:

1. Learning basics of C
2. Going to https://en.wikipedia.org/wiki/Elementary_cellular_automaton 

# Ok, but how does it work?

The rules are implemented as arrays of chars 'ruleset', which themselves are binary form of integer representing the rule in Wolframs naming system.

The 'neighborhoodDetection' function returns char representing number state of cells in the neighborhood. A value between 0 and 7.

This value serves as an index of the element from ruleset array, the chosen element represents new state of the cell.

After determining new state of all cells the values are copied from 'tempState' array to 'state' array. 
Values in the 'state' array are printed on screen as series of stars '*' and spaces ' '.

And the process repeats. Please note that only area determined by the '-s' size parameter is affected and displayed.
The rest remains unchanged. 

The edges of the "world" grid are connected to each other. 
Therefore element 'state[size]', where 'size' is the size of automaton, is technically 'state[0]'.

This can and does lead anomalous behavior along the world "edges", you should therefore choose such size of automaton where it isn't an issue.
Or just take it into account in your work. 
Please note that the 'WORLD_SIZE' define can be modified before compilation to allow for worlds far larger than default 200000.

Obviously you should take memory requirements into account when choosing the world size.

Please note that the code might be messy and or inefficient, the result of rather hasty work on my part. 
There are at least two major inefficiencies I know of. I will fix them at a later date when I don't have so much on my plate.
