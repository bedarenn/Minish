# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/10 15:48:47 by bedarenn          #+#    #+#              #
#    Updated: 2024/03/23 12:46:54 by bedarenn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##################################### NAME #####################################
NAME := minishell
WATI_NAME := libwati.a
WATI_RULES := libwati-

################################### COMPILER ###################################
CC := clang

################################# DIRECTORIES ##################################

DIR_OBJS := objs/
DIR_WATI := libwati/
DIR_LIBS := libs/

DIR_SRCS := srcs/
DIR_HDRS := hdrs/
DIR := \
	$(DIR_SRCS) \
	$(DIR_HDRS)

#################################### FILES #####################################

SRCS = \
	wati_readline.c \
	wati_prompt.c \
	env/env_manage.c env/env_tools.c \
	dir/dir_manage.c \
	wati_echo.c \
	signal_new.c \
	main_ehlz.c \
	parse/parsing.c \
	parse/parsing_utils.c \
	environnement/variable.c \
	environnement/create_env_list.c

OBJS = $(addprefix $(DIR_OBJS), $(SRCS:%.c=%.o))

#################################### FLAGS #####################################
CFLAGS := -Wall -Wextra #-Werror
LFLAGS := -L$(DIR_LIBS) -lreadline -lwati
IFLAGS := -I$(DIR_HDRS)

##################################### MAKE #####################################
MAKE := make --no-print-directory -C

#################################### RULES #####################################

all:
debug:

$(NAME): $(OBJS)
	@printf "$(GREEN)compile $@                                         $(NC)\n"
	@$(CC) $^ $(LFLAGS) -o $@

$(DIR_OBJS)%.o: $(DIR_SRCS)%.c
	@printf "$(BROWN)compile $(notdir $<)                              $(NC) \r"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean: $(WATI_RULES)clean
	@printf "$(RED)clean objs$(NC)\n"
	@rm -rf $(DIR_OBJS)

fclean: $(WATI_RULES)fclean
	@printf "$(RED)clean $(NAME)$(NC)\n"
	@rm -rf $(DIR_OBJS)
	@rm -f $(NAME)
	@rm -f $(DIR_LIBS)$(WATI_NAME)

re: fclean all

all:	$(WATI_RULES)all $(NAME)
debug:	CFLAGS += -g
debug:	$(WATI_RULES)debug $(NAME)

dir: $(DIR)
	mkdir -p $^

################################# WATI_RULES ###################################

$(WATI_RULES)all:
	@$(MAKE) $(DIR_SRCS)$(DIR_WATI) -j
	@mkdir -p $(DIR_LIBS)
	@cp $(DIR_SRCS)$(DIR_WATI)$(WATI_NAME) $(DIR_LIBS)
	@cp $(DIR_SRCS)$(DIR_WATI)libwati.h $(DIR_HDRS)libwati.h
$(WATI_RULES)debug:
	@$(MAKE) $(DIR_SRCS)$(DIR_WATI) debug
	@mkdir -p $(DIR_LIBS)
	@cp $(DIR_SRCS)$(DIR_WATI)$(WATI_NAME) $(DIR_LIBS)
	@cp $(DIR_SRCS)$(DIR_WATI)libwati.h $(DIR_HDRS)libwati.h
$(WATI_RULES)clean:
	@$(MAKE) $(DIR_SRCS)$(DIR_WATI) clean
$(WATI_RULES)fclean:
	@$(MAKE) $(DIR_SRCS)$(DIR_WATI) fclean
$(WATI_RULES)re:
	@$(MAKE) $(DIR_SRCS)$(DIR_WATI) re
git:
	@printf "$(RED)clean wati_git$(NC)\n"
	@rm -rf $(DIR_SRCS)$(DIR_WATI).git

#################################### PHONY #####################################
.PHONY: all clean fclean debug dir git

#################################### COLORS ####################################
RED = \033[0;31m
GREEN = \033[0;32m
BROWN = \033[1;33m
PURPLE = \033[0;35m
NC = \033[0m