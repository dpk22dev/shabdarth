#ifndef READ_DB_H
#define READ_DB_H

#define WORD_SIZE 256
#define TEMP_SIZE 2048

#include <glib.h>
#include <stdlib.h>

typedef struct {
	unsigned int ntype;
	char *type;
	unsigned int nmean;
	char *mean;
} WordInfo;

void find_meaning_put_gui( char *str );
void put_hash_table( GHashTable *hash, char *key, WordInfo *wss );
GHashTable *generate_hash_table( gchar *filename );

#endif
