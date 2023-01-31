/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramondo <jramondo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:33:19 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/31 19:51:03 by jramondo         ###   ########.fr       */
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
# include <limits.h>
# include <string.h>
# include <signal.h>

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

// Heredoc path
# define HDOC_TMPFILE "/tmp/heredoc"

/********** STRUCTS **********/

// Singly linked list
typedef struct s_slist
{
	char			*data;
	struct s_slist	*next;
}	t_slist;

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

/********** PROTOTYPES **********/

/********** SINGLY LINKED LIST **********/

/**
 * Create a new singly linked list and set the first element to NULL
 * In case of error, return NULL
**/
t_slist		**create_slist(void);

/**
 * Create a node for 't_slist' with `data`.
 * In case of error, return NULL
**/
t_slist		*create_slist_node(char *data);

/**
 * Create a new node at the end of `list` with `data`
**/
t_slist		**append_to_slist(t_slist **list, char *data);

/**
 * Free `node` and return NULL
**/
t_slist		*free_slist_node(t_slist *node);

/**
 * Free all the nodes from `list`, free `list` and return NULL
**/
t_slist		**clear_slist(t_slist **list);

/**
 * Remove `node` from the list and free it
**/
t_slist		**delete_from_slist(t_slist **list, t_slist *node);

/**
 * Join all the strings from `list` and free `list` memory.
 * If the list empty, return an empty string
**/
char		*join_list(t_slist **list);

/********** TOKENIZER **********/

/**
 * Split the command line in a list of tokens.
 * Return NULL in case of error.
**/
t_slist		**get_tokens(char *cmdline);

/**
 * Check for delimiters in `index`.
 * If found, return the index of the delimiter, otherwise return -1
**/
int			get_delimiter_index(const char *cmdline, int current, int start);


/********** LEXICAL ANALYZER **********/

/**
 * Check for syntax errors in `tokens`.
 * Return 0 if any errors were found, 1 if no errors were found.
 * Print in stderr the error message, in case of error.
**/
int			check_syntax_errors(t_slist **tokens);

/**
 * Check for invalid special chars in `data`.
 * Return 0 if any errors were found, 1 if no errors were found.
 * Print in stderr the error message
**/
int			check_special_chars(char *data);

/**
 * Print the invalid token to STDERR
**/
void		print_syntax_error(char *invalid_data);

/**
 * Print the error to STDERR
**/
void		print_quote_error(void);

/**
 * Print the error with the invalid char `c` to STDERR
**/
void		print_special_char_error(char c);

/**
 * Return 1 if it finds unclosed quotes or 0 if not
**/
int			check_unclosed_quotes(char *data);

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
 * Search for the variable `key` and return its value
 * Return "" if `key` is not on the list
**/
char		*search_env_var(t_env_var **env_list, char *key);

/**
 * Create an env_list from the `envp` array
 * Return NULL in case of error
**/
t_env_var	**create_env_with_envp(char **envp);

/********** EXPANSOR **********/

/**
 * Expand all tokens that contain environment variables,
 * replacing $VAR_NAME with its value.
 * If the var doesn't exists, replace with an empty string
**/
t_slist		**expand_variables(t_slist **tokens, t_env_var **envl);

/**
 * Remove all tokens that contain data == "".
 * Return `token_head`
**/
t_slist		**clear_empty_tokens(t_slist **tokens);

/**
 * Expand all tokens that contain environment variables,
 * remove the quotes from the tokens and remove empty tokens.
 * Return NULL in case of error.
**/
t_slist		**expand_tokens(t_slist **tokens, t_env_var **env_list);

/**
 * Split `data` up to `length` bytes and expand the var.
 * Add both to `data_list`.
 * Return var name length
**/
int			expand_var_data(char *data, int length, t_slist **data_list,
				t_env_var **envl);

/**
 * Split `data` up to `length` bytes and add to data_list
 * Return `data_list`
**/
t_slist		**split_token_data(char *data, int length, t_slist **data_list);

/**
 * Remove quoted strings from `tokens`.
 * Return `tokens`
**/
t_slist		**remove_quotes(t_slist **tokens);

/**
 * Return the length of `data` until the first occurrence of quotes or '\0'
**/
int			get_next_quote(char *data);

/**
 * Return the length of the data inside quotes from `data`
**/
int			get_quote_length(char *data);

/********** PARSER **********/

/**
 * Parse `input` to create a command list.
 * Return NULL in case of error
**/
t_cmd		**parse_input(char *input, t_env_var **env_list);

/********** UTILS **********/

/**
 * Free the token list and exit the program
**/
void		exit_error_token(t_slist **tokens);

int			toggle_quote_state(int quote_state, char c, char quote_char);

/**
 * Toggle `squote` if `c` is '\'' or toggle `dquote` if `c` is '"'
**/
void		update_quote_state(char c, int *squote, int *dquote);

/**
 * Handle the prompt if changed the cwd
*/
char		*handle_prompt();

void    	set_signal(void (*handler)(int), int signal);

void    	sig_prompt(int signal);

void		sig_parent(int signal);

void 	   sig_child(int signal);

void		sig_heredoc_child(int signal);

void		sig_heredoc_parent(int signal);

void	    clean_process(void);

#endif
