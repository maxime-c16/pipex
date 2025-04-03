# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/03 13:03:04 by macauchy          #+#    #+#              #
#    Updated: 2025/04/03 13:12:18 by macauchy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES	=	pipex.c singleton.c
SRC_DIR	=	srcs
SRCS	=	$(addprefix $(SRC_DIR)/, $(FILES))
OBJ_DIR	=	.objs
OBJS	=	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
INCLUDE	=	includes/pipex.h

NAME	=	pipex
CC		=	gcc
CFLAGS	=	-g3
DEBUG	=	-fsanitize=address
RM		=	/bin/rm -rf
LDFLAGS	=	 -Llibft -lft

all:		$(NAME)

$(NAME):	$(OBJS)
		@$(MAKE) -j -C libft 2>&1 > /dev/null
		@echo "\033[32m[libft OK]\033[0m"
		@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
		@echo "\033[32m[$(NAME) OK]\033[0m"

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(INCLUDE)
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(CFLAGS) -c $< -o $@
		@echo "\033[32m[$< OK]\033[0m"

debug:	fclean $(OBJS)
		@$(MAKE) -j -C libft 2>&1 > /dev/null
		@$(CC) $(CFLAGS) $(DEBUG) $(OBJS) $(LDFLAGS) -o $(NAME)
		@echo "\033[32m[$(NAME) OK (DEBUG MODE)]\033[0m"

clean:
		@$(MAKE) -C libft clean
		@$(RM) $(OBJ_DIR)
		@echo "\033[33m[cleaning $(NAME)]\033[0m"

fclean: clean
		@$(MAKE) -C libft fclean
		@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
