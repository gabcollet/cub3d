# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 15:31:26 by sfournie          #+#    #+#              #
#    Updated: 2021/12/20 15:50:41 by sfournie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilation
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
C_OBJS	= $(CC) $(CFLAGS) $(INCS_FLAGS) -c $< -o $@
C_MAIN	= $(CC) $(CFLAGS) $(INCS_FLAGS) -lmlx $(C_FWRK) $(L_ALL)
C_FWRK	= -framework OpenGL -framework AppKit

#

# Program
NAME	= cub3D 
#

# Directories
DIR_SRCS	= srcs
DIR_OBJS	= objs
DIR_INCS	= includes
DIR_MAINS	= mains
DIR_LFT		= libft
#

# Libraries and Includes
L_LFT		= $(DIR_LFT)/libft.a

L_ALL		= $(LIB_LFT)
INCS_ALL	= $(DIR_LFT) $(DIR_INCS) mlx
INCS_FLAGS	= $(patsubst %,-I%,$(INCS_ALL))
#

# Makefiles
MK_LFT		= make -C $(DIR_LFT)
#

# Mains
MAIN		= $(DIR_MAINS)/cub3d.c
MAIN_PRAC	= $(DIR_MAINS)/main.c

# Headers
_HEADS	=	cub3d.h
HEADS		= $(patsubst %,$(DIR_INCS)/%,$(_HEADS))
#

# Sources and Objects
SRC	= 	

_OBJ	= $(SRC:.c=.o)
OBJ		= $(patsubst %,$(DIR_OBJS)/%,$(_OBJ))

$(DIR_OBJS)/%.o :  %.c
		@ $(C_OBJS)

vpath %.c $(DIR_SRCS)

SRCS	= $(SRC)
OBJS	= $(OBJ)
#
all		: $(NAME)

$(NAME)	: $(HEADS) $(DIR_INCS) $(L_LFT) $(SRCS) $(MAIN) $(DIR_OBJS) $(OBJS)
		 $(C_MAIN) $(MAIN) $(OBJS) -o $(NAME)
		# $(shell echo "Compiling cub3d done!")
		# $(shell echo "Executable is : $(NAME)")

$(DIR_OBJS)	: 
		@ mkdir objs

$(L_LFT)	:
		@ $(MK_LFT) all

clean	: 
		@ rm -rf $(DIR_OBJS)
		@ $(MK_LFT) clean
		# $(shell echo "cub3d cleaned!")

fclean	: clean
		@ $(MK_LFT) fclean
		@ rm -rf $(NAME)
		
practice	: _practice $(NAME)
_practice	: 
			$(eval MAIN=$(MAIN_PRAC))



re		: fclean all

bonus	: $(NAME)

.PHONY	: all re clean fclean bonus practice
