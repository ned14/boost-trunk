/*
 * Copyright 1993-2002 Christopher Seiwald and Perforce Software, Inc.
 *
 * This file is part of Jam - see jam.c for Copyright information.
 */

/*
 * builtins.h - compile parsed jam statements
 */

void load_builtins();

LIST *builtin_depends( PARSE *parse, LOL *args );
LIST *builtin_echo( PARSE *parse, LOL *args );
LIST *builtin_exit( PARSE *parse, LOL *args );
LIST *builtin_flags( PARSE *parse, LOL *args );
LIST *builtin_glob( PARSE *parse, LOL *args );

