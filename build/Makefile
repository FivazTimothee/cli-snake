APP_NAME := snake

VPATH += ../src
OUTDIR := out

SRC_FILES += main.c

OBJS := $(addprefix $(OUTDIR)/,$(SRC_FILES:.c=.o))
DEPS := $(addprefix $(OUTDIR)/,$(SRC_FILES:.c=.d))

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
	gcc -c -MMD $< -o $@

$(OUTDIR):
	@echo Creating folder $@
	$(MKDIR) $@

clean:
	$(RMDIR) $(OUTDIR) $(ERRIGNORE)
	$(RMDIR) $(APP_NAME) $(ERRIGNORE)
	@echo Cleaning done

.PHONY: all clean

-include $(DEPS)
