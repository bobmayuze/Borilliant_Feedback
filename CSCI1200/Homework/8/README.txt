HOMEWORK 8: QUAD TREES AND TREE ITERATION


NAME:  Ziniu Yu


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

	http://stackoverflow.com/questions/15994538/find-binary-tree-height
	Asked 2 questions on LMS
	The rest all by myself

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  5hours



ORDER NOTATION ANALYSIS: 
Give the big O notation of each of the QuadTree operations and justify
your answer for the non trivial operations (please be concise!)
Analyze both the running time and the additional memory usage needed
(beyond the space allocated for the existing tree structure).  You may
assume that the tree is reasonably well balanced for all operations.


n = the number of elements in the tree


size()
  running time: O(1)
  memory usage: O(1)
	
	The size of QuadTree is stored in the class, so we can simply get
	it when we call size()

insert()
  running time: O(logn)
  memory usage: O(logn)

	Recursively insert the node to corresponding child node.
	
find()
  running time: O(logn)
  memory usage: O(1)

	Recursively find the node from corresponding child node.

height()
  running time: O(n)
  memory usage: O(n)

	We need to go through all nodes to find the maximum height.

begin()
  running time: O(1)
  memory usage:	 O(1)
	
	Just simply return the root node

end()
  running time: O(1)
  memory usage: O(1)

	Just simply return the NULL pointer

bf_begin()
  running time: O(1)
  memory usage: O(1)
	
	Just simply return the root node

bf_end()
  running time: O(1)
  memory usage: O(1)

	Just simply return the NULL pointer

operator++()
  running time: O(logn)/O(n)
  memory usage: O(1)/O(n)

	For the depth iterator: we get the child node or recursively
	get the next node
	For the breadth iterator: we first store all the node into a 
	list and then increment it

operator*()
  running time: O(1)
  memory usage: O(1)

	Just return the point of that node

getLabel()
  running time: O(1)
  memory usage: O(1)

	Just return the label of that node


getDepth()
  running time: O(logn)
  memory usage: O(1)

	Go through the parent pointer till the root

copy constructor
  running time: O(n)
  memory usage: O(n)

	Just copy every node of the old tree

assignment operator
  running time: O(n)
  memory usage: O(n)

	Same as copy, sometimes we need to delete current tree first

destructor
  running time: O(n)
  memory usage: O(n)

	Go to the leaves of the tree and delete each node till the root

EXTRA CREDIT:  TREE BALANCING
How does the point insertion order affect the shape of the resulting
QuadTree object? What are specific examples of the worst case and best
case?  Discuss your strategy for reordering the input to rebalance the
tree.  Paste example output with and without your rebalancing.

	The order of inserting object decide which nodes to be parents.
	The worst case is just like my student test case, which former
	object is the latter’s parent. And the best case is that the 
	tree is perfectly balanced, the height difference is less than
	2. 

	My strategy is recursively find the median point of x coordinate,
	and create a new vector, push_back the median point, and then
	divide each of the two half parts into upper and lower part,
	find the median points each half part separately and push_back
	them to the new vector. Repeat several time until the length of
	the half is 1 or 0.

	Following are two examples. One is from given test, one is from
	my own test.

// ==============================================================
// ==============================================================
// Example from given extra_credit_test

Beginning extra_credit_test()...

point collection:
+-----------------------------------------+
|                                         |
|                        A                |
|                                  B      |
|                C                        |
|     D                                   |
|                              E          |
|          F                              |
|                          G              |
|   H                                     |
|              I                          |
|                                   J     |
|                    K                    |
|                 L                       |
|                         M               |
|  N                                      |
|                                     O   |
|                               P         |
|           Q                             |
|                                    R    |
|    S                                    |
|               T                         |
|                       U                 |
|                                         |
+-----------------------------------------+

inserted sorted by y coordinate:
+-----------------------------------------+
|                        |                |
|------------------------A----------------|
|                |       |---------B------|
|----------------C-------|     |   ||     |
|-----D----------|   |   |     |   ||     |
|   | |    |     |   |   |-----E---||     |
|   | |----F-----|   |   | |   ||  ||     |
|   | |    |   | |   |   |-G---||  ||     |
|---H-|    |   | |   |   |||   ||  ||     |
|  ||||    |---I-|   |   |||   ||  ||     |
|  ||||    ||  |||   |   |||   ||  |J-----|
|  ||||    ||  |||---K---|||   ||  || |   |
|  ||||    ||  |||L--|  ||||   ||  || |   |
|  ||||    ||  ||||  |  ||M|   ||  || |   |
|--N|||    ||  ||||  |  ||||   ||  || |   |
|  ||||    ||  ||||  |  ||||   ||  ||-O---|
|  ||||    ||  ||||  |  ||||   |P--||||   |
|  ||||    |Q--||||  |  ||||   ||  ||||   |
|  ||||    ||  ||||  |  ||||   ||  ||R|   |
|  ||S|    ||  ||||  |  ||||   ||  ||||   |
|  ||||    ||  |T||  |  ||||   ||  ||||   |
|  ||||    ||  ||||  |--U|||   ||  ||||   |
|  ||||    ||  ||||  |  ||||   ||  ||||   |
+-----------------------------------------+
before balancing this tree has height = 5
A (24,1)
  C (16,3)
    D (5,4)
      H (3,8)
        N (2,14)
        S (4,19)
      F (10,6)
        I (14,9)
          Q (11,17)
          T (15,20)
    K (20,11)
      L (17,12)
      U (23,21)
  B (34,2)
    E (30,5)
      G (26,7)
        M (25,13)
      P (31,16)
    J (35,10)
      O (37,15)
        R (36,18)

