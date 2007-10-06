/*
 * Copyright 1993, 1995 Christopher Seiwald.
 *
 * This file is part of Jam - see jam.c for Copyright information.
 */

/*
 * command.c - maintain lists of commands
 */

# include "jam.h"

# include "lists.h"
# include "parse.h"
# include "variable.h"
# include "rules.h"

# include "command.h"

/*
 * cmd_new() - return a new CMD or 0 if too many args
 */

CMD *
cmd_new(
	RULE	*rule,
	LIST	*targets,
	LIST	*sources,
	LIST	*shell )
{
	CMD *cmd = (CMD *)malloc( sizeof( CMD ) );

	cmd->rule = rule;
	cmd->shell = shell;
	cmd->next = 0;

	lol_init( &cmd->args );
	lol_add( &cmd->args, targets );
	lol_add( &cmd->args, sources );

	/* Bail if the result won't fit in MAXLINE */
	/* We don't free targets/sources/shell if bailing. */

	if( var_string( rule->actions, cmd->buf, MAXLINE, &cmd->args ) < 0 )
	{
	    cmd_free( cmd );
	    return 0;
	}

	return cmd;
}

/*
 * cmd_free() - free a CMD
 */

void
cmd_free( CMD *cmd )
{
	lol_free( &cmd->args );
	list_free( cmd->shell );
	free( (char *)cmd );
}
