# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enena <enena@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/03 17:51:07 by enena             #+#    #+#              #
#    Updated: 2021/11/28 04:40:01 by enena            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = /bin/sh

.PHONY: all real clean fclean re norme recl 

CC:= gcc
NAME:=		cub3D
HDRS_DIR:=	hdrs
SRCS_DIR:=	srcs
OBJS_DIR:=	objs

HEADERS:=	defines.h structs.h

DIRS:=		main
HEADERS+=		cub3d.h
SRCS_FILE:=		cub3d.c

DIRS+=		bmp_utils
HEADERS+=		bmp_utils.h
SRCS_FILE+=		bmp_utils.c

DIRS+=		error_handling
HEADERS+=		error_handling.h
SRCS_FILE+=		error_handling.c\
				free_utils.c

DIRS+=		general
HEADERS+=		general.h
SRCS_FILE +=	game.c\
				key_work.c\
				react_keys_part_1.c\
				react_keys_part_2.c\
				do_bmp.c\
				raycast.c

DIRS+=		initialization
HEADERS+=		initialization.h
SRCS_FILE+=		game_master_init.c\
				parser.c\
				check_junk.c\
				settings_linker_init.c\
				setters_settings.c\
				read_part_with_analyzer.c\
				map_init.c\
				map_convert_utils.c\
				images.c\
				keys_init.c\
				render_init.c

DIRS+=		instruments
HEADERS+=		instruments.h
SRCS_FILE+=		common_things_part_1.c\
				algebra_part_1.c\
				drawning.c\
				wall_calculate.c\
				sprite_calculate.c\
				quick_sort_sprite.c

DIRS+=		naming_utils
HEADERS+=		naming_utils.h 
SRCS_FILE+=		naming_utils.c

OBJS_FILE=	$(SRCS_FILE:%.c=%.o)
LIBS_NAME:=	mlx ft
LIBS_DIRS:= $(addprefix lib,$(LIBS_NAME))
LIBS_FILE:= $(addsuffix .a,$(addprefix lib,$(LIBS_NAME)))
RM_LIBS:= $(addprefix $(LIBS_DIRS)/, $(LIBS_FILE))
LIB_LINK=	$(addprefix -l,$(LIB)) $(addprefix -Llib,$(LIB))
LIBS_LINK:=	$(foreach LIB,$(LIBS_NAME),$(LIB_LINK)) -lz
FRM:=		-framework OpenGL -framework AppKit
FLAGS:=		-Wall -Wextra -Werror -g
SRCS_PATH:=	$(addprefix $(SRCS_DIR)/,$(DIRS))

vpath %.c $(SRCS_PATH)
vpath %.h $(HDRS_DIR)
vpath %.o $(OBJS_DIR)
vpath %.a $(LIBS_DIRS)

#color things
RED = \033[31m
GREEN = \033[32m
PURPLE = \033[35m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJS_DIR) $(LIBS_FILE) $(OBJS_FILE)
	@make real

libft.a:
	@echo Checking libft
	make bonus -C libft

libmlx.a:
	@echo Checking libmlx
	make -C libmlx

real: $(OBJS_FILE)
	@echo Build all .o in $(NAME)
	$(CC) $(filter %.o, $^) $(FLAGS) -I$(HDRS_DIR) $(LIBS_LINK) $(FRM) -o $(NAME)

%.o: %.c libft.h mlx.h $(HEADERS)
	@$(CC) -c $< $(FLAGS) -I$(HDRS_DIR) -o $(OBJS_DIR)/$@
	@echo "✅ $@"

$(OBJS_DIR):
	mkdir -p $@

clean: 
ifeq (,$(wildcard $(OBJS_DIR)))
	@echo "$(GREEN)Objects files $(NAME)$(NC) already removed."
else
	@echo "Remove $(RED)objects files MLX$(NC)"
	@rm -rf $(OBJS_DIR)
	@echo "$(GREEN)Done.$(NC)"
endif

fclean: clean
	@make fclean -C libft
	@make fclean -C libmlx
ifeq (,$(wildcard $(NAME)))
	@echo "$(GREEN)$(NAME)$(NC) already removed."
else
	@echo "Remove $(RED)$(NAME)$(NC)"
	@rm -f $(NAME)
	@echo "$(GREEN)Done.$(NC)"
endif

re: fclean all

norme:
	@make norme -C libft
	@echo "$(PURPLE)CHECK THE NORM FOR $(RED)$(NAME)$(NC)"
	@norminette $(SRCS_PATH)/*.c
	@norminette $(HDRS_DIR)/*.h

recl:
	@make re && make clean

%:
	@echo "Can't find rule for target $@"
