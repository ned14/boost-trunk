/*
 * Copyright 1993-2002 Christopher Seiwald and Perforce Software, Inc.
 *
 * This file is part of Jam - see jam.c for Copyright information.
 */

/*  This file is ALSO:
 *  (C) Copyright David Abrahams 2001. Permission to copy, use,
 *  modify, sell and distribute this software is granted provided this
 *  copyright notice appears in all copies. This software is provided
 *  "as is" without express or implied warranty, and with no claim as
 *  to its suitability for any purpose.
 */

/*
 * filesys.h - OS specific file routines 
 */

typedef void (*scanback)( void *closure, char *file, int found, time_t t );

<<<<<<< variant A
#ifndef FILESYS_DWA20011025_H
# define FILESYS_DWA20011025_H

# include "strings.h"

typedef struct _filename FILENAME;
typedef struct _filepart FILEPART;

struct _filepart {
	char	*ptr;
	int	len;
};

struct _filename {
	FILEPART	part[6];
# ifdef OS_VMS
	int		parent;
# endif

# define f_grist	part[0]
# define f_root		part[1]
# define f_dir		part[2]
# define f_base		part[3]
# define f_suffix	part[4]
# define f_member	part[5]

} ;

void file_build( FILENAME *f, string *file, int binding );
void file_build1( FILENAME *f, string *file );

void file_parse( char *file, FILENAME *f );
void file_parent( FILENAME *f );

void file_dirscan( char *dir, void (*func)( char *f, int s, time_t t ) );
void file_archscan( char *arch, void (*func)( char *f, int s, time_t t ) );
>>>>>>> variant B
void file_dirscan( char *dir, scanback func, void *closure );
void file_archscan( char *arch, scanback func, void *closure );
####### Ancestor
typedef struct _filename FILENAME;
typedef struct _filepart FILEPART;

struct _filepart {
	char	*ptr;
	int	len;
};

struct _filename {
	FILEPART	part[6];
# ifdef OS_VMS
	int		parent;
# endif

# define f_grist	part[0]
# define f_root		part[1]
# define f_dir		part[2]
# define f_base		part[3]
# define f_suffix	part[4]
# define f_member	part[5]

} ;

void file_build( FILENAME *f, char *file, int binding );
void file_parse( char *file, FILENAME *f );
void file_parent( FILENAME *f );

void file_dirscan( char *dir, void (*func)( char *f, int s, time_t t ) );
void file_archscan( char *arch, void (*func)( char *f, int s, time_t t ) );
======= end

int file_time( char *filename, time_t *time );

#endif // FILESYS_DWA20011025_H
