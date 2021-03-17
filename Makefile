NAME := Blaster

CC := gcc -m32
ASM := nasm

CFLAGS = -masm=intel -fno-pic -fno-stack-protector -Wall -Werror -Wextra -O0 
ifeq ($(OPT), LD)
CFLAGS +=  -fno-pic -ffunction-sections -nostdlib -D __NO_MAIN__
endif

SFLAGS := -f elf32

CPATH = src/
HPATH = inc/
OPATH = obj/

OBJS = \
       loader.o\
       Blaster_start.o \
       Main_Blaster.o\
       Blaster_end.o\
       Blaster.o \

ALL_OBJS = $(addprefix $(OPATH), $(OBJS))

HFILES = inc/ft_virus.h

INC = $(addprefix -I./, $(HPATH))

LINKER := ld
LINKER_CONF := linker.ld
LINKER_FLAGS := -T $(LINKER_CONF) 

#.PHONY: all install clean fclean re test

all: $(NAME)

$(OPATH):
	mkdir -p $(OPATH)

ifeq ($(OPT), LD)
$(NAME): $(ALL_OBJS)
	$(LD) $(LINKER_FLAGS) $(ALL_OBJS) -o $(NAME)
else
$(NAME): $(ALL_OBJS)
	$(CC) $(CFLAGS) $(ALL_OBJS) -o $(NAME)
endif

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	mkdir -p $(OPATH)
	$(CC) $(CFLAGS) $(INC) $< -c -o $@

$(OPATH)%.o: $(CPATH)%.s $(HFILES)
	mkdir -p $(OPATH)
	$(ASM) $(SFLAGS) $< -o $@

clean:
	rm -f $(ALL_OBJS)

fclean: clean
	rm -f $(NAME)
	rmdir $(OPATH)

re: fclean all
