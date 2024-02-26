CFLG	=	-std=c11 $(addprefix -W, all extra error pedantic) -g 

SRC_DIR	= src
INC_DIR	= inc
OBJ_DIR	= obj

INC_FILES = $(wildcard $(INC_DIR)/*.h)
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:%.c=%.o)))


all: install

install: libmx/libmx.a uls

uls: $(OBJ_FILES)
	@clang $(CFLG) -lsqlite3 $(OBJ_FILES) -L libmx -lmx -o $@
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES)
	@clang $(CFLG) -c  $< -o $@ -I$(INC_DIR) -I libmx/inc
	@printf "\r\33[2K uls \033[33;1mcompile \033[0m$(<:$(SRC_DIR)/%.c=%) "

$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $@

libmx/libmx.a:
	@make -sC libmx
	
clean:
	@rm -rf $(OBJ_DIR)
	@printf "$(OBJ_DIR) in uls \033[31;1mdeleted\033[0m\n"

uninstall:
	@make -sC libmx $@
	@rm -rf $(OBJ_DIR)
	@rm -rf uls
	@printf "uls \033[31;1muninstalled\033[0m\n"

reinstall: uninstall all
