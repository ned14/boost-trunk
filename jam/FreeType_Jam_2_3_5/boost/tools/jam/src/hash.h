/*
 * Copyright 1993, 1995 Christopher Seiwald.
 *
 * This file is part of Jam - see jam.c for Copyright information.
 */

/*
 * hash.h - simple in-memory hashing routines 
 */

typedef struct hashdata HASHDATA;

struct hash *	hashinit( int datalen, char *name );
int 		hashitem( struct hash *hp, HASHDATA **data, int enter );
void 		hashdone( struct hash *hp );

# define	hashenter( hp, data ) !hashitem( hp, data, !0 )
# define	hashcheck( hp, data ) hashitem( hp, data, 0 )
