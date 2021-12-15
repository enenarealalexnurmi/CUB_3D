# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enena <enena@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/03 17:51:07 by enena             #+#    #+#              #
#    Updated: 2021/11/28 03:31:42 by enena            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = /bin/sh

.PHONY: all bonus clean fclean re norme recl

CC = gcc

NAME = libft.a

HEADER = libft.h 

SRC_NAME =  ft_atoi\
			ft_atol\
			ft_atoll\
			ft_bzero\
			ft_calloc\
			ft_charcount\
			ft_isalnum\
			ft_isalpha\
			ft_isascii\
			ft_isupper\
			ft_islower\
			ft_isodd\
			ft_iseven\
			ft_isanum\
			ft_upper\
			ft_lower\
			ft_isspace\
			ft_isdigit\
			ft_isprint\
			ft_itoa\
			ft_lltoa_base\
			ft_ulltoa_base\
			ft_memccpy\
			ft_memchr\
			ft_memcmp\
			ft_memcpy\
			ft_memmove\
			ft_memset\
			ft_putendl_fd\
			ft_putnbr_fd\
			ft_putchar_fd\
			ft_putstr_fd\
			ft_split\
			ft_free_tab\
			ft_tab_size\
			ft_strchr\
			ft_strdup\
			ft_strjoin\
			ft_strlcat\
			ft_strlcpy\
			ft_strlen\
			ft_strncmp\
			ft_strmapi\
			ft_strnstr\
			ft_strrchr\
			ft_strtrim\
			ft_substr\
			ft_tolower\
			ft_toupper\
			ft_swap_p\
			ft_swap_ch\
			ft_swap\
			ft_stous\
			ft_get_next_line\
			ft_sec_free\
			ft_set_output_attr\
			ft_write_bmp\
			ft_check_extention\

BONUS_NAME = ft_lstadd_back\
			 ft_lstadd_front\
			 ft_lstclear\
			 ft_lstdelone\
			 ft_lstiter\
			 ft_lstlast\
			 ft_lstmap\
			 ft_lstnew\
			 ft_lstsize\

FLAGS = -Wall -Wextra -Werror

O_FILE = $(addsuffix .o, $(SRC_NAME))

O_BONUS_FILE = $(addsuffix .o, $(BONUS_NAME)) 

O_ALL ?= $(O_FILE)

HEADER_ALL ?= $(HEADER)

#color things
RED = \033[31m
GREEN = \033[32m
PURPLE = \033[35m
NC = \033[0m

all: $(NAME)

bonus:
	@make O_ALL:="$(O_FILE) $(O_BONUS_FILE)" all

$(NAME): $(O_ALL)
	@echo "$(PURPLE)Creating library $(GREEN)$@$(NC)"
	@ar rc $@ $?
	@ranlib $@

%.o: %.c $(HEADER_ALL)
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "✅ $@"

clean:
ifeq (,$(wildcard *.o))
	@echo "$(GREEN)Objects files $(NAME)$(NC) already removed."
else
	@echo "Remove $(RED)objects files $(NAME)$(NC)"
	@rm -f *.o
	@echo "$(GREEN)Done.$(NC)"
endif

fclean: clean
ifeq (,$(wildcard $(NAME)))
	@echo "$(GREEN)$(NAME)$(NC) already removed."
else
	@echo "Remove $(RED)$(NAME)$(NC)"
	@rm -f $(NAME)
	@echo "$(GREEN)Done.$(NC)"
endif

re: fclean all

norme:
	@echo "$(PURPLE)CHECK THE NORM FOR $(RED)$(NAME)$(NC)"
	@norminette *.c
	@norminette *.h

recl:
	@make re && make clean

%:
	@echo "Can't find rule for target $(RED)$@$(NC)"
