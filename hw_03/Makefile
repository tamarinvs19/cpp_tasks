CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++17 -Iinclude
LDFLAGS = 

EXE = hw_03
SRCDIR = src
TEST_EXE = hw_03_test
TEST_DIR = test
OBJDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(TEST_DIR)/*.cpp))

all: $(EXE)

test: $(TEST_EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)

$(TEST_EXE): $(TEST_OBJECTS) obj/huffman.o obj/tree.o
	$(CXX) obj/huffman.o obj/tree.o $(TEST_OBJECTS) -o $(TEST_EXE) $(LDFLAGS)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR) 
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

$(OBJDIR)/%.o: $(TEST_DIR)/%.cpp | $(OBJDIR) 
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(OBJDIR)/*.d)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXE) $(TEST_EXE) *.test_file

.PHONY: clean all
