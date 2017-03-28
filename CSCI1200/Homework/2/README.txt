HOMEWORK 2: TENNIS CLASSES


NAME:  Ziniu Yu


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

	LMS
	cplusplus.com
	lecture notes
	google

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.

	

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  15+



DESCRIPTION OF 3RD STATISTIC:
Please be concise!

	My third table is about win round percentage. It first count
	the win and lose numbers for each player, and compute the win
	round percentage by the following formula:
		rpercent = winround / (winround + loseround)
	Furthermore, it have something called easy win and tough win
	percentages. If player wins the round by three or more scores
	(such as 6-0 6-3), it count as one easy win. If player wins
	the round by two or less scores (such as 7-6 6-4), it count
	as one tough win. Those two percentages show the potential of
	a player. This table is sort by win round percentage.

RESULTS FROM 3RD STATISTIC:
Paste in a small amount of sample output into this file, or list the
file names of sample input & output included with your submisssion.
Describe what is interesting about your statistic on this data.
Please be concise!

/////////////////////////////////
//input file: sample_scores.txt//
/////////////////////////////////

ROUND STATISTICS
Player              W    L   percentage         easy        tough
Marcos Baghdatis    9    6        0.600        0.444        0.556
David Nalbandian    5    5        0.500        0.800        0.200
Ivan Ljubicic       2    3        0.400        0.500        0.500
Radek Stepanek      2    3        0.400        1.000        0.000
Danai Udomchoke     2    3        0.400        0.500        0.500

///////////////////////////////////////
//input file: mens_2014_5_setters.txt//
///////////////////////////////////////

