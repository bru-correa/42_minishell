/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bcorrea->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:33:19 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/10/19 22:09:13 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/********** INCLUDES **********/

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
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

# define TK_PIPE 0
# define TK_INPUT 1
# define TK_OUTPUT 2
# define TK_APPEND 3
# define TK_HEREDOC 4
# define TK_WORD 5

/********** STRUCTS **********/

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
}	t_token;

/********** PROTOTYPES **********/

/**
  Create a new token and set next to NULL.
  In case of error, returns NULL
**/
t_token	*create_token(int type, char *value);

/**
  Add a new token to the end of the list.
  If `token` is NULL, `token` will be the newly created token.
  In case of error, free all the tokens and return NULL
**/
t_token	*add_token(t_token *token, int type, char *value);

/**
  Free the token list and return NULL
**/
t_token	*free_tokens(t_token *token);

// NOTE: Needs documentation
t_token	*get_tokens(char *cmdline);

#endif
