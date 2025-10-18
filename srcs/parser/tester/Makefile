# Libft
LIBFT_DIR = ../../../libs/Libft-2.1.1
LIBFT_HEADER_DIR = $(LIBFT_DIR)/include
LIBFT = $(LIBFT_DIR)/libft.a

SOURCE_DIR = ..
OBJS_DIR = ..
LOCAL_HEADER_DIR = ..
LOCAL_HEADER = local_tokenizer.h
HEADER_DIR = ../../../include
HEADER = tokenizer.h

CFILES = $(SOURCE_DIR)/fn_helpers.c $(SOURCE_DIR)/fn_token_lists.c \
		$(SOURCE_DIR)/tokenizer.c $(SOURCE_DIR)/fn_crawl.c tester.c
		
OBJS = $(CFILES:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I $(LIBFT_HEADER_DIR) -I $(HEADER_DIR) -I $(LOCAL_HEADER_DIR) -g

all : test

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

test : $(OBJS) $(LIBFT)
	cc $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o test

$(OBJS_DIR)/%.o: ../%.c $(HEADER) $(LOCAL_HEADER)
	cc $(CFLAGS) -c $< -L$(LIBFT_DIR) -lft -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f test
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all