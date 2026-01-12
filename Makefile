# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/07 15:25:57 by pecavalc          #+#    #+#              #
#    Updated: 2025/12/01 10:44:34 by pecavalc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell 

SRC_DIR = src
OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR)/, fn_signals.c fn_envp.c)
SRC_MAIN = $(addprefix $(SRC_DIR)/,minishell.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
OBJ_MAIN = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_MAIN))

HEADER_DIR = include
HEADER = $(HEADER_DIR)/signals.h $(HEADER_DIR)/envp.h

# Parser
PARSER_SRC_DIR = src/parser
PARSER_SRC = $(addprefix $(PARSER_SRC_DIR)/, fn_add_argv.c \
											 fn_build_cmd_lst.c \
											 fn_check_token_sequence.c \
											 fn_cmd_list.c \
											 fn_crawl.c \
											 fn_expand_tokens_utils.c \
											 fn_expand_tokens.c \
											 fn_general_utils.c \
											 fn_helpers.c \
											 fn_heredoc_execute.c \
											 fn_heredoc_prepare.c \
											 fn_token_lists.c \
											 fn_tokenizer.c \
											 parse.c)

PARSER_OBJ_DIR = obj/parser
PARSER_OBJ = $(patsubst $(PARSER_SRC_DIR)/%.c, \
				$(PARSER_OBJ_DIR)/%.o, $(PARSER_SRC))

PUB_PARSER_HEADER_DIR = include
LOCAL_PARSER_HEADER_DIR = $(PARSER_SRC_DIR)
PARSER_HEADERS = $(PUB_PARSER_HEADER_DIR)/parser.h \
				 $(LOCAL_PARSER_HEADER_DIR)/local_parser.h

# Execute
EXECUTE_SRC_DIR = src/execute
EXECUTE_SRC = $(addprefix $(EXECUTE_SRC_DIR)/,execute.c \
												fn_assign_input_output.c \
												fn_get_full_path.c \
												fn_run_builtin_in_parent.c \
												fn_run_cmd.c \
												fn_create_process_id_arr.c \
												fn_loop_pids.c \
												fn_utils.c)

EXECUTE_OBJ_DIR = obj/execute
EXECUTE_OBJ = $(patsubst $(EXECUTE_SRC_DIR)/%.c, \
				$(EXECUTE_OBJ_DIR)/%.o, $(EXECUTE_SRC))

PUB_EXECUTE_HEADER_DIR = src/execute
LOCAL_EXECUTE_HEADER_DIR = $(EXECUTE_SRC_DIR)
EXECUTE_HEADERS = $(PUB_EXECUTE_HEADER_DIR)/execute.h \
				 $(LOCAL_EXECUTE_HEADER_DIR)/local_execute.h

# built_in
BUILTIN_SRC_DIR = src/builtin
BUILTIN_SRC = $(addprefix $(BUILTIN_SRC_DIR)/, fn_built_in_cd.c \
												fn_built_in_cd_update_env.c \
												fn_built_in_env.c \
												fn_built_in_unset_I.c \
												fn_built_in_unset_II.c \
												fn_built_in_export_I.c \
												fn_built_in_export_II.c \
												fn_built_in_export_III.c \
												fn_built_in_pwd.c \
												fn_quick_sort.c \
												fn_builtin_echo.c \
												fn_builtin_exit.c \
												search_builtin_functions.c)

BUILTIN_OBJ_DIR = obj/builtin
BUILTIN_OBJ = $(patsubst $(BUILTIN_SRC_DIR)/%.c, \
				$(BUILTIN_OBJ_DIR)/%.o, $(BUILTIN_SRC))

PUB_BUILTIN_HEADER_DIR = include
LOCAL_BUILTIN_HEADER_DIR = $(BUILTIN_SRC_DIR)
BUILTIN_HEADERS = $(PUB_BUILTIN_HEADER_DIR)/builtin.h \
				 $(LOCAL_BUILTIN_HEADER_DIR)/local_builtin.h

# Directories of all objects above - only used to create obj folders
OBJ_DIRS = $(OBJ_DIR) $(PARSER_OBJ_DIR) $(EXECUTE_OBJ_DIR) $(BUILTIN_OBJ_DIR)

# Libft
LIBFT_DIR = libs/Libft-2.1.1
LIBFT_HEADER_DIR = $(LIBFT_DIR)/include
LIBFT = $(LIBFT_DIR)/libft.a

# For Mac OS compatibility
READLINE_PATH := $(shell brew --prefix readline)
LDFLAGS = -L$(READLINE_PATH)/lib -lreadline -lhistory
CPPFLAGS = -I$(READLINE_PATH)/include

CFLAGS = -g -Wall -Wextra -Werror -I$(HEADER_DIR) \
								  -I$(LOCAL_PARSER_HEADER_DIR) \
							   	  -I$(LIBFT_HEADER_DIR) \
							   	  -I$(LOCAL_EXECUTE_HEADER_DIR) \
							   	  -I$(LOCAL_BUILTIN_HEADER_DIR)LOCAL_EXECUTE_HEADER_DIR

all: $(OBJ_DIRS) $(NAME)

# Create all obj folders beforehand
$(OBJ_DIRS):
	mkdir -p $@

