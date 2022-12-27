##
##	Makefile
##  use make to compile the project 
##  needed [gcc, make] binary
##


##info
NAME	=	ftp

## Compile info
CC	=	gcc
CFLAGS	= -Wextra -Wall -g3

## include
LDIR	=	-I includes/

## source
SRC	=	$(wildcard ./src/*.c)	
OBJ	= $(SRC:.c=.o)	

%.o : %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(LDIR)


all: $(NAME)


$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(LDIR)


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
