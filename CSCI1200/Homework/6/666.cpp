
/*
 * Generate battleship puzzles.
 *
 * Copyright (c) 2005-2008 James Dow Allen
 * This code is made available, without warrantee,
 *      under General License subject to the provision that
 *      it not be used in a product to be sold for profit.
 * Contact the author (jamesdowallen at gmail.com) if
 *      you need a stronger License.
 *
 * Usage:
 * cc -O -o bship bship.c
 * bship
 *	- generate many valid puzzles.
 * bship | grep rows | sort -nr | head
 *	- show puzzles; hardest first
 * bship #S1 #S2
 *	- generate HTML of the puzzle with S1 and S2 as clues.
 * bship 4321313111 1412063021
 *	- example, using rows and cols found with
 *		bship | grep rows | sort -nr | head -1
 *
 * I've compiled for X86 Linux.  Might work for Windoze:
 *	just get rid of getpid() -- you don't need it.
 */

#include	<stdio.h>
#include	<stdlib.h>

/* Parameters for puzzle generation */
#define	BWID	10	/* Width */
#define	BHEI	BWID	/* Height -- not sure if non-square grid ever tested */
#define	NUM5	0	/* Number of Carriers */
#define	NUM4	1	/* Number of Battleships */
#define	NUM3	2	/* Number of Cruisers */
#define	NUM2	3	/* Number of Destroyers */
#define	NUM1	4	/* Number of Submarines */

#define	PRESUB	1	/* Number of submarines to be preplaced */
#define	SUB_X	8	/* X coord of 1st preplaced sub */
#define	SUB_Y	4	/* Y coord of 1st preplaced sub */

/* Stop solution search when MAXTOT solutions are found.
 * Normally MAXTOT == 2 is appropriate since any puzzle
 * with more thna one solution will be rejected anyway.
 */
#define	MAXTOT	2

struct pos {
	char	v[BWID][BHEI];
} Ipos, Solved;

struct sco {
	char	ctot[BWID];
	char	rtot[BHEI];
} Thesco;

struct node {
	struct pos np;
	struct sco ns;
};

/* We'd like to estimate the difficulty of a puzzle (Complexity)
 * and print that with the puzzle.
 * Unfortunately, the estimation here is VERY VERY crude.
 */
int	Complexity;

/* function prototypes */
int solver(int sx, int sy, struct node *tp,
		int numa, int numb, int numc, int numd, int nums);
int cntsol(struct sco *sp);
void rand_perturb(void);
int randi(int k);
int kplace(struct pos *pp, int len, int x, int y, int dir);
int rplace(struct pos *pp, int len);
void genrand(struct pos *pp);
void setit(char *sp, char *cp, int len);
int cntzz(struct sco *sp);
int doit(void);
int main(int argc, char **argv);
void showpos(struct pos *pp, struct sco *sp);
void scoreit(struct pos *pp, struct sco *sp);
void genhtml(int m);

/* Find solutions, recursively */
int solver(int sx, int sy, struct node *tp,
		int numa, int numb, int numc, int numd, int nums)
{
	int	x, y, k, dir, shipt, shipnxt;
	struct node tnode;
	int	cnt;

	++Complexity;
	cnt = 0;
	shipt = numa ? 5 : numb ? 4 : numc ? 3 : numd ? 2 : nums ? 1 : 0;
	if (shipt == 0) {
		Solved = tp->np;
		return 1;
	}
	shipnxt = numa > 1 ? 5 : numb > 1 ? 4
			: numc > 1 ? 3 : numd > 1 ? 2 : nums > 1 ? 1 : 0;
	/*
	 * Deeply nested code follows.
	 * To save white space, we indent ONLY at
	 * levels which require " { ... } "
	 */
	for (x = sx; x < BWID; x++)
	if (tp->ns.ctot[x])
	for (y = (x == sx ? sy : 0); y < BHEI; y++)
	if (tp->ns.rtot[y])
	for (dir = 0; dir < (shipt == 1 ? 1 : 2); dir++)
	if (shipt == 1 || (dir ? x < BWID + 1 - shipt : y < BHEI + 1 - shipt))
	if (shipt == 1 || (dir ? tp->ns.rtot[y] : tp->ns.ctot[x]) >= shipt)
	if (1) {
		tnode = *tp;
		if (! kplace(&tnode.np, shipt, x, y, dir))
			continue;
		if (dir) {
			tnode.ns.rtot[y] -= shipt;
			for (k = 0; k < shipt; k++) {
				if (tnode.ns.ctot[x + k] == 0)
					goto fail;
				tnode.ns.ctot[x + k] -= 1;
			}
		} else {
			tnode.ns.ctot[x] -= shipt;
			for (k = 0; k < shipt; k++) {
				if (tnode.ns.rtot[y + k] == 0)
					goto fail;
				tnode.ns.rtot[y + k] -= 1;
			}
		}
		if (shipt > 9) {
			printf("Tried setting %d-ship:\n", shipt);
			showpos(&tnode.np, &tnode.ns);
		}
		if (shipt == shipnxt) {
			switch (shipt) {
			case 5:
				cnt += solver(x, y, &tnode, numa - 1,
					numb, numc, numd, nums);
				break;
			case 4:
				cnt += solver(x, y, &tnode, numa, numb - 1,
					numc, numd, nums);
				break;
			case 3:
				cnt += solver(x, y, &tnode, numa, numb,
					numc - 1, numd, nums);
				break;
			case 2:
				cnt += solver(x, y, &tnode, numa, numb,
					numc, numd - 1, nums);
				break;
			case 1:
				cnt += solver(x, y, &tnode, numa, numb,
					numc, numd, nums - 1);
				break;
			}
		} else {
			switch (shipt) {
			case 5:
				cnt += solver(0, 0, &tnode, numa - 1,
					numb, numc, numd, nums);
				break;
			case 4:
				cnt += solver(0, 0, &tnode, numa, numb - 1,
					numc, numd, nums);
				break;
			case 3:
				cnt += solver(0, 0, &tnode, numa, numb,
					numc - 1, numd, nums);
				break;
			case 2:
				cnt += solver(0, 0, &tnode, numa, numb,
					numc, numd - 1, nums);
				break;
			case 1:
				cnt += solver(0, 0, &tnode, numa, numb,
					numc, numd, nums - 1);
				break;
			}
		}
		if (cnt >= MAXTOT)
			return cnt;
	fail:
		continue;
	}
	return cnt;
}

/* Return number of solutions */
int cntsol(struct sco *sp)
{
	int	x, y;
	struct node tnode;

	tnode.ns = *sp;
	for (x = 0; x < BWID; x++)
	for (y = 0; y < BHEI; y++)
		tnode.np.v[x][y] = 0;
	if (PRESUB > 0) {
		kplace(&tnode.np, 1, SUB_X, SUB_Y, 0);
		tnode.ns.rtot[SUB_Y] -= 1;
		tnode.ns.ctot[SUB_X] -= 1;
	}
	if (PRESUB > 1) {
		printf("Specify 2nd sub's location; recompile.\n");
		exit(1);
	}
	Complexity = 0;
	return solver(0, 0, &tnode, NUM5, NUM4, NUM3, NUM2, NUM1 - PRESUB);
}

/* seed the PRNG.  (Compiler will warn that we forgot some #includes) */
void rand_perturb(void)
{
	srandom(getpid() + (int)time((long *)0));
}

/* return from {0,1,...,k-1} randomly */
int randi(int k)
{
	return (random() >> 4 & 0xffffff) % k;
}

/* Place a ship, updating data structures
 * If the ship would touch another, don't, just return 0
 */
