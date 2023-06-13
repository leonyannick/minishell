# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/19 09:17:44 by lbaumann          #+#    #+#              #
#    Updated: 2023/06/13 12:11:03 by aehrlich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = #-Wall -Werror -Wextra
MAKEFLAGS   += --no-print-directory

UNAME := $(shell uname)

ifeq ($(NOFLAGS), 1)
CFLAGS = 
endif

ifeq ($(DEBUG), 1)
CFLAGS = -g
all: fclean
endif

SRCDIR := srcs
INCDIR := includes
OBJDIR := objs
LIBFTDIR := libft

LEXDIR := $(SRCDIR)/lexer

# Colors
GR	= \033[32;1m
RE	= \033[31;1m
PU	= \033[35;1m
BL	= \033[34;1m3
RC	= \033[0m

HEADERS = -I $(INCDIR)

#libft
LIBFT = $(LIBFTDIR)/libft.a
LIBFTINCL = -L$(LIBFTDIR) -lft

LDFLAGS = -lreadline $(LIBFTINCL)

SRCS = \
	minishell.c \
	lexer/lexer.c \
	lexer/lexer_utils_helper_1.c \
	lexer/lexer_utils_helper_2.c \
	lexer/lexer_utils_postprocess.c \
	lexer/lexer_utils_token_1.c \
	lexer/lexer_utils_token_2.c \
	error/error.c \
	data_init.c \
	./parser/parser_utils_cmd.c \
	./parser/parser_print.c \
	./parser/parser.c \
	./parser/parser_utils.c \
	executor/executor_utils.c \
	executor/executor.c \
	executor/redirection.c \
	executor/command.c 

ifeq ($(UNAME), Linux)
endif
ifeq ($(UNAME), Darwin)
endif

SRCS		:= $(SRCS:%=$(SRCDIR)/%)
OBJS		:= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	$(info CREATED $(NAME))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<
	$(info CREATED $@)

$(LIBFT):
	if [ ! -d "libft" ]; then git clone https://github.com/leonyannick/libft.git; fi
	$(MAKE) -C $(LIBFTDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SILENT:
