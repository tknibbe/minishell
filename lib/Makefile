# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 14:27:27 by tknibbe           #+#    #+#              #
#    Updated: 2023/07/03 13:48:57 by tknibbe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

FLAGS = -Wall -Wextra -Werror

SRCLIB = check/ft_isalpha.c \
		check/ft_isdigit.c \
		check/ft_isalnum.c \
		check/ft_isascii.c \
		check/ft_isprint.c \
		str/ft_strlen.c \
		memory/ft_memset.c \
		conversions/ft_bzero.c \
		memory/ft_memcpy.c \
		memory/ft_memmove.c \
		str/ft_strlcpy.c \
		str/ft_strlcat.c \
		conversions/ft_toupper.c \
		conversions/ft_tolower.c \
		str/ft_strchr.c \
		str/ft_strrchr.c \
		str/ft_strncmp.c \
		memory/ft_memchr.c \
		memory/ft_memcmp.c \
		str/ft_strnstr.c \
		conversions/ft_atoi.c \
		memory/ft_calloc.c \
		str/ft_strdup.c \
		str/ft_substr.c \
		str/ft_strjoin.c \
		str/ft_strtrim.c \
		str/ft_split.c \
		conversions/ft_itoa.c \
		str/ft_strmapi.c \
		str/ft_striteri.c \
		io/ft_putchar_fd.c \
		io/ft_putstr_fd.c \
		io/ft_putendl_fd.c \
		io/ft_putnbr_fd.c \
		str/ft_instr.c
		

OBJLIB = ft_isalpha.o ft_isdigit.o ft_isalnum.o \
		ft_isascii.o ft_isprint.o ft_strlen.o ft_memset.o \
		ft_bzero.o ft_memcpy.o ft_memmove.o ft_strlcpy.o \
		ft_strlcat.o ft_toupper.o ft_tolower.o ft_strchr.o \
		ft_strrchr.o ft_strncmp.o ft_memchr.o ft_memcmp.o \
		ft_strnstr.o ft_atoi.o ft_calloc.o ft_strdup.o \
		ft_substr.o ft_strjoin.o ft_strtrim.o ft_split.o \
		ft_itoa.o ft_strmapi.o ft_striteri.o ft_putchar_fd.o \
		ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o \
		ft_instr.o
		
SRCPRINTF = io/ft_printf.c \
			io/c_s_u_d_i_conversion.c \
			io/hex_conversion.c \
			io/more_functions.c \
			
OBJPRINTF = ft_printf.o hex_conversion.o \
			c_s_u_d_i_conversion.o more_functions.o

SRCGNL = io/get_next_line.c \
			io/get_next_line_utils.c

OBJGNL = get_next_line.o \
			get_next_line_utils.o

ALLFILES = $(SRCLIB) ${SRCPRINTF} ${SRCGNL}

ALLOBJ = ${OBJLIB} ${OBJPRINTF} ${OBJGNL}

$(NAME): $(ALLFILES)
	@cc $(FLAGS) -c $(ALLFILES)
	@ar r $(NAME) $(ALLOBJ)
	@make clean
	@echo "\033[0;32mLibft ready\033[0m"

all: $(NAME)

clean:
	@rm -f $(OBJLIB) ${OBJPRINTF} ${OBJGNL}
	
fclean: clean
	@rm -rf $(NAME)
	
re: fclean all
	







			