#ifndef BALPAR__H
#define BALPAR__H

//  balpar : tente de lire une expression bien parenthésée à partir de l'adresse
//    s. Renvoie l'adresse qui suit l'expression bien parenthésée lue en cas de
//    succès. Renvoie sinon s.
extern char *balpar(const char *s);

#endif
