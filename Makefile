# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/14 10:00:31 by tmatis            #+#    #+#              #
#    Updated: 2021/09/02 13:25:33 by tmatis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################


NAME	= ft_containers
CC 		= clang++
CFLAGS	= -Wall -Werror -Wextra -std=c++98
AUTHOR	= tmatis
DATE	= 01/09/2021

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS_PATH		= ./

INCLUDE_PATH	= ./

SRCS			=
SRCS_CHECKER	= checker/main.cpp
SRCS_TESTS 		= tests/main.cpp tests/test_vector.cpp

################################################################################
#                                 Makefile logic                               #
################################################################################


OBJ_CHECKER	= $(addprefix objs/, ${SRCS_CHECKER:.cpp=.o})
OBJ_TESTS		= $(addprefix objs/, ${SRCS_TESTS:.cpp=.o})
OBJS				= $(addprefix objs/, ${SRCS:.cpp=.o})

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

OK_STRING    = "[OK]"
ERROR_STRING = "[KO]"
WARN_STRING  = "[WARN]"
COM_STRING   = "Compiling"

define run_and_test
printf "%b" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@F)$(NO_COLOR)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
if [ $$RESULT -ne 0 ]; then \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"   ; \
elif [ -s $@.log ]; then \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"   ; \
else  \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"   ; \
fi; \
cat $@.log; \
rm -f $@.log; \
exit $$RESULT
endef

all:	header bin_ft bin_stl

header:
	@printf "%b" "$(OK_COLOR)"
	@echo "        ___  _____ ___  ___      _        "
	@echo "       /   |/ __  \|  \/  |     | |       "
	@echo "      / /| |\`' / /'| .  . | __ _| | _____ "
	@echo "     / /_| |  / /  | |\/| |/ _\` | |/ / _ \\"
	@echo "     \___  |./ /___| |  | | (_| |   <  __/"
	@echo "         |_/\_____/\_|  |_/\__,_|_|\_\___|"
	@echo
	@printf "%b" "$(OBJ_COLOR)Name:	$(WARN_COLOR)$(NAME)\n"
	@printf "%b" "$(OBJ_COLOR)Author:	$(WARN_COLOR)$(AUTHOR)\n"
	@printf "%b" "$(OBJ_COLOR)Date: 	$(WARN_COLOR)$(DATE)\n\033[m"
	@echo

bin_stl: 	
			@$(call run_and_test,$(CC) $(CFLAGS) -D TESTED_NAMESPACE=std -o $@ ${SRCS_TESTS})

bin_ft: 	
			@$(call run_and_test,$(CC) $(CFLAGS) -D TESTED_NAMESPACE=ft -o $@ ${SRCS_TESTS})

./bin_test:	${OBJS} ${OBJ_CHECKER}
		@$(call run_and_test,$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -o $@ ${OBJS} ${OBJ_CHECKER})
	
run: header fclean bin_stl bin_ft ./bin_test
		@./bin_ft > ./stl.out
		@./bin_stl > ./ft.out
		@./bin_test


objs/%.o: 	$(SRCS_PATH)/%.cpp
			@mkdir -p $(dir $@)
			@$(call run_and_test,$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_PATH))

clean:		header
			@rm -rf objs objs_tests ft.out stl.out
			@printf "%-53b%b" "$(COM_COLOR)clean:" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"

fclean:		header clean
			@rm -rf ./verif ./bin_ft ./bin_stl ./bin_test
			@rm -rf $(TEST_NAME)
			@printf "%-53b%b" "$(COM_COLOR)fclean:" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"

re:			fclean all

.PHONY:		all clean fclean re libft header
