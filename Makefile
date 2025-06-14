# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/03 13:03:04 by macauchy          #+#    #+#              #
#    Updated: 2025/06/02 12:25:09 by macauchy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET	= \033[0m
BOLD	= \033[1m
RED		= \033[31m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m
CYAN	= \033[36m

FILES		=	singleton.c exec.c parsing.c pipe.c redir.c utils.c path.c
NO_BONUS	=	pipex.c
YES_BONUS	=	pipex_bonus.c
SRC_DIR		=	srcs
SRCS		=	$(addprefix $(SRC_DIR)/, $(FILES))
NO_BONUS_SRCS	=	$(addprefix $(SRC_DIR)/, $(NO_BONUS))
YES_BONUS_SRCS	=	$(addprefix $(SRC_DIR)/, $(YES_BONUS))
OBJ_DIR			=	.objs
OBJS			=	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
NO_BONUS_OBJS	=	$(addprefix $(OBJ_DIR)/, $(NO_BONUS:.c=.o))
YES_BONUS_OBJS	=	$(addprefix $(OBJ_DIR)/, $(YES_BONUS:.c=.o))
INCLUDE			=	includes/pipex.h

NAME	=	pipex
CC		=	cc
CFLAGS	=	-g3 -Wall -Wextra -Werror
DEBUG	=	-fsanitize=address
RM		=	/bin/rm -rf
LDFLAGS	=	 -Llibft -lft

all:		$(NAME)

$(NAME):	$(OBJS) $(NO_BONUS_OBJS)
		@$(MAKE) -C libft -q --no-print-directory || (echo "$(BLUE)[Libft]$(RESET) Compiling libft" && $(MAKE) -C libft -j > /dev/null 2>&1)
		@echo "$(GREEN)[libft OK]$(RESET)"
		@echo "$(BOLD)$(CYAN)[Link]$(RESET) $(NAME)"
		@$(CC) $(CFLAGS) $(OBJS) $(NO_BONUS_OBJS) $(LDFLAGS) -o $(NAME)
		@echo "$(GREEN)Build complete.$(RESET)"

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(INCLUDE)
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(CFLAGS) -c $< -o $@
		@echo "$(YELLOW)[Compiling]$(RESET) $<"

bonus:	$(OBJS) $(YES_BONUS_OBJS)
	@$(MAKE) -C libft -q --no-print-directory || (echo "$(BLUE)[Libft]$(RESET) Compiling libft" && $(MAKE) -C libft -j > /dev/null 2>&1)
	@echo "$(GREEN)[libft OK]$(RESET)"
	@echo "$(BOLD)$(CYAN)[Link]$(RESET) $(NAME)"
	@$(CC) $(CFLAGS) $(OBJS) $(YES_BONUS_OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Build complete.$(RESET)"

debug:	fclean $(OBJS)
		@$(MAKE) -C libft -q --no-print-directory || (echo "$(BLUE)[Libft]$(RESET) Compiling libft" && $(MAKE) -C libft -j > /dev/null 2>&1)
		@$(CC) $(CFLAGS) $(DEBUG) $(OBJS) $(LDFLAGS) -o $(NAME)
		@echo "$(GREEN)[$(NAME) OK (DEBUG MODE)]$(RESET)"
	
clean:
		@$(MAKE) -C libft clean > /dev/null 2>&1
		@$(RM) $(OBJ_DIR)
		@echo "$(YELLOW)[cleaning $(NAME)]$(RESET)"

fclean: clean
		@$(MAKE) -C libft fclean > /dev/null 2>&1
		@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus debug