int kplace(struct pos *pp, int len, int x, int y, int dir)
{
	int	k;

	if (dir) {
		for (k = 0; k < len; k++)
			if (pp->v[x + k][y])
				return 0;
		for (k = 0; k < len; k++) {
			if (y > 0)
				pp->v[x + k][y - 1] = 1;
			if (y < BHEI - 1)
				pp->v[x + k][y + 1] = 1;
			pp->v[x + k][y] = 2;
		}
		if (x > 0) {
			pp->v[x - 1][y] = 1;
			if (y > 0)
				pp->v[x - 1][y - 1] = 1;
			if (y < BHEI - 1)
				pp->v[x - 1][y + 1] = 1;
		}
		if (x + len < BWID) {
			pp->v[x + len][y] = 1;
			if (y > 0)
				pp->v[x + len][y - 1] = 1;
			if (y < BHEI - 1)
				pp->v[x + len][y + 1] = 1;
		}
	} else {
		for (k = 0; k < len; k++)
			if (pp->v[x][y + k])
				return 0;
		for (k = 0; k < len; k++) {
			if (x > 0)
				pp->v[x - 1][y + k] = 1;
			if (x < BWID - 1)
				pp->v[x + 1][y + k] = 1;
			pp->v[x][y + k] = 2;
		}
		if (y > 0) {
			pp->v[x][y - 1] = 1;
			if (x > 0)
				pp->v[x - 1][y - 1] = 1;
			if (x < BWID - 1)
				pp->v[x + 1][y - 1] = 1;
		}
		if (y + len < BHEI) {
			pp->v[x][y + len] = 1;
			if (x > 0)
				pp->v[x - 1][y + len] = 1;
			if (x < BWID - 1)
				pp->v[x + 1][y + len] = 1;
		}
	}
	return 1;
}

/* place a ship randomly */
int rplace(struct pos *pp, int len)
{
	int	x, y;

	if (len == 1 || randi(2)) {
		x = randi(BWID - len + 1);
		y = randi(BHEI);
		return kplace(pp, len, x, y, 1);
	} else {
		x = randi(BWID);
		y = randi(BHEI - len + 1);
		return kplace(pp, len, x, y, 0);
	}
	return 1;
}

/* Create a random placement for all ships */
void genrand(struct pos *pp)
{
	int	x, y, i;

  retry:
	for (x = 0; x < BWID; x++)
	for (y = 0; y < BHEI; y++)
		pp->v[x][y] = 0;
	if (PRESUB > 0)
		kplace(pp, 1, SUB_X, SUB_Y, 0);
	for (x = 0; x < NUM5; x++)
		for (i = 0; ; i++)
			if (rplace(pp, 5))
				break;
			else if (i > 100)
				goto retry;
	for (x = 0; x < NUM4; x++)
		for (i = 0; ; i++)
			if (rplace(pp, 4))
				break;
			else if (i > 100)
				goto retry;
	for (x = 0; x < NUM3; x++)
		for (i = 0; ; i++)
			if (rplace(pp, 3))
				break;
			else if (i > 100)
				goto retry;
	for (x = 0; x < NUM2; x++)
		for (i = 0; ; i++)
			if (rplace(pp, 2))
				break;
			else if (i > 200)
				goto retry;
	for (x = 0; x < NUM1 - PRESUB; x++)
		for (i = 0; ; i++)
			if (rplace(pp, 1))
				break;
			else if (i > 200)
				goto retry;
}

/* Convert, e.g. "12005" to "\1\2\0\0\5" */
void setit(char *sp, char *cp, int len)
{
	while (len--)
		*sp++ = *cp++ - '0';
}

/* Count zeros --> choose high for easy, low for hard */
int cntzz(struct sco *sp)
{
	int	i, ztot;

	ztot = 0;
	for (i = 0; i < BWID; i++)
		ztot += sp->ctot[i] == 0;
	for (i = 0; i < BHEI; i++)
		ztot += sp->rtot[i] == 0;
	if (PRESUB > 0) {
		ztot += sp->ctot[SUB_X] == 1;
		ztot += sp->rtot[SUB_Y] == 1;
	}
	return ztot;
}

