HOMEWORK 9:  PRIORITY QUEUES FOR MESH SIMPLIFICATION


NAME:  Ziniu Yu


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Every threads on LMS
Lecture notes
Went to office hour once
This time, Google seems not that useful

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  20h+


ALGORITHM ANALYSIS: 
Assume v_0 vertices, e_0 edges, and t_0 triangles in the initial mesh,
reduced to t_final triangles using the -shortest criteria.  What is
the overall order notation for the program?  Analyze the separate
compoenents of the program to justify your answer.

ALGORITHM ANALYSIS -- LINEAR:

First we need to insert each of these stuff. It will cost O(v_0)to 
insert vertices	, O(t_0) to insert triangles, O(e_0 log e_0) to insert
edges. Then we get an edge to deal with. After we get two vertexes of
that edge, we need to erase the edges of those vertices, and each of
the RemoveEdge takes O(log e_0), each of the RemoveTriangle takes
O(log t_0). After that, we need to reinsert edges and triangles and
these will take O(log e_0) and O(1), respectively. Finally, we need to
remove a vertex which will take O(log v_0).

Based on my analysis, the overall order notation for the program is
O(V_0 + t_0 + e_0 * log e_0 + (t_0 - t_final) * (log e_0 + log t_0 +
log v_0))

ALGORITHM ANALYSIS -- PRIORITY QUEUE:

Just like the normal one, we need to insert all the edges in to the
priority queue, and it will cost O(e_0) to create the map, and will
take O(e_0 * log e_0) to make the heap. Remove and pop edges takes
O(log e_0). Update edges will take O(log e_0), too. 

Based on my analysis, the overall order notation for priority queue is
about O(e_0 * log e_0).

EXTRA CREDIT:  COLOR & OVERALL APPERANCE
Discuss the quality of your results in your README.txt and include
screenshots of your more impressive results.  If you have submitted
screenshots, give the file names and describe the results.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!

I have totally no idea how those codes work or how those codes do not
work. Maybe they are just miracles, who knows? And my brain hurts. 

I’ve tried to use the first method in the beginning, and I am very sure
I’m doing it right, but I just do not know why it failed. So I had to
use the second method finally.