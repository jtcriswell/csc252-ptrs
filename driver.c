/*
 * File: driver.c
 *
 * Description:
 *  This file calls the functions written by students and prints the output
 *  to standard output.  The inputs are read from standard input so that shell
 *  scripts can repeatedly call student code with different inputs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Triangle Type */
struct triangle {
  unsigned long a;
  unsigned long b;
  unsigned long c;
};

/* Ratio Type */
struct ratio {
  signed long a;
  signed long b;
  signed long c;
  signed long d;
};

/* Card Type */
struct card {
  unsigned char card;
  struct card * next;
};

/* Function prototypes for student code */
extern unsigned long findHypSq (struct triangle * p);
extern signed long ratios (struct ratio * p, unsigned long numElems);
extern unsigned long removeCard (struct card * p, unsigned long card);

/* Constant values for cards */
static const unsigned char hearts = 0;
static const unsigned char diamonds = 1;
static const unsigned char clubs = 2;
static const unsigned char spades = 3;

int
main (int argc, char ** argv) {
  /* Values for the ratio test */
  unsigned long numRatios;
  signed long a, b, c, d;

  /* Number of Cards to Allocate */
  unsigned long numCards = 0;

  /* Card to Remove */
  unsigned long cardToRemove = 0;

  /* Index variable */
  unsigned int index;

  /*
   * Call the student's findHypSq() function and print its return value.
   */
  struct triangle tri = {0,0,0};
  printf ("Please enter lengths of the triangle:");
  fflush (stdout);
  scanf ("%ld %ld", &(tri.a), &(tri.b));
  if (findHypSq (&tri)) {
    printf ("findHypSq: Integer Overflow/Underflow\n"); 
  } else {
    printf ("findHypSq: %ld %ld = %ld\n", tri.a, tri.b, tri.c); 
  }
  fflush (stdout);

  /*
   * Call the student's ratios() function and print its return value.
   */
  printf ("Please enter number of ratios: ");
  fflush (stdout);
  scanf ("%ld", &numRatios);
  if (numRatios >= (ULONG_MAX / sizeof (struct ratio))) {
    fprintf (stderr, "Too many ratios\n");
    return 1;
  }
  struct ratio * ratArray = malloc (sizeof (struct ratio) * numRatios);
  for (index= 0; index < numRatios; ++index) {
    printf ("Please enter a, b, c for ratio %d: ", index);
    fflush (stdout);
    scanf ("%ld %ld %ld", &a, &b, &c);
  }
  ratios (ratArray, numRatios);
  for (index= 0; index < numRatios; ++index) {
    printf ("ratios: %ld/%ld = %ld/%ld\n", ratArray[index].a,
                                           ratArray[index].b,
                                           ratArray[index].c,
                                           ratArray[index].d); 
  }
  fflush (stdout);

  /*
   * Call the student's removeCard() function and print the hand.
   */
  printf ("Please enter number of cards: ");
  fflush (stdout);
  scanf ("%ld", &numCards);
  printf ("Please enter card to remove: ");
  fflush (stdout);
  scanf ("%ld", &cardToRemove);
  struct card * cp = NULL;
  for (index = 0; index < numCards; ++index) {
    /* Allocate a new card */
    struct card * newCardp = malloc (sizeof (struct card));
    printf ("Please enter card number %d: ", index);
    fflush (stdout);
    scanf ("%hhx", &(newCardp->card));
    if (cp == NULL) {
      cp = newCardp;
      cp->next = NULL;
    } else {
      newCardp->next = cp;
      cp = newCardp;
    }
  }
  removeCard (cp, cardToRemove);
  for (; cp != NULL; cp = cp->next) {
    printf ("removeCard: %p: %hhx\n", cp, cp->card);
    fflush (stdout);
  }

  /*
   * Note that we don't deallocate any heap memory we've allocated.  Since the
   * process is terminating, the operating system kernel will reclaim all
   * memory used by the process.
   */
  return 0;
}
