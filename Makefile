# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/13 12:35:12 by gajanvie          #+#    #+#              #
#    Updated: 2025/11/26 09:57:10 by gajanvie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
NAME_BONUS = fdf_bonus
SRCD = src/
OBJDIR      = objs/
LIBFT = ./src/libft/libft.a
GREEN=\033[0;32m
YELLOW=\033[0;33m
RED=\033[0;31m
BLUE=\033[0;34m
PURPLE=\033[0;35m
NC=\033[0m
LIB = MacroLibX
LIB_URL = https://github.com/seekrs/MacroLibX.git

SRCS = $(SRCD)fdf.c \
	$(SRCD)algo_line.c \
	$(SRCD)check_map.c \
	$(SRCD)clean_map.c \
	$(SRCD)draw_lines.c \
	$(SRCD)draw_points.c \
	$(SRCD)events_funcs_manda.c \
	$(SRCD)find_color.c \
	$(SRCD)matrices_iso.c \
	$(SRCD)matrices_parallel.c \
	$(SRCD)matrices_rotates.c \
	$(SRCD)matrices_utils.c \
	$(SRCD)pars.c \
	$(SRCD)pars_utils.c \
	$(SRCD)rand_colors.c \
	$(SRCD)set_data.c \
	$(SRCD)lerp_colors.c \
	$(SRCD)menue.c \
	$(SRCD)calculate_sphere.c

SRCS_BONUS = $(SRCD)fdf.c \
	$(SRCD)algo_line.c \
	$(SRCD)check_map.c \
	$(SRCD)clean_map.c \
	$(SRCD)draw_lines.c \
	$(SRCD)draw_points.c \
	$(SRCD)events_funcs.c \
	$(SRCD)find_color.c \
	$(SRCD)matrices_iso.c \
	$(SRCD)matrices_parallel.c \
	$(SRCD)matrices_rotates.c \
	$(SRCD)matrices_utils.c \
	$(SRCD)pars.c \
	$(SRCD)pars_utils.c \
	$(SRCD)rand_colors.c \
	$(SRCD)set_data.c \
	$(SRCD)lerp_colors.c \
	$(SRCD)menue.c \
	$(SRCD)calculate_sphere.c

OBJS = $(SRCS:$(SRCD)%.c=$(OBJDIR)%.o)
OBJS_BONUS = $(SRCS_BONUS:$(SRCD)%.c=$(OBJDIR)%.o)

CC = clang
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g -I ./include
MLX_DIR = MacroLibX
MLX = $(MLX_DIR)/libmlx.so

all: $(LIB) $(NAME) banner

banner :
	@printf "$(PURPLE)fdf$(NC)\n"
	@printf "$(GREEN)_____$(NC)$(RED)/\\/\\/\\/\\/\\/$(NC)$(GREEN)___$(NC)$(RED)/\\/\\/\\/\\/$(NC)$(GREEN)______$(NC)$(RED)/\\/\\/\\/\\/\\/$(NC)$(GREEN)____$(NC)\n"
	@printf "$(GREEN)____$(NC)$(RED)/\\/$(NC)$(GREEN)___________$(NC)$(RED)/\\/$(NC)$(GREEN)_____$(NC)$(RED)/\\/$(NC)$(GREEN)____$(NC)$(RED)/\\/$(NC)$(GREEN)____________$(NC)\n"
	@printf "$(GREEN)___$(NC)$(RED)/\\/\\/\\/\\/$(NC)$(GREEN)_____$(NC)$(RED)/\\/$(NC)$(GREEN)_____$(NC)$(RED)/\\/$(NC)$(GREEN)____$(NC)$(RED)/\\/\\/\\/\\/$(NC)$(GREEN)______$(NC)\n"
	@printf "$(GREEN)__$(NC)$(RED)/\\/$(NC)$(GREEN)___________$(NC)$(RED)/\\/$(NC)$(GREEN)_____$(NC)$(RED)/\\/$(NC)$(GREEN)____$(NC)$(RED)/\\/$(NC)$(GREEN)____________$(NC)\n"
	@printf "$(GREEN)_$(NC)$(RED)/\\/$(NC)$(GREEN)___________$(NC)$(RED)/\\/\\/\\/\\/$(NC)$(GREEN)______$(NC)$(RED)/\\/$(NC)$(GREEN)____________$(NC)\n"
	@printf "$(GREEN)____________________________________________$(NC)\n"

bonus: $(LIB) $(NAME_BONUS) banner

$(NAME): src/libft/libft.a $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -lSDL2 -lm -o $(NAME)
	@echo "$(GREEN)✅ Compilation of fdf finished !$(NC)"

$(NAME_BONUS): src/libft/libft.a $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(MLX) -lSDL2 -lm -o $(NAME_BONUS)
	@echo "$(GREEN)✅ Compilation of fdf with bonus finished !$(NC)"

$(LIB):
	@git clone https://github.com/seekrs/MacroLibX.git -b v2.2.2 MacroLibX --depth=1
	@$(MAKE) --no-print-directory -C MacroLibX -j
	@echo "$(GREEN)✅ Importation of MacroLibX finished!$(NC)"

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
	@rm -rf $(LIB)
	@echo "$(RED)🧨 libft.a and fdf deleted and MacroLibX$(NC)"

re:		fclean all

re_bonus:	fclean bonus

.PHONY: all clean fclean re libft banner re_bonus bonus