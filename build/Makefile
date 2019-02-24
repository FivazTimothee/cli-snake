APP_NAME := snake

VPATH += ../src
VPATH += ../external/tinycthread/source
OUTDIR := out

SRC_FILES += main.c
SRC_FILES += map.c
SRC_FILES += snake.c
SRC_FILES += tinycthread.c
SRC_FILES += game.c

OBJS := $(addprefix $(OUTDIR)/,$(SRC_FILES:.c=.o))
DEPS := $(addprefix $(OUTDIR)/,$(SRC_FILES:.c=.d))
INC := $(addprefix -I,$(VPATH))

# OS specific part
ifeq ($(OS),Windows_NT)
    RM = del /F /Q
    RMDIR = -RMDIR /S /Q
    MKDIR = -mkdir
    ERRIGNORE = 2>NUL || true
    SEP=\\
else
    RM = rm -rf
    RMDIR = rm -rf
    MKDIR = mkdir -p
    ERRIGNORE = 2>/dev/null
    SEP=/
endif

all: $(APP_NAME)
	@echo Build done

$(APP_NAME): $(OBJS)
	@echo --------------------
	@echo Linking $@
	gcc $(OBJS) -o $@

$(OUTDIR)/%.o:%.c | $(OUTDIR)
	@echo Building $< [triggered by changes in $?]
	gcc -c -MMD -g $(INC) $< -o $@

$(OUTDIR):
	@echo Creating folder $@
	$(MKDIR) $@

clean:
	$(RMDIR) $(OUTDIR) $(ERRIGNORE)
	$(RMDIR) $(APP_NAME) $(ERRIGNORE)
	@echo Cleaning done

.PHONY: all clean

-include $(DEPS)
