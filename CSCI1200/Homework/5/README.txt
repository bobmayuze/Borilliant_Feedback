HOMEWORK 5: MULTI LINKED LISTS


NAME:  Ziniu Yu


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

	http://www.geeksforgeeks.org/a-linked-list-with-next-and-arbit-pointer/
	http://www.coderslexicon.com/generating-non-repeating-random-values-in-c/
	http://stackoverflow.com/questions/2879700/c-array-of-pointers
	And several LMS questions.

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  20+



TESTING & DEBUGGING STRATEGY:
Please be concise!  

	Comment out all functions or operations, test them one by one.
	Test all corner cases (No element, one element, repeat element,
	first element, last element, different types and etc.) Use Dr.
	Memory to find memory problems.


ORDER NOTATION of the member functions of MultiLL?
(in terms of n, the number of elements currently in the list)

	default constructor	O(1)

	copy constructor	O(n^2)->O(n)

	assignment operator	O(n^2)

	destructor		O(n)

	size			O(1)

	empty			O(1)

	clear			O(n)

	add			O(n^2)

	erase			O(1)

	begin_chronological	O(1)

	end_chronological	O(1)

	begin_sorted		O(1)

	end_sorted		O(1)

	begin_random		O(n)


ITERATOR INVALIDATION:
In what cases will iterators of the MultiLL be invalidated?  Justify
the need for each of the restrictions placed on your implementation.

	The iterator of random link will invalidate as soon as there
	are any modifications of MultiLL. It must be regenerate random
	pointer after each modification.
	The iterators of chronological and sorted links will not 
	invalidate.
	
EXTRA CREDIT: 
Which function in your implementation can be improved by a
non-insertion sort sorting method?  Describe.

	Copy constructor. O(n)

	Create the copy of Node 1 and insert it between Node 1 & Node 2
	in original Linked List(chronological link), create the copy of
	2 and insert it between 2 & 3… Continue in this fashion, add the
	copy of N after the Nth node. Then restore their points like this:
		original->next = original->next->next;
		copy->next = copy->next->next;
		original->previous = original->previous->previous;
		copy->previous  = copy->previous->previous;
	Finally, modify the original list and copied list’s heads and tails.

MISC. COMMENTS TO GRADER:  
Optional, please be concise!

	Well, I have tons of work to do this week, and I have lots of
	exams, so I have to use a precious late day. I stuck in random
	linked list for about 3 days and have almost no idea how to do
	it. I’m sure what I have done still got some bugs in it. As far
	as I know, there is a chance that you can meet segmentation fault
	at random part, you can just rerun the program. I will not give
	up until all problems are solved… maybe after spring break:)
	Thank you for grading! Have a wonderful holiday!
