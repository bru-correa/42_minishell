/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramondo <jramondo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:33:19 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/13 05:38:43 by bcorrea-         ###   ########.fr       */
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
# include <signal.h>
# include <wait.h>
# include "libft.h"
# include "errno.h"
# include "limits.h"

/********** MACROS **********/

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

// Use for error checking
# define SUCCESS 1
# define FAILURE 0

// Use for exec and redirect functions
# define CHILD_ID 0
# define IN 0
# define OUT 1
# define ERROR -1

// Token types
# define T_UNDEFINED 0
# define T_RDIR_IN 1
# define T_RDIR_OUT 2
# define T_RDIR_APPEND 3
# define T_RDIR_HERE 4
# define T_PIPE 5
# define T_ARG 6

// Heredoc path
# define HDOC_TMPFILE "/tmp/heredoc"

/********** STRUCTS **********/

// Singly linked list
typedef struct s_slist
{
	char			*data;
	int				type;
	struct s_slist	*next;
}	t_slist;

typedef struct s_cmd
{
	char	**args;
	t_slist	**rdir_list;
}	t_cmd;

typedef struct s_pipeline
{
	int		default_fd[2];
	int		cmd_count;
	t_cmd	**cmds;
}	t_pipeline;

// Store the environment variables in (k,v) pairs
typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

/********** GLOBAL VAR **********/

extern int	g_exit_status;

/********** PROTOTYPES **********/

/**
 * Prompt the user for input, add it to to readline history,
 * parse the given input and try to execute the created pipeline.
 * After executing the pipeline, it will redisplay the prompt.
**/
void		repl(t_env_var **env_list);

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

/**
 * Remove `node` from `list`, set next to NULL and return it
**/
t_slist		*pop_slist_node(t_slist **list, t_slist *node);

/**
 * Append `node` to `list`. Return `node`
**/
t_slist		**append_node_to_slist(t_slist **list, t_slist *node);

/**
 * Get all data from `list` and create an string array.
 * The last element of the array will be NULL.
 * Clear `list` after creating the array.
 * In case of error, return NULL
**/
char		**slist_to_str_array(t_slist **list);

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
 * Search for the variable `key` and return its value.
 * Return "" if `key` is not on the list
**/
char		*search_env_var(t_env_var **env_list, char *key);

/**
 * Create an env_list from the `envp` array.
 * Return NULL in case of error
**/
t_env_var	**create_env_with_envp(char **envp);

/**
 * Convert `env_list` into an array of strings.
 * Return NULL in case of error
**/
char		**get_env_array(t_env_var **env_list);

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
 * Create the the token list from `input` and expand them.
 * Return the token list, or NULL in case of error.
**/
t_slist		**create_token_list(char *input, t_env_var **env_list);

/**
 * Parse `input` to create a command list.
 * Return NULL in case of error
**/
t_pipeline	*parse_input(char *input, t_env_var **env_list);

/**
 * Create the cmd array and set the last element to NULL.
 * It extract all the elements from `token` to create the cmds.
 * Return the cmd array.
 * In case of error, return NULL.
**/
t_cmd		**create_cmds(t_slist **tokens, int cmd_count);

/**
 * Split the tokens in sub tokens until it finds NULL or '|',
 * then set `start_token` to the token after the split.
 * Return the sub tokens
**/
t_slist		**split_tokens(t_slist *start_token);

/**
 * Assign the type of each token in `tokens`.
 * It also deletes redirect operators from `tokens`.
**/
t_slist		**set_tokens_types(t_slist **tokens);

/********** PIPELINE **********/

/**
 * Create the command array from `tokens` and return the pipeline
 * In case of error, return NULL.
**/
t_pipeline	*create_pipeline(t_slist **tokens);

/**
 * Create a cmd by extracting the tokens from `tokens`,
 * until it reaches a T_PIPE token or NULL.
**/
t_cmd		*extract_next_cmd(t_slist **tokens);

/**
 * Free `pipeline` and all it's elements
**/
void		clear_pipeline(t_pipeline *pipeline);

/********** EXECUTE **********/

/**
 * Handle the redirections and execute the command pipeline.
 * All the commands will be executed in child processes asynchronously.
**/
void		exec_pipeline(t_pipeline *pipeline, t_env_var **env_list);

