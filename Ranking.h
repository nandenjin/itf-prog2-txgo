
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TextUtil.h"

typedef struct {

  int score;
  char name[20];

} RankNode;

#define RANKING_DATA_FILE "./ranking_data.txt"

void loadRanking( RankNode *ranking, int *n );
int isRankedIn( int score );
void sortRanking( RankNode *ranking, int length );
void renderRanking( void );
