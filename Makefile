# ********** MUTE MAKEFILE ********** #
ifndef VERBOSE
.SILENT:
endif

# ********** VARIABLES ********** #
RED					= \033[1;31m
YELLOW				= \033[1;33m
GREEN				= \033[1;32m
NOCOLOR				= \033[0m
DONE_MSG			= "$(GREEN)Done!$(NOCOLOR)"
COMPILING_MSG		= "$(YELLOW)Compiling...$(NOCOLOR)"
CLEANING_MSG		= "$(RED)Cleaning up...$(NOCOLOR)"

NAME				= minishell
CC					= cc
CFLAGS				= -Wall -Wextra -Werror -O0 -g3 -I$(LIBFT_DIR) -I$(INCLUDE_DIR)
CFLAGS_LIB			= -lft -L $(LIBFT_DIR) -lreadline

INCLUDE_DIR			= include
SRC_DIR				= src
OBJ_DIR				= obj
LIB_DIR				= lib
LIBFT_DIR			= lib/libft

FILENAMES			= builtins/env builtins/export builtins/echo
FILENAMES			+= builtins/exit builtins/cd builtins/pwd
FILENAMES			+= builtins/print_export builtins/unset
FILENAMES			+= parser/parse_input parser/set_tokens_types
FILENAMES			+= parser/create_tokens prompt/get_prompt_str
FILENAMES			+= prompt/goodbye prompt/prompt_input
FILENAMES			+= prompt/welcome prompt/repl
FILENAMES			+= pipeline/create_cmds pipeline/clear_pipeline
FILENAMES			+= pipeline/create_pipeline pipeline/extract_next_cmd
FILENAMES			+= tokenizer/get_delimiter tokenizer/get_tokens
FILENAMES			+= env_var/get_env_array env_var/add_var_to_env
FILENAMES			+= env_var/create_env_with_envp env_var/create_env
FILENAMES			+= env_var/delete_env env_var/search_env_var
FILENAMES			+= utils/toggle_quote utils/clear_all utils/clear_fds
FILENAMES			+= utils/check_var_name utils/exit_error utils/print_errno
FILENAMES			+= exec/exec_single_cmd exec/exec_builtin exec/execute
FILENAMES			+= exec/exec_last_cmd exec/is_builtin exec/get_cmd_path
FILENAMES			+= exec/exec_pipeline exec/default_fd exec/wait
FILENAMES			+= exec/exec_cmd lexical_analyzer/check_special
FILENAMES			+= lexical_analyzer/print_syntax_error
FILENAMES			+= lexical_analyzer/check_quotes
FILENAMES			+= lexical_analyzer/check_syntax_errors
FILENAMES			+= heredoc/exit_heredoc heredoc/print_hdoc_warning
FILENAMES			+= heredoc/handle_heredoc expansor/remove_quotes_utils
FILENAMES			+= expansor/expand_variables expansor/expand_variables_utils
FILENAMES			+= expansor/expand_tokens expansor/remove_quotes
FILENAMES			+= expansor/clear_empty_tokens slist/slist
FILENAMES			+= slist/slist_to_str_array slist/join_list
FILENAMES			+= slist/slist_utils signal/sig_setup signal/sig_handlers
FILENAMES			+= redirects/redirects redirects/set_pipe

# SRC_FILES			= $(shell find src/ -type f -name '*.c')
SRC_FILES			= $(foreach filename,$(FILENAMES),$(SRC_DIR)/$(filename).c)
OBJ_FILES			= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
MAIN				= minishell.c
VALGRIND			= valgrind --leak-check=full --show-leak-kinds=all
VALGRIND			+= --track-origins=yes --quiet --tool=memcheck
VALGRIND			+= --suppressions=readline.supp

# ********** RULES ********** #

all:				$(NAME)

$(NAME):			required
					$(CC) $(MAIN) $(OBJ_FILES) $(CFLAGS) $(CFLAGS_LIB) \
						-o $(NAME)
					echo $(DONE_MSG)

# Compile required src files
required:			compile_message $(OBJ_DIR) $(OBJ_FILES) libft

libft:
					$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
					mkdir -p $@

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					mkdir -p "$(@D)"
					$(CC) -c $< $(CFLAGS) -o $@

clean:
					echo $(CLEANING_MSG)
					rm -rf $(OBJ_DIR)
					$(MAKE) -C $(LIBFT_DIR) clean

fclean:				clean
					rm -f $(NAME)
					$(MAKE) -C $(LIBFT_DIR) fclean

re:					fclean all

re_bonus:			fclean bonus

compile_message:
					echo $(COMPILING_MSG)


# Add -g flag and change output to debug
setup_debug:
					$(eval NAME=debug)
					$(eval CFLAGS+=-g)

# Compile with -g flag and output the 'debug' file
debug:				clean setup_debug all compile_message

run:				all
					$(VALGRIND) ./$(NAME)

test:				all
					./tests/tests.sh

.PHONY:	all run clean fclean re re_bonus libft debug setup_debug