/* Display the unique solution for Thesco, if there is one */
int doit(void)
{
	int	numsol, numz;

	numsol = cntsol(&Thesco);
	if (numsol == 1) {
		numz = cntzz(&Thesco);
		printf("\nUnique solution\n");
		printf(" (%08d) (%02d) ", Complexity, numz);
		showpos(&Solved, &Thesco);
		return 1;
	} else {
#if	0
		showpos(&Solved, &Thesco);
		printf("Number of solutions = %d\n\n", numsol);
#endif
		return 0;
	}
}

int main(int argc, char **argv)
{
	int	iter;

	setlinebuf(stdout);
	if (argc == 3) {
		setit(Thesco.rtot, argv[1], BHEI);
		setit(Thesco.ctot, argv[2], BWID);
		if (doit()) {
			printf("<p>Puzzle:\n");
			genhtml(0);
			printf("<p>Solution:\n");
			genhtml(1);
		} else {
			printf("You asked for an invalid puzzle\n");
		}
		exit(0);
	}
	rand_perturb();	/* So each run is different */
	/* Generate 100 puzzles and terminate */
	for (iter = 0; iter < 100; ) {
		genrand(&Ipos);
		scoreit(&Ipos, &Thesco);
		/* In my opinion, a, say 10x10, problem must have
		 *   non-empty 1st and last rows and non-empty
		 *   1st and last columns -- otherwise it is a
		 *   9x10 problem (or less).
		 * Reject problems which lack that criterion.
		 */
		if (Thesco.ctot[0] == 0) continue;
		if (Thesco.rtot[0] == 0) continue;
		if (Thesco.ctot[BWID - 1] == 0) continue;
		if (Thesco.rtot[BHEI - 1] == 0) continue;
		iter += doit();
	}
	exit(0);
}

void showpos(struct pos *pp, struct sco *sp)
{
	int	x, y;

	printf("Totals:  rows: ");
	for (y = 0; y < BHEI; y++)
		printf("%d", sp->rtot[y]);
	printf("  cols: ");
	for (x = 0; x < BWID; x++)
		printf("%d", sp->ctot[x]);
	printf("\n");
	printf("\n");
	printf("    ");
	for (x = 0; x < BWID; x++)
		printf("%2d", sp->ctot[x]);
	printf("\n");
	for (y = 0; y < BHEI; y++) {
		printf(" %2d ", sp->rtot[y]);
		for (x = 0; x < BWID; x++)
			printf(" %c", ". X"[pp->v[x][y]]);
		printf("\n");
	}
	printf("\n");
}

void scoreit(struct pos *pp, struct sco *sp)
{
	int	x, y, tot;

	for (x = 0; x < BWID; x++) {
		for (tot = y = 0; y < BHEI; y++) {
			if (pp->v[x][y] == 2)
				++tot;
		}
		sp->ctot[x] = tot;
	}
	for (y = 0; y < BHEI; y++) {
		for (tot = x = 0; x < BWID; x++) {
			if (pp->v[x][y] == 2)
				++tot;
		}
		sp->rtot[y] = tot;
	}
}

/* Create a html table for a puzzle */
void genhtml(int showsol)
{
	int	x, y;
	struct pos *pp = &Solved;
	struct sco *sp = &Thesco;

	printf("<table border=\"1\" bordercolor=\"#000000\" cellspacing=3 cellpadding=3 bgcolor=\"#f4dcf8\">\n");
	printf("<tr><td>&nbsp;");
	for (x = 0; x < BWID; x++)
		printf("<td>%c<br>%d", 'q' + x, sp->ctot[x]);
	printf("\n");
	for (y = 0; y < BHEI; y++) {
		printf("<tr><td>%c &nbsp; %d", 'A' + y, sp->rtot[y]);
		for (x = 0; x < BWID; x++) {
			if (showsol && pp->v[x][y] == 2)
				printf("<td align=center><b>X</b>");
			else if (PRESUB > 0
						&& x == SUB_X
						&& y == SUB_Y)
				printf("<td align=center><b>S</b>");
			else
				printf("<td>&nbsp;&nbsp;&nbsp;&nbsp;");
		}
		printf("\n");
	}
	printf("</table>\n");
}
