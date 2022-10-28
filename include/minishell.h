/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bcorrea->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:33:19 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/10/28 19:41:45 by bcorrea-         ###   ########.fr       */
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

# define TK_PIPE 1
# define TK_INPUT 2
# define TK_OUTPUT 3
# define TK_APPEND 4
# define TK_HEREDOC 5
# define TK_CMD 6
# define TK_ARG 7

// Used for error checking
# define SUCCESS 0
# define FAILURE 1

/********** STRUCTS **********/

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char	*path;
	char	**args;
	char	*input_file;
	char	*output_file;
}	t_cmd;

/********** PROTOTYPES **********/

/**
  Create a new token and set next to NULL.
  In case of error, returns NULL
**/
t_token	*create_token(int type, char *value);

/**
  Add a new token to the end of the list.
  If `token_head` is NULL, `token_head` will point to `token_new`.
  In case of error, return NULL
**/
t_token	*append_token(t_token *token_head, int type, char *value);

/**
  Free the token list and return NULL
**/
t_token	*free_tokens(t_token *token_head);

// TODO: Document
t_token	*get_tokens(char *cmdline);

/**
 * Check for delimiters in `index`.
 * If found, return the index of the delimiter, otherwise return -1
**/
int		get_delimiter_index(const char *cmdline, int current, int start);

// TODO: Document
int		check_syntax_errors(t_token *token_head);

#endif