new insertion order to improve tree quality:
K (20,11)
F (10,6)
D (5,4)
H (3,8)
C (16,3)
I (14,9)
Q (11,17)
N (2,14)
S (4,19)
L (17,12)
T (15,20)
E (30,5)
A (24,1)
G (26,7)
B (34,2)
J (35,10)
P (31,16)
M (25,13)
U (23,21)
O (37,15)
R (36,18)

resulting tree:
+-----------------------------------------+
|     |    |     |   |   |     |   |      |
|     |    |     |   |---A-----|   |      |
|     |    |     |   |   |     |---B------|
|     |    |-----C---|   |     |   |      |
|-----D----|     |   |   |     |   |      |
|     |    |     |   |---------E----------|
|----------F---------|     |   |    |     |
|   |      |   |     |-----G---|    |     |
|---H------|   |     |     |   |    |     |
|   |      |---I-----|     |   |    |     |
|   |      |   |     |     |   |----J-----|
|--------------------K--------------------|
|  |        |-----L--|    |     |     |   |
|  |        |     |  |----M-----|     |   |
|--N--------|     |  |    |     |     |   |
|  |        |     |  |    |     |-----O---|
|  |        |     |  |----------P---------|
|-----------Q--------|  |       |    |    |
|    |      |   |    |  |       |----R----|
|----S------|   |    |  |       |    |    |
|    |      |---T----|  |       |    |    |
|    |      |   |    |--U-------|    |    |
|    |      |   |    |  |       |    |    |
+-----------------------------------------+
after balancing this tree has height = 2
K (20,11)
  F (10,6)
    D (5,4)
    C (16,3)
    H (3,8)
    I (14,9)
  E (30,5)
    A (24,1)
    B (34,2)
    G (26,7)
    J (35,10)
  Q (11,17)
    N (2,14)
    L (17,12)
    S (4,19)
    T (15,20)
  P (31,16)
    M (25,13)
    O (37,15)
    U (23,21)
    R (36,18)

Finished with extra_credit_test().

// ==============================================================
// ==============================================================
// Example of my own test.

Beginning extra_credit_test()...

point collection:
+---------------------+
|*                    |
| A                   |
|  B                  |
|   C                 |
|    D                |
|     E               |
|      F              |
|       G             |
|        H            |
|         I           |
|          J          |
|           K         |
|            L        |
|             M       |
|              N      |
|               O     |
|                P    |
|                 Q   |
|                  R  |
|                   S |
|                    T|
+---------------------+

inserted sorted by y coordinate:
+---------------------+
|*--------------------|
||A-------------------|
|||B------------------|
||||C-----------------|
|||||D----------------|
||||||E---------------|
|||||||F--------------|
||||||||G-------------|
|||||||||H------------|
||||||||||I-----------|
|||||||||||J----------|
||||||||||||K---------|
|||||||||||||L--------|
||||||||||||||M-------|
|||||||||||||||N------|
||||||||||||||||O-----|
|||||||||||||||||P----|
||||||||||||||||||Q---|
|||||||||||||||||||R--|
||||||||||||||||||||S-|
|||||||||||||||||||||T|
+---------------------+
before balancing this tree has height = 20
* (0,0)
  A (1,1)
    B (2,2)
      C (3,3)
        D (4,4)
          E (5,5)
            F (6,6)
              G (7,7)
                H (8,8)
                  I (9,9)
                    J (10,10)
                      K (11,11)
                        L (12,12)
                          M (13,13)
                            N (14,14)
                              O (15,15)
                                P (16,16)
                                  Q (17,17)
                                    R (18,18)
                                      S (19,19)
                                        T (20,20)

new insertion order to improve tree quality:
J (10,10)
B (2,2)
* (0,0)
A (1,1)
C (3,3)
D (4,4)
G (7,7)
E (5,5)
F (6,6)
H (8,8)
I (9,9)
M (13,13)
K (11,11)
L (12,12)
N (14,14)
O (15,15)
R (18,18)
P (16,16)
Q (17,17)
S (19,19)
T (20,20)

resulting tree:
+---------------------+
|*-|       |          |
||A|       |          |
|--B-------|          |
|  |C------|          |
|  ||D-----|          |
|  |||E-|  |          |
|  ||||F|  |          |
|  |||--G--|          |
|  |||  |H-|          |
|  |||  ||I|          |
|----------J----------|
|          |K-|       |
|          ||L|       |
|          |--M-------|
|          |  |N------|
|          |  ||O-----|
|          |  |||P-|  |
|          |  ||||Q|  |
|          |  |||--R--|
|          |  |||  |S-|
|          |  |||  ||T|
+---------------------+
after balancing this tree has height = 6
J (10,10)
  B (2,2)
    * (0,0)
      A (1,1)
    C (3,3)
      D (4,4)
        G (7,7)
          E (5,5)
            F (6,6)
          H (8,8)
            I (9,9)
  M (13,13)
    K (11,11)
      L (12,12)
    N (14,14)
      O (15,15)
        R (18,18)
          P (16,16)
            Q (17,17)
          S (19,19)
            T (20,20)

Finished with extra_credit_test().

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