ROUND STATISTICS
Player                    W    L   percentage         easy        tough
Kevin Anderson           12    8        0.600        0.417        0.583
Facundo Bagnis            3    2        0.600        0.667        0.333
Roberto Bautista-Agut     6    4        0.600        0.333        0.667
Thomaz Bellucci           3    2        0.600        0.667        0.333
Tomas Berdych             3    2        0.600        1.000        0.000
Jeremy Chardy             3    2        0.600        0.000        1.000
Nikolay Davydenko         3    2        0.600        0.667        0.333
Grigor Dimitrov           3    2        0.600        0.333        0.667
Damir Dzumhur             3    2        0.600        1.000        0.000
Matthew Ebden             3    2        0.600        0.667        0.333
Teymuraz Gabashvili       3    2        0.600        0.000        1.000
Santiago Giraldo          3    2        0.600        0.333        0.667
Jan Hernych               3    2        0.600        0.667        0.333
Tatsuma Ito               3    2        0.600        1.000        0.000
Blaz Kavcic               3    2        0.600        1.000        0.000
Alexander Kudryavtsev     3    2        0.600        0.333        0.667
Andrey Kuznetsov          6    4        0.600        0.833        0.167
Dusan Lajovic             3    2        0.600        0.667        0.333
Feliciano Lopez           3    2        0.600        0.333        0.667
Yen-Hsun Lu               3    2        0.600        0.333        0.667
Adrian Mannarino          3    2        0.600        0.667        0.333
Paul-Henri Mathieu        3    2        0.600        0.333        0.667
Florian Mayer             3    2        0.600        0.667        0.333
Leonardo Mayer            3    2        0.600        0.333        0.667
Axel Michon               3    2        0.600        0.667        0.333
Vincent Millot            3    2        0.600        0.667        0.333
Andy Murray               6    4        0.600        0.667        0.333
Jarkko Nieminen           6    4        0.600        0.500        0.500
Kei Nishikori            12    8        0.600        0.333        0.667
Benoit Paire              6    4        0.600        0.333        0.667
Julian Reister            3    2        0.600        0.000        1.000
Tommy Robredo             9    6        0.600        0.556        0.444
Joao Sousa                3    2        0.600        0.333        0.667
Jan-Lennard Struff        3    2        0.600        0.667        0.333
Dominic Thiem             3    2        0.600        0.667        0.333
Jo-Wilfried Tsonga        6    4        0.600        0.500        0.500
Jerzy Janowicz           11    9        0.550        0.545        0.455
Novak Djokovic            8    7        0.533        0.625        0.375
Martin Klizan             8    7        0.533        0.375        0.625
Simone Bolelli           10   10        0.500        0.400        0.600
Marin Cilic              10   10        0.500        0.500        0.500
Guillermo Garcia-Lopez    5    5        0.500        0.600        0.400
Richard Gasquet           5    5        0.500        0.800        0.200
Marcel Granollers        10   10        0.500        0.400        0.600
Ernests Gulbis            5    5        0.500        0.600        0.400
Andreas Haider-Maurer     5    5        0.500        0.600        0.400
Nick Kyrgios              5    5        0.500        0.000        1.000
Sam Querrey               5    5        0.500        0.400        0.600
Milos Raonic              5    5        0.500        0.400        0.600
Gilles Simon             10   10        0.500        0.500        0.500
Radek Stepanek            5    5        0.500        0.400        0.600
Fernando Verdasco        10   10        0.500        0.400        0.600
Jiri Vesely               5    5        0.500        0.400        0.600
Stanislas Wawrinka        5    5        0.500        0.400        0.600
Donald Young              5    5        0.500        0.400        0.600
Mikhail Youzhny           5    5        0.500        0.800        0.200
Julien Benneteau          7    8        0.467        0.714        0.286
Roger Federer             7    8        0.467        0.143        0.857
Fabio Fognini             7    8        0.467        0.429        0.571
Steve Johnson             7    8        0.467        0.571        0.429
Andreas Seppi             7    8        0.467        0.429        0.571
Gael Monfils              9   11        0.450        0.444        0.556
Facundo Arguello          2    3        0.400        0.500        0.500
Benjamin Becker           2    3        0.400        0.500        0.500
Daniel Brands             4    6        0.400        0.250        0.750
Pablo Carreno-Busta       4    6        0.400        0.750        0.250
Pablo Cuevas              4    6        0.400        0.000        1.000
Frank Dancevic            2    3        0.400        0.500        0.500
Steve Darcis              2    3        0.400        1.000        0.000
Juan-Martin Del-Potro     2    3        0.400        0.000        1.000
Somdev Devvarman          2    3        0.400        0.500        0.500
Ivan Dodig                4    6        0.400        0.500        0.500
Alexandr Dolgopolov       4    6        0.400        0.750        0.250
Evgeny Donskoy            2    3        0.400        1.000        0.000
James Duckworth           2    3        0.400        0.500        0.500
David Ferrer              2    3        0.400        0.500        0.500
Maximo Gonzalez           2    3        0.400        0.000        1.000
Robin Haase               2    3        0.400        1.000        0.000
Lleyton Hewitt            4    6        0.400        0.000        1.000
Tobias Kamke              2    3        0.400        0.000        1.000
Ivo Karlovic              2    3        0.400        0.500        0.500
Bradley Klahn             2    3        0.400        0.000        1.000
Philipp Kohlschreiber     4    6        0.400        0.500        0.500
Lukasz Kubot              2    3        0.400        1.000        0.000
Mikhail Kukushkin         2    3        0.400        1.000        0.000
Alex Kuznetsov            2    3        0.400        1.000        0.000
Laurent Lokoli            2    3        0.400        0.000        1.000
Nicolas Mahut             2    3        0.400        0.500        0.500
Marinko Matosevic         4    6        0.400        0.000        1.000
Jurgen Melzer             2    3        0.400        1.000        0.000
Gilles Muller             2    3        0.400        0.000        1.000
Aleksandr Nedovyesov      2    3        0.400        0.500        0.500
Wayne Odesnik             2    3        0.400        0.000        1.000
Vasek Pospisil            2    3        0.400        1.000        0.000
Michal Przysiezny         2    3        0.400        0.000        1.000
Edouard Roger-Vasselin    2    3        0.400        0.500        0.500
Blaz Rola                 2    3        0.400        1.000        0.000
Lukas Rosol               2    3        0.400        0.500        0.500
Michael Russell           2    3        0.400        0.000        1.000
Dudi Sela                 2    3        0.400        0.500        0.500
Jordan Thompson           2    3        0.400        0.500        0.500

MISC. COMMENTS TO GRADER:  
Optional, please be concise!


