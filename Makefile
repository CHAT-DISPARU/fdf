# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/13 12:35:12 by gajanvie          #+#    #+#              #
#    Updated: 2025/11/13 12:37:17 by gajanvie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRCD = src/
OBJDIR      = objs/
LIBFT = ./src/libft/libft.a
GREEN=\033[0;32m
YELLOW=\033[0;33m
RED=\033[0;31m
BLUE=\033[0;34m
PURPLE=\033[0;35m
NC=\033[0m

SRCS = $(SRCD)fdf.c

OBJS = $(SRCS:$(SRCD)%.c=$(OBJDIR)%.o)

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g -I ./include

all: $(NAME) banner

banner :
	@echo "$(BLUE)"
	@echo "FDF"
	@echo "$(NC)"

$(NAME): src/libft/libft.a $(OBJS) $(OBJS_PRINTF) $(OBJS_GNL)
	@$(CC) $(CFLAGS) $(OBJS) $(OBJS_PRINTF) $(OBJS_GNL) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)✅ Compilation of fdf finished !$(NC)"

$(OBJDIR)%.o: $(SRCD)%.c
	@mkdir -p objs/
	@$(CC) $(CFLAGS) $< -c -o $@

$(LIBFT):
	@make --no-print-directory -C src/libft
	@echo "$(GREEN)✅ Compilation of libft finished !$(NC)"

clean:
	@make --no-print-directory -C src/libft clean
	@rm -rf $(OBJDIR)
	@echo "$(YELLOW)🧹 file .o cleaned successfully $(NC)"

fclean: clean
	@make --no-print-directory -C src/libft fclean
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@echo "$(RED)🧨 libft.a and fdf deleted$(NC)"

re:		fclean all

.PHONY: all clean fclean re libft banner