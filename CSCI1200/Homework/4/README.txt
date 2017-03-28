HOMEWORK 4: GROCERY LISTS


NAME:  Ziniu Yu


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

LMS
Google

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  6+



ORDER NOTATION:
For each request/command,

i = # of different ingredients in the kitchen
u = maximum units of a single ingredient in the kitchen
r = # of different recipes
k = maximum # of different ingredients in a single recipe
v = maximum units of single ingredient in a single recipe
a = maximum # of different ingredients added with a single ’a’ command 
w = maximum units of a single ingredient added with a single ’a’ command


command 'r' / add a recipe: O(r+k)

command 'a' / add ingredients to the kitchen: O(a*i)

command 'p' / print a recipe: O(r+k)

command 'm' / make a recipe: O(r*i)

command 'k' / print the contents of the kitchen: O(i)

command 's' / suggest recipes: O(r*i)


(extra credit) command 'd' / suggest dinner menu:



EXTRA CREDIT:
Describe your implementation of the "suggest dinner menu" option.

	I’ve thought about this option for several days and found some
	possible solutions. It’s a Knapsack problem. In order to solve
	this problem, we may use Dynamic programming which may have
	Pseudo-polynomial time issues. Or we may use NP-completeness
	algorithm. But the biggest problem is that…I have no idea for
	how to write them, maybe several lectures later. I apologize
	for my temporary ignorance.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


