##
## Makefile for Makefile in /home/oem/home/PSU_2016_myftp
##
## Made by maxence.lauque
## Login   <lauque_m@epitech.net>
##
## Started on  Wed May 10 14:02:00 2017 maxence.lauque
## Last update Sun May 21 21:29:25 2017 maxence.lauque
##

CC = gcc

NAME = server

RM = rm -f

SRC = 	src/main.c \
	src/str_2_wordtab.c \
	src/get_next_line.c \
	src/creating_socket.c \
	src/list_cmd.c \
	src/list_cmd2.c \
	src/listen_socket.c \
	src/manage_cwd.c \
	src/usr_pass.c \
	src/manage_cmd.c \
	src/tool_functions.c

INCLUDE = -I ./includes

FLAGS = -W -Wall -Werror -pedantic

CFLAGS = $(INCLUDE) $(FLAGS)

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

all : $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
