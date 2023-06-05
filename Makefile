# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epasquie <epasquie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 11:31:05 by jalevesq          #+#    #+#              #
#    Updated: 2023/06/05 11:14:53 by epasquie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

INC_DIR = include
SRCS_DIR = srcs
OBJS_DIR = objs

PARSING = parsing copy_map checker texture rgb map flood_fill color_texture reverse_map
RAYCASTING = raycasting main movement calcul graphic
UTILS = free error utils

SRCS = $(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
		$(addsuffix .c, $(addprefix srcs/raycasting/, $(RAYCASTING))) \
	  	$(addsuffix .c, $(addprefix srcs/utils/, $(UTILS)))

OBJS = $(addprefix ${OBJS_DIR}/, $(subst srcs/,,$(SRCS:.c=.o)))

LIBFT_PATH = libft
LIBFT_LIB = ${LIBFT_PATH}/libft.a
LIBFT_INC = ${LIBFT_PATH}/include

MLX_PATH = MLX42/build
MLX_LIB = ${MLX_PATH}/libmlx42.a
# Change this path for your homebrew path
MLX_INC = -Iinclude -lglfw -L"/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib"
# MLX_INC = -Iinclude -lglfw -L"/Users/${USER}/homebrew/opt/glfw/lib/"
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit

GREEN	= \033[32;1m
CYAN	= \033[36;1m
RED		= \033[0;31m
BOLD	= \033[1m
RESET	= \033[0m
MAGENTA	=\033[0;95m

all: ${MLX_LIB} ${LIBFT_LIB} ${NAME}

${MLX_LIB}:
	@cd MLX42 && cmake -B build
	@cmake --build ${MLX_PATH} -j4

${LIBFT_LIB}:
	@make -C ${LIBFT_PATH}

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	@mkdir -p ${@D}
	@${CC} ${CFLAGS} -I ${INC_DIR} -I ${LIBFT_INC} -c $< -o $@
	@echo "$(GREEN)Compiling: $<$(RESET)$(MAGENTA)              [OK]$(RESET)"

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} ${MLX_FLAGS} ${MLX_INC} ${OBJS} ${LIBFT_LIB} ${MLX_LIB} -o ${NAME}
	@echo "$(GREEN)Compilation terminé avec succès !"

clean:
	@make clean -C ${LIBFT_PATH}
	@make clean -C ${MLX_PATH}
	@${RM} ${OBJS_DIR}
	@echo "$(RED)$(BOLD)Nettoyage effectué avec succès !"

fclean:	clean
	@make fclean -C ${LIBFT_PATH}
	@make clean -C ${MLX_PATH}
	@${RM} ${NAME}

re: fclean all
	@echo "$(CYAN)Recompilation Terminé !"

.PHONY: all clean fclean re