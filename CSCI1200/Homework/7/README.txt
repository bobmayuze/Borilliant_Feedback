HOMEWORK 7: MINIBLAST


NAME:  Ziniu Yu


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

	This one is pretty easy, I only read the lecture note and several
	threads about input and output on LMS.

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  2h



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the map data structure require (order notation for memory use)?

	First, we need to store the genome into a string and this will
	take L memories. Then we need to store all the kmers and their
	locations into a map, and it will take at most L * k memories
	(the case that all kmers are different). Then we need to store
	the query into a class DNA and this will cost q memories. And
	it will take p memories for locations where the key is found.
	Added all together and the program will take about (L * (k + 1)
	+ p + q) memories when we use map.

What is the order notation for performance (running time) of each of
the commands?

	Input command		|MAP	|VECTOR
	=============================================================
	input_small.txt		|0.019s	|0.949s
	input_medium.txt	|0.047s	|0.103s
	input_large.txt		|0.107s	|2.318s
	input_larger.txt	|0.783s	|20min23.705s(I almost give up)

EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

	
Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.

	My program takes an optional third command “vector” to use
	vector instead of map.
	
	The running time table is merged with the map one. The vector
	will basically take the same memories as map, but it the find
	function is O(N) instead of O(logN) and for the larger file.
	When we build the index, it will consume a long time to loop
	through the vector to find if it has already exists. And the
	same situation happens when we want to find the match genome,
	it will first loop through the vector to find the index, and
	then compare the following alphabet.

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

	Enjoy the life!
