#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "slower.h"

#define STR(s)  #s
#define XSTR(s) STR(s)

#define NORMAL()  printf("\x1b[0m")
#define OTHER()   printf("\x1b[5m\x1b[3;37m")

int main() {
  srand((unsigned int) time(nullptr));
  slower x;
  slower_rand(&x);
  printf("J'ai choisi une suite de %d lettres minuscules.\n"
      "Ces lettres, je les ai tirées au hasard parmi les %d premières"
      " lettres de\nl'alphabet usuel.\nMission pour toi si tu l'acceptes :"
      " deviner la suite des %d lettres.\n",
      SLOWER_LENGTH, LOWER_CARD, SLOWER_LENGTH);
#if SLOWER_COMPAR_LENGTH < SLOWER_LENGTH
  OTHER();
  printf("(Psst ! Il ne fera la comparaison que sur %s !)\n",
      SLOWER_COMPAR_LENGTH == 1
      ? "la première lettre"
      : "les " XSTR(SLOWER_COMPAR_LENGTH) " premières lettres");
  NORMAL();
#endif
  while (1) {
    printf("\nTa proposition ? ");
    slower y;
    if (slower_fget(&y, stdin) != 0) {
      printf("\nTu arrêtes ? Dommage...\nJ'avais choisi '");
      slower_fput(&x, stdout);
      printf("'.\nÀ une autre fois peut-être ?\n");
      OTHER();
      printf("(Petit joueur !!!)\n");
      NORMAL();
      printf("\n");
      return EXIT_FAILURE;
    }
    int c = slower_compar(&x, &y);
    if (c == 0) {
      printf("Tu as gagné !\nTu as découvert que j'avais choisi '");
      slower_fput(&x, stdout);
      printf("'.\nBravo !\n");
      OTHER();
      printf("(Merci qui ??\?)\n");
      NORMAL();
      printf("\n");
      return EXIT_SUCCESS;
    }
    printf("Loupé !\n");
    OTHER();
    printf("(Psst ! Vise plus %s...)\n", c < 0 ? "bas" : "haut");
    NORMAL();
  }
}
