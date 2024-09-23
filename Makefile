CC = gcc
CFLAGS = -c -g
LDFLAGS = -pthread

BUILD_DIR = build

# $(CC) -c circbuff.c -o circbuff.o

TESTS_CIRCBUFF = tests/circbuff_test.c

TEST_SRCS = \
	$(TESTS_CIRCBUFF)

LIB_SRCS = \
	circularbuffer/circbuff.c

SRCS = \
	$(TEST_SRCS) \
	$(LIB_SRCS)

OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

run:
	make all
	clear
	./$(BUILD_DIR)/circbuff_test

all: $(OBJS)
#	 $(CC) $(CFLAGS) $(SRCS)
	$(CC) $(LDFLAGS) -o $(BUILD_DIR)/circbuff_test $(OBJS) -lcunit
#	clear

# Compile source files into object files in the build directory
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(BUILD_DIR)
	clear