/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bcorrea->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:33:19 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/18 17:31:18 by bcorrea-         ###   ########.fr       */
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

// Hashtable size
# define HT_SIZE 10

/********** STRUCTS **********/

// List of tokens split from the commandline
typedef struct s_token
{
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	int		args_count;
	int		input_count;
	int		output_cout;
	char	**args;
	char	**input_files;
	char	**output_files;
}	t_cmd;

// Store the environment variables in (k,v) pairs
typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

/********** Hashtable **********/

typedef struct s_ht_item
{
	char	*key;
	char	*value;
}	t_ht_item;

typedef struct s_hashtable
{
	t_ht_item	**items;
	int			size;
	int			count;
}	t_hashtable;

typedef struct s_ht_list
{
	t_ht_item		*item;
	struct s_node	*next;
}	t_ht_list;

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

//TODO: Needs documentation

void	exit_error_token(t_token *token_head);

/********** HASHTABLE **********/

// TODO: Needs documentation

// t_ht_item	*create_ht_item(char *key, char *value);
// t_hashtable	*create_hashtable(int size);
// void		free_ht_item(t_ht_item *item);
// void		free_hashtable(t_hashtable *table);
// int			hash(char *str);
// void		ht_insert(t_hashtable *table, char *key, char *value);
// char		*ht_search(t_hashtable *table, char *key);

/********** ENVIRONMENT VARIABLES **********/

/**
 * Create env_list and set the first element to NULL
 * Return NULL in case of error
**/
t_env_var	**create_env_list(void);

/**
 * Create env_var and assign next to NULL
 * Return NULL in case of error
**/
t_env_var	*create_env_var(char *key, char *value);


/**
 * Create an ev_var and append it to the end of list
 * Is the variable already existis, update its value with the new one
**/
t_env_var	**add_var_to_env(t_env_var **env_list, char *key, char *value);

/**
 * Free all the elements from list and free the list
**/
void		clear_env_list(t_env_var **env_list);

/**
 * Remove and free an env_var from the list
**/
t_env_var	**delete_env_var(t_env_var **env_list, char *key);

/**
 * Create an env_list from the `envp` array
 * Return NULL in case of error
**/
t_env_var	**create_env_with_envp(char **envp);

#endif
