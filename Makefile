# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enena <enena@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/03 17:51:07 by enena             #+#    #+#              #
#    Updated: 2022/01/08 20:06:28 by enena            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = /bin/sh

.PHONY: all bonus bonus_build clean fclean re norme recl check_lib

CC				:=	gcc
NAME			:=	cub3D
BONUS_NAME		:=	cub3D_bonus
HDRS_DIR		:=	hdrs
HDRS_BONUS_DIR	:=	hdrs_bonus
SRCS_DIR		:=	srcs
OBJS_DIR		:=	objs

HEADERS			:=	defines.h structs.h

DIRS			:=	main
HEADERS			+=		cub3d.h
SRCS_FILE		:=		cub3d.c

DIRS			+=	bmp_utils
HEADERS			+=		bmp_utils.h
SRCS_FILE		+=		bmp_utils.c\
						naming_utils.c\
						do_bmp.c

DIRS			+=	error_handling
HEADERS			+=		error_handling.h
SRCS_FILE		+=		error_handling.c\
						free_utils.c

DIRS			+=	general
HEADERS			+=		general.h
SRCS_FILE		+=		game.c\
						key_work.c\
						raycast.c\
						react_keys_part_1.c\
						react_keys_part_2.c

DIRS			+=	initialization
HEADERS			+=		initialization.h
SRCS_FILE		+=		check_junk.c\
						game_master_init.c\
						images.c\
						keys_init.c\
						map_convert_utils.c\
						map_init.c\
						parser.c\
						read_part_with_analyzer.c\
						render_init.c\
						setters_settings.c\
						settings_linker_init.c

DIRS			+=	instruments
HEADERS			+=		instruments.h
SRCS_FILE		+=		algebra_part_1.c\
						common_things_part_1.c\
						drawning.c\
						wall_calculate.c

BONUS_DIRS		+=	sprite

HEADERS_BONUS	+=	sprite_bonus.h

SRCS_BONUS_FILE	+=	anime_bonus.c\
					quick_sort_sprite_bonus.c\
					sprite_calculate_bonus.c\
					collision_bonus.c\
					map_bonus.c\
					mouse_bonus.c\
					react_keys_part_3_bonus.c

HEADERS_BONUS 	+=	$(HEADERS:%.h=%_bonus.h)
SRCS_BONUS_FILE	+=	$(SRCS_FILE:%.c=%_bonus.c)
OBJS_FILE		:=	$(addprefix $(OBJS_DIR)/,$(SRCS_FILE:%.c=%.o))
OBJS_BONUS_FILE	:=	$(addprefix $(OBJS_DIR)/,$(SRCS_BONUS_FILE:%.c=%.o))
LIBS_NAME		:=	mlx ft
LIBS_DIRS		:=	$(addprefix lib,$(LIBS_NAME))
LIBS_FILE		:=	$(addsuffix .a,$(addprefix lib,$(LIBS_NAME)))
LIB_LINK		=	$(addprefix -l,$(LIB)) $(addprefix -Llib,$(LIB))
LIBS_LINK		:=	$(foreach LIB,$(LIBS_NAME),$(LIB_LINK)) -lz
FRM				:=	-framework OpenGL -framework AppKit
FLAGS			:=	-Wall -Wextra -Werror
SRCS_PATH		:=	$(addprefix $(SRCS_DIR)/,$(DIRS))
SRCS_BONUS_PATH	:=	$(addprefix $(addsuffix _bonus, $(SRCS_DIR))/,$(DIRS) $(BONUS_DIRS))

vpath %.c $(SRCS_PATH) $(SRCS_BONUS_PATH)
vpath %.h $(HDRS_DIR) $(HDRS_BONUS_DIR)
vpath %.a $(LIBS_DIRS)

#color things
RED = \033[31m
GREEN = \033[32m
PURPLE = \033[35m
NC = \033[0m

all: $(NAME)

bonus: $(BONUS_NAME)

check:
	@echo $(LIBS_FILE)

$(NAME): $(LIBS_FILE) $(OBJS_FILE)
	$(CC) $(filter %.o, $^) $(FLAGS) -I$(HDRS_DIR) $(LIBS_LINK) $(FRM) -o $@
	@echo "$(PURPLE)Build all $(GREEN)objects files $(PURPLE)in $(GREEN)$(NAME).$(NC)"

$(BONUS_NAME): $(LIBS_FILE) $(OBJS_BONUS_FILE)
	$(CC) $(filter %.o, $^) $(FLAGS) -I$(HDRS_BONUS_DIR) $(LIBS_LINK) $(FRM) -o $@
	@echo "$(PURPLE)Build all $(GREEN)objects files $(PURPLE)in $(GREEN)$(NAME).$(NC)"

$(LIBS_FILE): check_lib

check_lib:
	@echo "$(PURPLE)Checking $(RED)libft.$(NC)"
	@make bonus -C libft
	@echo "$(PURPLE)Checking $(RED)libmlx.$(NC)"
	@make -C libmlx

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@echo "$(PURPLE)Create folder for object files.$(NC)"

$(OBJS_DIR)/%_bonus.o: %_bonus.c $(LIBS_FILE) $(HEADERS_BONUS) | $(OBJS_DIR) 
	$(CC) -c $< $(FLAGS) -I$(HDRS_BONUS_DIR) $(addprefix -I,$(LIBS_DIRS)) -o $@
	@echo "✅ $@"

$(OBJS_DIR)/%.o: %.c $(LIBS_FILE) $(HEADERS) | $(OBJS_DIR) 
	$(CC) -c $< $(FLAGS) -I$(HDRS_DIR) $(addprefix -I,$(LIBS_DIRS)) -o $@
	@echo "✅ $@"

clean:
	@make clean -C libft
	@make clean -C libmlx
ifeq (,$(wildcard $(OBJS_DIR)))
	@echo "$(GREEN)Objects files $(NAME)$(NC) already removed."
else
	@rm -rf $(OBJS_DIR)
	@echo "$(PURPLE)Remove $(RED)objects files $(NAME)$(NC)"
	@echo "$(GREEN)Done.$(NC)"
endif

fclean: clean
	@make fclean -C libft
	@make fclean -C libmlx
ifeq (,$(wildcard $(NAME)))
	@echo "$(GREEN)$(NAME)$(NC) already removed."
else
	@rm -f $(NAME)
	@rm -f $(BONUS_NAME)
	@echo "$(PURPLE)Remove $(RED)$(NAME)$(NC)"
	@echo "$(GREEN)Done.$(NC)"
endif

re: fclean all

norme:
	@make norme -C libft
	@echo "$(PURPLE)CHECK THE NORM FOR $(RED)$(NAME)$(NC)"
	@norminette $(SRCS_PATH)
	@norminette $(HDRS_DIR)
	@norminette $(SRCS_BONUS_PATH)

recl:
	@make re && make clean

%:
	@echo "Can't find rule for target $@"
