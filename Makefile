CC := gcc
SRCDIR := src
TSTDIR := test
BUILDDIR := build
TARGET := bin/run
TST_TARGET := test/run
SRCEXT := c
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := 
# LIB := -L 
INC := -I include


$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB) -O3

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo " Building..."
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $< -save-temps -O3

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)
	@echo " $(RM) -r $(TSTDIR) $(TST_TARGET)"; $(RM) -r $(TSTDIR)/*.o $(TSTDIR)/*.out *.out $(TST_TARGET)

run: clean $(TARGET)
	./$(TARGET)

test/pool.o :
	$(CC) $(CFLAGS) $(INC) -c -o test/pool.o src/pool.c -I include/;

test/1.o :
	$(CC) $(CFLAGS) $(INC) -c -o test/1.o test/test_1.c -I include/;

test/2.o :
	$(CC) $(CFLAGS) $(INC) -c -o test/2.o test/test_2.c -I include/;

test/3.o :
	$(CC) $(CFLAGS) $(INC) -c -o test/3.o test/test_3.c -I include/;

# Tests
test: clean test/pool.o test/1.o test/2.o test/3.o
	$(CC) -o test/1.out test/pool.o test/1.o -I include/
	$(CC) -o test/2.out test/pool.o test/2.o -I include/
	$(CC) -o test/3.out test/pool.o test/3.o -I include/
	test/1.out
	test/2.out
	test/3.out
	

.PHONY: clean

all: $(TARGET) 