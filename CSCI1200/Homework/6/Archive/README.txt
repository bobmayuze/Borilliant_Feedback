HOMEWORK 6: BATTLESHIP RECURSION


NAME:  Ziniu Yu



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

	Every threads on LMS. 
	Some online battleship games.
	The non-linear word search in class.

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  Like forever (50h+)



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of ships (s)? 
The total number of occupied cells (o) or open water (w)? 
The number of constraints (c)? 
The number of unknown sums (u) or unspecified ship types (t)? 
Etc. 

	Base case: solutions with no constraints and no unknown
	situations. The worst case is we have to put all ship into
	all locations with two rotations to get the result. It will
	take about [(w * h * 2) ** s] steps to find the result.
	If there are [c] constraints, it will take about [((w * h *
	2) ** s) * c] to find the correct result. Because [c = o + 
	water], we can also write [((w * h * 2) ** s) * (o + water)].
	If there are some unknown sums or unspecified ship types.
	We will take [((w * h * 2) ** s) * c * (u ** 2) * (t ** 2)]
	steps which means if you are unlucky, it will take forever
	to run :)

SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES:
# of solutions & approximate wall clock running time for different
puzzles for a single solution or all solutions.

	test case file name		||one solution	||all solutions
	=============================================================
	puzzle_sample			||0.004s	||0.003s # 2
	puzzle_sample_constraints	||0.004s	||0.003s # 1		
	puzzle1				||0.003s	||0.004s # 1
	puzzle2				||0.003s	||0.003s # 1
	puzzle3				||0.003s	||0.003s # 1
	puzzle4				||0.003s	||0.003s # 1
	puzzle5				||0.003s	||0.004s # 2
	puzzle6				||0.004s	||0.006s # 24
	puzzle6_unknowns		||0.005s	||0.020s # 24
	puzzle7				||0.003s	||0.013s # 14
	puzzle8				||0.006s	||0.560s # 2
	puzzle9				||0.013s	||1.066s # 152
	puzzle9_constraints		||0.775s	||0.857s # 1
	puzzle10			||0.004s	||1m48.306s # 3754
	puzzle10_constraints		||0.316s	||13.308s # 86

	I apologize for not showing some unknown cases, because I started
	really late and used all late days, there are some undebuggable 
	(no error message) bugs in it. It seems will take me more than
	1 hour and 30 minutes (which is I only have) to debug, so I have
	to give up some points…

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

	  _____            _ _             _ _  __  __ _            _ _   
	 |  __ \          | | |           | (_)/ _|/ _(_)          | | |  
	 | |__) |___  __ _| | |_   _    __| |_| |_| |_ _  ___ _   _| | |_ 
	 |  _  // _ \/ _` | | | | | |  / _` | |  _|  _| |/ __| | | | | __|
	 | | \ \  __/ (_| | | | |_| | | (_| | | | | | | | (__| |_| | | |_ 
	 |_|  \_\___|\__,_|_|_|\__, |  \__,_|_|_| |_| |_|\___|\__,_|_|\__|
                       	 __/ |                                     
                       	|___/                                      

	I went to Seattle for my spring break and I didn’t start the
	homework until Tuesday. I got several exams this week, these
	all really give me a hard time. I tried my best and used all
	late day I have. I even slept less than 5h a night this week.
	Because..

 	  _______ _     _       _       _____  _____ _____ 	  _ 
	 |__   __| |   (_)     (_)     |  __ \|  __ \_   _|	 | |
	    | |  | |__  _ ___   _ ___  | |__) | |__) || |  	 | |
	    | |  | '_ \| / __| | / __| |  _  /|  ___/ | |  	 | |
	    | |  | | | | \__ \ | \__ \ | | \ \| |    _| |_ 	 |_|
	    |_|  |_| |_|_|___/ |_|___/ |_|  \_\_|   |_____|   (_)
