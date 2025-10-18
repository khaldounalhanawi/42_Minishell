# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/07 15:25:57 by pecavalc          #+#    #+#              #
#    Updated: 2025/10/18 09:42:56 by kalhanaw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell 

SRCS_DIR = srcs
OBJS_DIR = objs

SRCS = $(addprefix $(SRCS_DIR)/, minishell.c \
								 signals.c)
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

HEADER_DIR = include
HEADER = $(HEADER_DIR)/minishell.h

# Parser
PARSER_SRCS_DIR = srcs/parser
PARSER_SRCS = $(addprefix $(PARSER_SRCS_DIR)/, fn_crawl.c \
											   fn_helpers.c \
											   fn_token_lists.c \
											   fn_expand_vars_utils.c \
											   fn_expand_vars.c \
											   fn_general_utils.c \
											   tokenizer.c)

PARSER_OBJS_DIR = objs/parser
PARSER_OBJS = $(patsubst $(PARSER_SRCS_DIR)/%.c, \
				$(PARSER_OBJS_DIR)/%.o, $(PARSER_SRCS))

PUB_PARSER_HEADER_DIR = include
LOCAL_PARSER_HEADER_DIR = $(PARSER_SRCS_DIR)
PARSER_HEADERS = $(PUB_PARSER_HEADER_DIR)/parser.h \
				 $(LOCAL_PARSER_HEADER_DIR)/local_parser.h

# Execute
EXECUTE_SRCS_DIR = srcs/execute
EXECUTE_SRCS = $(addprefix $(EXECUTE_SRCS_DIR)/,execute.c \
												fn_assign_input_output_utils.c \
												fn_assign_input_output.c \
												fn_built_in_I.c \
												fn_built_in_II.c \
												fn_get_full_path.c \
												fn_run_cmd.c \
												fn_utils.c)

EXECUTE_OBJS_DIR = objs/execute
EXECUTE_OBJS = $(patsubst $(EXECUTE_SRCS_DIR)/%.c, \
				$(EXECUTE_OBJS_DIR)/%.o, $(EXECUTE_SRCS))

PUB_EXECUTE_HEADER_DIR = include
LOCAL_EXECUTE_HEADER_DIR = $(EXECUTE_SRCS_DIR)
EXECUTE_HEADERS = $(PUB_EXECUTE_HEADER_DIR)/execute.h \
				 $(LOCAL_EXECUTE_HEADER_DIR)/local_execute.h

# Directories of all objects above - only used to create obj folders
OBJS_DIRS = $(OBJS_DIR) $(PARSER_OBJS_DIR) $(EXECUTE_OBJS_DIR)

# Libft
LIBFT_DIR = libs/Libft-2.1.1
LIBFT_HEADER_DIR = $(LIBFT_DIR)/include
LIBFT = $(LIBFT_DIR)/libft.a

# Mac
READLINE_PATH := $(shell brew --prefix readline)
LDFLAGS = -L$(READLINE_PATH)/lib -lreadline -lhistory
CPPFLAGS = -I$(READLINE_PATH)/include

CFLAGS = -Wall -Wextra -Werror -I$(HEADER_DIR) \
							   -I$(LOCAL_PARSER_HEADER_DIR) \
							   -I$(LOCAL_EXECUTE_HEADER_DIR) \
							   -I$(LIBFT_HEADER_DIR) \
							   -g

all: $(OBJS_DIRS) $(NAME)

# Create all obj folders beforehand
$(OBJS_DIRS):
	mkdir -p $@

# ***Mac edited ***
# Compile minishell
$(NAME): $(OBJS) $(PARSER_OBJS) $(LIBFT) $(EXECUTE_OBJS)
	cc $(CFLAGS) $(LDFLAGS) $(OBJS) $(PARSER_OBJS) $(EXECUTE_OBJS) $(LIBFT) -o $(NAME)

# ***Mac edited ***
# Build main objs in srcs
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER)
	cc $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

# Build parser objs 
$(PARSER_OBJS_DIR)/%.o: $(PARSER_SRCS_DIR)/%.c $(PARSER_HEADERS)
	cc $(CFLAGS) -c $< -o $@

# Build execute objs 
$(EXECUTE_OBJS_DIR)/%.o: $(EXECUTE_SRCS_DIR)/%.c $(EXECUTE_HEADERS)
	cc $(CFLAGS) -c $< -o $@

# Trigger Libft compilation
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	rm -rf $(OBJS_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all re clean fclean
