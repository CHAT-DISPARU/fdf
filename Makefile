# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/13 12:35:12 by gajanvie          #+#    #+#              #
#    Updated: 2025/11/14 11:55:18 by gajanvie         ###   ########.fr        #
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

CC = clang
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g -I ./include
MLX_DIR = MacroLibX
MLX = $(MLX_DIR)/libmlx.so

all: $(NAME) banner

banner :
	@printf "$(PURPLE)fdf$(NC)\n"
	@printf "$(GREEN)_____$(NC)$(RED)/\\/\\/\\/\\/\\/$(NC)$(GREEN)___$(NC)$(RED)/\\/\\/\\/\\/$(NC)$(GREEN)______$(NC)$(RED)/\\/\\/\\/\\/\\/$(NC)$(GREEN)____$(NC)\n"
	@printf "$(GREEN)____$(NC)$(RED)/\\/$(NC)$(GREEN)___________$(NC)$(RED)/\\/$(NC)$(GREEN)_____$(NC)$(RED)/\\/$(NC)$(GREEN)____$(NC)$(RED)/\\/$(NC)$(GREEN)____________$(NC)\n"
	@printf "$(GREEN)___$(NC)$(RED)/\\/\\/\\/\\/$(NC)$(GREEN)_____$(NC)$(RED)/\\/$(NC)$(GREEN)_____$(NC)$(RED)/\\/$(NC)$(GREEN)____$(NC)$(RED)/\\/\\/\\/\\/$(NC)$(GREEN)______$(NC)\n"
	@printf "$(GREEN)__$(NC)$(RED)/\\/$(NC)$(GREEN)___________$(NC)$(RED)/\\/$(NC)$(GREEN)_____$(NC)$(RED)/\\/$(NC)$(GREEN)____$(NC)$(RED)/\\/$(NC)$(GREEN)____________$(NC)\n"
	@printf "$(GREEN)_$(NC)$(RED)/\\/$(NC)$(GREEN)___________$(NC)$(RED)/\\/\\/\\/\\/$(NC)$(GREEN)______$(NC)$(RED)/\\/$(NC)$(GREEN)____________$(NC)\n"
	@printf "$(GREEN)____________________________________________$(NC)\n"

$(NAME): src/libft/libft.a $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -lSDL2 -o $(NAME)
	@echo "$(GREEN)✅ Compilation of fdf finished !$(NC)"

$(OBJDIR)%.o: $(SRCD)%.c
	@mkdir -p objs/
	@$(CC) $(CFLAGS) -I MacroLibX/includes $< -c -o $@

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
