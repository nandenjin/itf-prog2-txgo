
#include "Ranking.h"

void loadRanking( RankNode *ranking, int *n ){

  FILE *fp = fopen( RANKING_DATA_FILE, "r" );

  if( fp != NULL ){

    int i;
    for( i = 0; i < 10; i++ ){

      if( fscanf( fp, "%s %d", ranking[i].name, &(ranking[i].score) ) == EOF ){

        break;

      }

    }

    *n = i;

    fclose( fp );

  }else{

    *n = 0;

  }

}

int isRankedIn( int score ){

  RankNode ranking[10];
  int length;

  loadRanking( ranking, &length );

  if( length < 10 ) return 1;

  for( int i = 0; i < length; i++ ){

    if( ranking[i].score > score ) return 1;

  }

  return 0;

}

void joinToRanking( char *name, int score ){

  RankNode ranking[11];
  int length;

  loadRanking( ranking, &length );
  ranking[length].score = score;
  strcpy( ranking[length].name, name );
  length++;

  sortRanking( ranking, length );

  FILE *fp = fopen( RANKING_DATA_FILE, "w" );

  if( fp == NULL ){

    printf( "ERROR: Cannot open ranking file: %s\n", RANKING_DATA_FILE );
    exit( EXIT_FAILURE );

  }

  for( int i = 0; i < length; i++ ){

    if( i >= 10 ) break;

    fprintf( fp, "%s %d\n", ranking[i].name, ranking[i].score );

  }

  fclose( fp );

}

void sortRanking( RankNode *ranking, int length ){

  for( int i = 0; i < length; i++ ){

    for( int j = 0; j < length - 1; j++ ){

      if( ranking[j].score > ranking[j+1].score ){

        char n[20];
        strcpy( n, ranking[j+1].name );
        int s = ranking[j+1].score;

        strcpy( ranking[j+1].name, ranking[j].name );
        ranking[j+1].score = ranking[j].score;

        strcpy( ranking[j].name, n );
        ranking[j].score = s;

      }

    }

  }

}

void renderRanking( void ){

  RankNode ranking[10];
  int length;
  loadRanking( ranking, &length );

  for( int i = 0; i < length; i++ ){

    char d[30];
    sprintf( d, "%s %ds", ranking[i].name, ranking[i].score );

    if( i < 4 ) RenderText( d, 200, 100 + 40 * i );
    else if( i < 7 ) RenderText( d, 380, 100 + 40 * ( i - 4 ) );
    else RenderText( d, 600, 100 + 40 * ( i - 7 ) );

  }

}
