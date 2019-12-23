# Makefile of #2 exercise - Semester A (winter) 2019

.PHONY: all clean

OS := $(shell uname)
CC:= @gcc 
CFLAGS:= -std=c99 -std=gnu11 -Wall
TIME = $(shell date +"%T.%3N")

#MAIN PROG DIR, SOURCES AND OBJECTS
MAIN_DIR:= ex2_q1/src
MAIN_SRC:= $(wildcard $(MAIN_DIR)/*.c)
MAIN_obj:= $(MAIN_SRC:.c=.o) 

#HELPER PROG DIR, SOURCES AND OBJECTS
HELPER_DIR:= ex2_q1_helper/src
HELPER_SRC:= $(wildcard $(HELPER_DIR)/*.c)
HELPER_obj:= $(HELPER_SRC:.c=.o)

ifneq (,$(findstring CYGWIN,$(OS)))
  EXT = .exe
else
  EXT = .out
endif

PROG1 = ex2_q1_helper$(EXT)
PROG2 = ex2_q1$(EXT)

all: $(PROG1) $(PROG2) test

$(PROG1) : $(HELPER_obj)
	@echo ===============================================================
	@echo -e Compilation of target "\\e[5;41m$@\\e[0m" started at "\\e[5;41m$(TIME)\\e[0m"
	@echo ===============================================================
	$(CC) $(CFLAGS) $^ -o $(PROG1)
	@echo ===============================================================
	@echo -e Compilation of target "\\e[5;41m$@\\e[0m" started at "\\e[5;41m$(TIME)\\e[0m"
	@echo ===============================================================
	
$(PROG2) : $(MAIN_obj)
	@echo ===============================================================
	@echo -e Compilation of target "\\e[5;41m$@\\e[0m" started at "\\e[5;41m$(TIME)\\e[0m"
	@echo ===============================================================
	$(CC) $(CFLAGS) $^ -o $(PROG2)
	@echo ===============================================================
	@echo -e Compilation of target "\\e[5;41m$@\\e[0m" started at "\\e[5;41m$(TIME)\\e[0m"
	@echo ===============================================================
	
test:
	@echo ===============================================================
	@echo -e Execution of "\\e[5;41m$@\\e[0m" "\\e[5;41m$(PROG)\\e[0m" started at: "\\e[5;41m$(TIME)\\e[0m"
	@echo ===============================================================
	./$(PROG2) < in.txt > out.log
		@echo ===========================================================
	@echo -e Execution of "\\e[5;41m$@\\e[0m" "\\e[5;41m$(PROG)\\e[0m" finished at: "\\e[5;41m$(TIME)\\e[0m"
	@echo ===============================================================
	@echo
	@echo
	@echo ===============================================================
	@echo -e "\\e[1;43mResults:\\e[0m"
	@echo ===============================================================
	
	@cat out.log
	
clean:

	@ rm -f $(MAIN_DIR)/*.o $(HELPER_DIR)/*.o *.exe *.log *.tmp
	@echo ===============================================================
	@echo Binary,Obj, Log and Tmp files were cleaned!
	@echo ===============================================================