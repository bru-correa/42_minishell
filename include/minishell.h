/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bcorrea->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:33:19 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/10/31 14:53:04 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/********** INCLUDES **********/

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

/********** MACROS **********/

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

// Used for error checking
# define SUCCESS 1
# define FAILURE 0

/********** STRUCTS **********/

/**
 * List of tokens split from the commandline
**/
typedef struct s_token
{
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**args;
	char			**input_files;
	char			**output_files;
	struct s_cmd	*next;
}	t_cmd;

/********** PROTOTYPES **********/

/**
  Create a new token and set next to NULL.
  In case of error, returns NULL
**/
t_token	*create_token(char *value);

/**
  Add a new token to the end of the list.
  If `token_head` is NULL, `token_head` will point to `token_new`.
  In case of error, return NULL
**/
t_token	*append_token(t_token *token_head, char *value);

/**
  Free the token list and return NULL
**/
t_token	*free_tokens(t_token *token_head);

/**
 * Split the command line in a list of tokens.
 * Return NULL in case of error.
**/
t_token	*get_tokens(char *cmdline);

/**
 * Check for delimiters in `index`.
 * If found, return the index of the delimiter, otherwise return -1
**/
int		get_delimiter_index(const char *cmdline, int current, int start);

/**
 * Return 0 if any errors were found, 1 if no errors were found.
 * Print in stderr the error message, in case of error.
**/
int		check_syntax_errors(t_token *token_head);

#endif
