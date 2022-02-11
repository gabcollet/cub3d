# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 15:31:26 by sfournie          #+#    #+#              #
#    Updated: 2022/02/11 14:19:24 by gcollet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilation
# INCS_FLAGS has all the -I that are needed. (-Imlx, -Ilibft, etc.)
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
C_ALL			= $(CC) $(CFLAGS) $(INCS_FLAGS) $(INC_MLX)
C_OBJS			= $(C_ALL) -g
C_MAIN			= $(C_ALL) -g $(MAIN) $(OBJS) -lmlx $(C_FWRK) $(LIB_LFT) -o $(NAME)
C_BMAIN			= $(C_ALL) -g $(BMAIN) $(BOBJS) -lmlx $(C_FWRK) $(LIB_LFT) -o $(B_NAME)
C_LINUX_OBJS	= $(C_ALL) -O3 -g
C_LINUX_MAIN	= $(C_ALL) -g $(MAIN) $(OBJS) -Lmlx_linux -lmlx_linux -lXext -lX11 -lm -lz $(LIB_LFT) -o $(NAME)
C_LINUX_BMAIN	= $(C_ALL) -g $(BMAIN) $(BOBJS) -Lmlx_linux -lmlx_linux -lXext -lX11 -lm -lz $(LIB_LFT) -o $(NAME)
C_FWRK			= -framework OpenGL -framework AppKit
#

# Program
NAME	= cub3D
B_NAME  = cub3D_bonus
#

# Directories
DIR_SRCS	= srcs
DIR_BSRCS	= srcs_bonus
DIR_OBJS	= objs
DIR_INCS	= includes
DIR_MAINS	= mains
DIR_LFT		= libft
#

# Libraries and Includes
LIB_LFT		= $(DIR_LFT)/libft.a
INC_MLX		= -Imlx

INCS_ALL	= $(DIR_LFT) $(DIR_INCS)
INCS_FLAGS	= $(patsubst %,-I%,$(INCS_ALL))
#

# Makefiles
MK_LFT		= make -C $(DIR_LFT)
#

# Mains
MAIN		= $(DIR_MAINS)/main.c
BMAIN		= $(DIR_MAINS)/main_bonus.c
#

# Headers
_HEADS	=	cub3d.h cub3d_struct.h
HEADS		= $(patsubst %,$(DIR_INCS)/%,$(_HEADS))
#

# Sources and Objects
SRCS	= 	game.c map.c map_utils.c\
			parse.c parse_map.c parse_utils.c parse_wall.c\
			parse_map_id.c parse_cub_id.c\
			position.c rotation.c size.c\
			math_utils.c math_angles.c\
			image.c mlx.c textures.c\
			color.c color_trgb.c color_utils.c\
			background.c\
			collision.c intersection.c intersection_utils.c\
			raycast.c\
			input.c

_OBJS	= $(SRCS:.c=.o)
OBJS	= $(patsubst %,$(DIR_OBJS)/%,$(_OBJS))

# BONUS Headers
_BHEADS	=	cub3d_bonus.h cub3d_struct_bonus.h cub3d_time_bonus.h
BHEADS		= $(patsubst %,$(DIR_INCS)/%,$(_HEADS))
#

# BONUS Sources and Objects
_BSRCS	= 	game map map_utils interface\
			parse parse_map parse_utils parse_wall\
			parse_map_id parse_cub_id\
			position rotation\
			math_utils math_angles\
			image mlx textures sprite\
			color color_trgb color_utils\
			draw minimap\
			background\
			animation time\
			collision intersection intersection_utils\
			raycast\
			object init_object\
			door door_utils animation_door\
			player gun enemy init_enemy\
			input
			
BSRCS	= $(patsubst %,%_bonus.c,$(_BSRCS))

_BOBJS	= $(BSRCS:.c=.o)
BOBJS	= $(patsubst %,$(DIR_OBJS)/%,$(_BOBJS))

$(DIR_OBJS)/%.o :  %.c
		$(C_OBJS) -c $< -o $@

vpath %.c $(DIR_SRCS)
vpath %.c $(DIR_BSRCS)
#

all		: $(NAME)

$(NAME)	: $(HEADS) $(DIR_INCS) $(LIB_LFT) $(SRCS) $(MAIN) $(DIR_OBJS) $(OBJS)
		@ $(C_MAIN)
		# $(shell echo "Compiling cub3d done!")
		# $(shell echo "Executable is : $(NAME)")

$(DIR_OBJS)	: 
		@ mkdir objs

$(LIB_LFT)	:
		@ $(MK_LFT) all

clean	: 
		@ rm -rf $(DIR_OBJS)
		@ $(MK_LFT) clean
		# $(shell echo "cub3d cleaned!")

fclean	: clean
		@ $(MK_LFT) fclean
		@ rm -rf $(NAME)
		@ rm -rf $(B_NAME)

linux	: _linux $(NAME)

_linux	:
		$(eval C_OBJS=$(C_LINUX_OBJS))
		$(eval C_MAIN=$(C_LINUX_MAIN))
		$(eval INC_MLX=$(INC_MLX))
		
_b_linux	:
		$(eval C_OBJS=$(C_LINUX_OBJS))
		$(eval C_BMAIN=$(C_LINUX_BMAIN))
		$(eval INC_MLX=$(INC_MLX))

re		: fclean all

re_linux : fclean linux

bonus	: $(B_NAME)

$(B_NAME)	: $(BHEADS) $(DIR_INCS) $(LIB_LFT) $(BSRCS) $(BMAIN) $(DIR_OBJS) $(BOBJS)
		@ $(C_BMAIN)
		# $(shell echo "Compiling cub3d bonus done!")
		# $(shell echo "Executable is : $(B_NAME)")

re_bonus	: fclean bonus

b_linux	: _b_linux bonus

re_b_linux	: fclean _b_linux bonus

signature : 
	@echo "                        								"
	@echo "                        .@@@@@@@@@@@@@@@@@@@@@@@@&."
	@echo "                      (@@@@@@@@POUTINE-STJEAN@@@@@@@@/"
	@echo "                   .&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*"
	@echo "                  .&../@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%"
	@echo "                  %%@#%@@@@@@@@@@@@@@@@@@@@@@@@@@#&. ./%*   ,&(@@&,*&/"
	@echo "     #(  &*       ##@/ %@@@@@@@(/&@@@@@@@@@@@&@@@@@*  *&  /%*@@@@@@@@.%,"
	@echo "   (#.&@@@//&/     @. @@#/.   .%@%@&@@@@@,       ,,/  &##.*@@@@@@@%.*@/@"
	@echo "  ,# .#@@@@@@( *&@&@, .#*        (&%@@@@& /@@%. *@@* ,   (@@@@@@,,%,   &*"
	@echo "   & @*(/./&@@@/      *@@(  , .%@@%@@@@@@@@#.%&@@@&       %@@( (.    .&*"
	@echo "   .@,        *%.  *@@@@@@@@@@@@@@%@@@@@@@@@@@@@@@@@#    ,/       .#%."
	@echo "     %#            ,.%@@@@@@@@@@@@@&/& @@@@@@@@@@@@@.          ,&("
	@echo "       *&(,           /(&@@@@@@@@@@@&@( &@@@@(/(/,          /&*"
	@echo "           ,#&/        /.  /&%%@@@@@@@@@@@@&,%           /@,"
	@echo "                /@(*      %@@@@@@@@@@@@@@@@@(@        .*&."
	@echo "                   /%&*     .@@@@@@@@@@@@@@@@&       ,&,"
	@echo "                    .%(      (((@@@@@@@@@@@@/&          .*%%(,"
	@echo "                *%#.         .  .,.(*,   ..              ,(%%%%#%&%#(*."
	@echo "            *&(*.      .,.                            /&@@@@@@@@@@@@@&%*#("
	@echo "     ##%&/*#&@@@@@&*                                    ..  ,#@@@@@@@@@@#.#"
	@echo "   /# (@@@@@@/. ,%/.         .#&&&#&       ((.              .*#/  .*%@*   &"
	@echo "   .@.     *&@#.        #@(.       ,#%&#* (/     ,@%(, *(.        .#,    &*"
	@echo "    .&.   &%       *&%.                *@@/          ,.    .#@&(       %#" 
	@echo "      ,@/ *   *%@*                                                .,#,"
	@echo "                        								"

.PHONY	: all re clean fclean bonus linux re_b_linux