# Compile minishell
$(NAME): $(OBJ) $(PARSER_OBJ) $(LIBFT) $(OBJ_MAIN) \
		 $(EXECUTE_OBJ) $(BUILTIN_OBJ)
	cc $(CFLAGS) $(LDFLAGS) $(OBJ) $(PARSER_OBJ) \
	   $(EXECUTE_OBJ) $(BUILTIN_OBJ) $(LIBFT) $(OBJ_MAIN) \
	   $(LDFLAGS) -o $(NAME)

# Build main obj in src
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	cc $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Build parser obj 
$(PARSER_OBJ_DIR)/%.o: $(PARSER_SRC_DIR)/%.c $(PARSER_HEADERS)
	cc $(CFLAGS) -c $< -o $@

# Build execute obj 
$(EXECUTE_OBJ_DIR)/%.o: $(EXECUTE_SRC_DIR)/%.c $(EXECUTE_HEADERS)
	cc $(CFLAGS) -c $< -o $@

# Build builtin obj 
$(BUILTIN_OBJ_DIR)/%.o: $(BUILTIN_SRC_DIR)/%.c $(BUILTIN_HEADERS)
	cc $(CFLAGS) -c $< -o $@
	
# Trigger Libft compilation
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Valgrind rules
valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	--suppressions=readline_suppress.supp ./$(NAME)
valchild: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	--track-fds=yes --trace-children=yes --suppressions=readline_suppress.supp ./$(NAME)

# --------------------------------------------------------------------------- #
# 								UNIT TESTS									  #
# --------------------------------------------------------------------------- #

TEST_DIR = test
TEST_SRC_DIR = $(TEST_DIR)/src
TEST_OBJ_DIR = $(TEST_DIR)/obj

# Create obj folder - ensure this is a dependency in the targets below
$(TEST_OBJ_DIR):
	mkdir -p $@

# NORMINETTE
test_norm:
	norminette -R CheckForbiddenHeaderSource \
	$(SRC_DIR) $(HEADER_DIR) $(LIBFT_DIR)/srcs $(LIBFT_DIR)/include

# PARSER TESTS

# 1: test_check_token_sequence
TEST_1_NAME	= test_check_token_sequence
TEST_1_SRC 	= $(addprefix $(TEST_SRC_DIR)/, test_check_token_sequence.c)
TEST_1_OBJ 	= $(patsubst $(TEST_SRC_DIR)/%.c, $(TEST_OBJ_DIR)/%.o, \
			  $(TEST_1_SRC))

# Compile and run test 1
$(TEST_1_NAME): $(OBJ_DIRS) $(OBJ) $(PARSER_OBJ) $(NAME) $(LIBFT) \
				$(TEST_OBJ_DIR) $(TEST_1_OBJ)
	@cc $(CFLAGS) $(LDFLAGS) $(OBJ) $(PARSER_OBJ) $(LIBFT) $(TEST_1_OBJ) \
	   $(LDFLAGS) -o $(TEST_1_NAME)
	./$(TEST_1_NAME)

# 2: test_tokenizer
TEST_2_NAME = test_tokenizer
TEST_2_SRC = $(addprefix $(TEST_SRC_DIR)/, test_tokenizer.c)
TEST_2_OBJ = $(patsubst $(TEST_SRC_DIR)/%.c, $(TEST_OBJ_DIR)/%.o, \
			 $(TEST_2_SRC))

# Compile and run test 2
$(TEST_2_NAME): $(OBJ_DIRS) $(OBJ) $(PARSER_OBJ) $(NAME) $(LIBFT) \
				$(TEST_OBJ_DIR) $(TEST_2_OBJ)
	@cc $(CFLAGS) $(LDFLAGS) $(OBJ) $(PARSER_OBJ) $(LIBFT) $(TEST_2_OBJ) \
	   $(LDFLAGS) -o $(TEST_2_NAME)
	./$(TEST_2_NAME)

# 3: test_build_cmd_lst
TEST_3_NAME = test_build_cmd_lst
TEST_3_SRC = $(addprefix $(TEST_SRC_DIR)/, test_build_cmd_lst.c)
TEST_3_OBJ = $(patsubst $(TEST_SRC_DIR)/%.c, $(TEST_OBJ_DIR)/%.o, \
			 $(TEST_3_SRC))

# Compile and run test 3
$(TEST_3_NAME): $(LIBFT) $(OBJ_DIRS) $(OBJ) $(PARSER_OBJ) $(NAME) \
				$(TEST_OBJ_DIR) $(TEST_3_OBJ)
	@cc $(CFLAGS) $(LDFLAGS) $(OBJ) $(PARSER_OBJ) $(TEST_3_OBJ) \
		$(LIBFT) -o $(TEST_3_NAME)
	./$(TEST_3_NAME)

# Compile test objects
$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c
	cc $(CFLAGS) -c $< -o $@

test: 		test_norm $(TEST_1_NAME) $(TEST_2_NAME) $(TEST_3_NAME)
test_1: 	$(TEST_1_NAME)
test_2:		$(TEST_2_NAME)
test_3:		$(TEST_3_NAME)

# --------------------------------------------------------------------------- #
# 								CLEAN UP									  #
# --------------------------------------------------------------------------- #

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(TEST_OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_1_NAME)
	rm -f $(TEST_2_NAME)
	rm -f $(TEST_3_NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all test $(TEST_1_NAME) $(TEST_2_NAME) $(TEST_3_NAME) re clean fclean