/**
 * Execute the last `cmd` in `pipeline`.
 * If `cmd` is not a builtin, it will set the exit signal.
**/
void		exec_last_cmd(t_cmd *cmd, t_pipeline *pipeline, t_env_var **env_list);

/**
 * Read $PATH and check if `cmd` executable exists.
 * If found, return the command path,
 * otherwise return NULL
**/
char		*get_cmd_path(char *cmd, char **envp);

/**
 * Execute `cmd` in a child process
**/
void		exec_cmd(t_cmd *cmd, t_env_var **env_list, t_pipeline *pipeline);

/**
 * Set `exit_status` to 127,
 * print the invalid cmd to stderr and exit the process
**/
void		exit_invalid_cmd(t_cmd *cmd, t_env_var **env_list,
				t_pipeline *pipeline);

/**
 * Iterate though all `rdirs` and do the proper redirect based on `rdir` types.
 * All the redirects replace the standard input/output file number
 * with the new file, except for heredoc,
 * that creates a .heredoc file in the current folder.
**/
int			redirect_list(t_slist **rdirs, t_pipeline *pipeline, t_env_var **env_list);

/**
 * Create a temporary file called .heredoc, then create a child process and run
 * readline, until the user input `delimiter`.
**/
int			handle_heredoc(char *delimiter, t_pipeline *pipeline, t_env_var **env_list);

/**
 * Free `pipeline` and `env_list` and exit the process
**/
void		exit_hdoc_process(int hdoc, t_pipeline *pipeline,
				t_env_var **env_list);

/**
 * Execute the command pipeline. If `pipeline` contains only one command,
 * it will run the builtin functions in the main process,
 * otherwise execute the commands in child processes asynchronously.
**/
void		execute(t_pipeline *pipeline, t_env_var **env_list);

/**
 * Handle all the redirections and execute `cmd`.
 * If `cmd` is a builtin function, run in the main process,
 * otherwise execute `cmd` in a child process
**/
void		exec_single_cmd(t_cmd *cmd, t_env_var **env_list, t_pipeline *pipeline);

/**
 * Check if the `cmd` is a valid builtin, if it is,
 * execute builtin and return 1, else return 0
**/
void		exec_builtin(t_cmd *cmd, t_env_var **env_list, t_pipeline *pipeline);

/**
 * Save STDIN and STDOUT in `default_fd`
**/
void		backup_default_fd(int *default_fd);

/**
 * Replace STDIN and STDOUT with `default_fd`
**/
void		restore_default_fd(int *default_fd);

// TODO: Document
void		set_pipe(int cmd_index, int cmd_count, int default_out);

// TODO: Document
int			wait_for_child(int child_pid);

// TODO: Document
void		wait_for_children(int *children_pid);

/********** BUILTINS **********/

/**
 * Check if the `cmd_name` is one of the builtin functions.
 * Return 1 if true, 0 if false
**/
int			is_builtin(char *cmd_name);

/**
 * Free `pipeline`, `env_list` and exit with code 0
**/
int			repl_exit(t_pipeline *pipeline, t_env_var **env_list);

/**
 * Print all the environment variables and return the status_code
**/
int			env(t_env_var **env_list);

/**
 * Print `cmd` args to stdout.
 * In case of flag -n,
 * print `cmd` args without a newline at the end.
 * Return the status_code
**/
int			echo(t_cmd *cmd);

/********** SIGNALS **********/

/**
 * Set exit status to 130 send an empty line to stdout
**/
void		interrupt_hdoc(int signum);

/**
 * Print warning message when heredoc receives CTRL+D
**/
void		print_hdoc_warning(char *delimiter);

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
 * Prints a message describing the value of errno and exit
**/
void		exit_perror(char *msg, int error_code);

/**
 * Get errno and print the error message,
 * caused by trying to open `filename`
**/
void		print_invalid_open(char *filename);

/**
 * Handle the prompt if changed the cwd
**/
char		*handle_prompt();

// TODO: Document
void		clear_all(t_pipeline *pipeline, t_env_var **env_list);

// TODO: Document
void		clear_fds(void);

/********** SIGNALS **********/

void	sig_setup_prompt(void);

void	sig_setup_exec(int pid);

void	sig_setup_heredoc(int pid);

void	sig_handle_prompt(int signal);

#endif
