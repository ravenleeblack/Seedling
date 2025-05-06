# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -fPIC -I$(SCOPE_INCLUDEDIR) -I$(SEED_INCLUDEDIR)
LDFLAGS = -shared
LDLIBS = -L$(LIBDIR) -lscope_table

# Directories
SEED_SRCDIR = 04_seed_source
SEED_INCLUDEDIR = 04_seed_include
SCOPE_SRCDIR = 05_scope_source
SCOPE_INCLUDEDIR = 05_scope_include

# Build directories
OBJDIR = 00_obj
LIBDIR = 00_lib
BINDIR = 00_bin

SEED_OBJDIR = $(OBJDIR)/seed
SCOPE_OBJDIR = $(OBJDIR)/scope
SCOPE_LIBDIR = $(LIBDIR)

# Seedling source files
SEED_SRCS = $(SEED_SRCDIR)/seed_main.c \
			$(SEED_SRCDIR)/seed_align.c \
			$(SEED_SRCDIR)/seed_arch.c \
			$(SEED_SRCDIR)/seed_assign.c \
			$(SEED_SRCDIR)/seed_arith.c \
			$(SEED_SRCDIR)/seed_begin_prog.c \
			$(SEED_SRCDIR)/seed_code.c \
			$(SEED_SRCDIR)/seed_compare.c \
			$(SEED_SRCDIR)/seed_common.c \
			$(SEED_SRCDIR)/seed_call.c \
			$(SEED_SRCDIR)/seed_nasm_encode.c \
			$(SEED_SRCDIR)/seed_error.c \
			$(SEED_SRCDIR)/seed_declare.c \
			$(SEED_SRCDIR)/seed_global_block.c \
			$(SEED_SRCDIR)/seed_global.c \
			$(SEED_SRCDIR)/seed_lex.c \
			$(SEED_SRCDIR)/seed_literal.c \
			$(SEED_SRCDIR)/seed_local_block.c \
			$(SEED_SRCDIR)/seed_local.c \
			$(SEED_SRCDIR)/seed_log.c \
			$(SEED_SRCDIR)/seed_list.c \
			$(SEED_SRCDIR)/seed_file.c \
			$(SEED_SRCDIR)/seed_match.c \
			$(SEED_SRCDIR)/seed_opcode.c \
			$(SEED_SRCDIR)/seed_pad.c \
			$(SEED_SRCDIR)/seed_phrases.c \
			$(SEED_SRCDIR)/seed_parse_type.c \
			$(SEED_SRCDIR)/seed_push.c \
			$(SEED_SRCDIR)/seed_registers.c \
			$(SEED_SRCDIR)/seed_section.c \
			$(SEED_SRCDIR)/seed_system.c \
			$(SEED_SRCDIR)/seed_transfer.c \
			$(SEED_SRCDIR)/seed_universal.c \
			$(SEED_SRCDIR)/seed_move.c \
			$(SEED_SRCDIR)/seed_jump.c \
			$(SEED_SRCDIR)/seed_pass_arg.c \
			$(SEED_SRCDIR)/seed_set_flag.c \
			$(SEED_SRCDIR)/color.c

SEED_OBJS = $(addprefix $(SEED_OBJDIR)/, $(notdir $(SEED_SRCS:.c=.o)))
SEED_HEADERS = $(wildcard $(SEED_INCLUDEDIR)/*.h)

# Scope Table library
SCOPE_SRCS = $(wildcard $(SCOPE_SRCDIR)/*.c)
SCOPE_HEADERS = $(wildcard $(SCOPE_INCLUDEDIR)/*.h)
SCOPE_OBJS = $(patsubst $(SCOPE_SRCDIR)/%.c,$(SCOPE_OBJDIR)/%.o,$(SCOPE_SRCS))

SCOPE_LIB_STATIC = $(LIBDIR)/libscope_table.a
SCOPE_LIB_SHARED = $(LIBDIR)/libscope_table.so

# Output executables
SEED_TARGET = $(BINDIR)/seed
ROOT_SEED = ./seed  # New target for the root directory copy

# Create necessary directories
create_dirs:
	@mkdir -p $(BINDIR) $(SEED_OBJDIR) $(SCOPE_OBJDIR) $(LIBDIR)

# Build rules
.PHONY: all clean clean_seed clean_scope

all: create_dirs $(SCOPE_LIB_STATIC) $(SCOPE_LIB_SHARED) $(SEED_TARGET) $(ROOT_SEED)

# Seed object files depend on source and headers
$(SEED_OBJDIR)/%.o: $(SEED_SRCDIR)/%.c $(SEED_HEADERS) $(SCOPE_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Seed executable in BINDIR
$(SEED_TARGET): $(SEED_OBJS) $(SCOPE_LIB_SHARED)
	$(CC) -o $@ $(SEED_OBJS) $(LDLIBS)

# Copy seed to root directory
$(ROOT_SEED): $(SEED_TARGET)
	cp $(SEED_TARGET) $(ROOT_SEED)

# Scope object files
$(SCOPE_OBJDIR)/%.o: $(SCOPE_SRCDIR)/%.c $(SCOPE_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Static and shared scope libraries
$(SCOPE_LIB_STATIC): $(SCOPE_OBJS)
	ar rcs $@ $^

$(SCOPE_LIB_SHARED): $(SCOPE_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Clean rules
clean: clean_seed clean_scope
	rm -rf $(OBJDIR) $(LIBDIR) $(BINDIR) $(ROOT_SEED)
	find . -type f -name "*.asm" -delete

clean_seed:
	rm -rf $(SEED_OBJDIR) $(SEED_TARGET)

clean_scope:
	rm -rf $(SCOPE_OBJDIR) $(SCOPE_LIB_STATIC) $(SCOPE_LIB_SHARED)