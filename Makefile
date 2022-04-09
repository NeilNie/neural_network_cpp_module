CXX = g++-11
CC = g++-11
CXXFLAGS = -std=c++20 -fmodules-ts

MODS_DIR = gcm.cache
SYS_MODS_DIR = $(MODS_DIR)/./usr/include/c++/11

sed_sys_mods = $(shell sed -En 's/^\s*import\s+<(.*)>\s*\;/\1/p' $(1) 2> /dev/null)
sed_local_mods = $(shell sed -En 's/^\s*(import|module)\s+(\w.*)\s*\;/\2/p' $(1) 2> /dev/null)
grep_mod_exporter = $(shell grep -REl '^\s*export\s+module\s+$(1)\s*\;' . | head -n1)

parse_mod_deps = $(addprefix $(MODS_DIR)/, $(addsuffix .gcm, $(call sed_local_mods,$(1)))) \
                 $(addprefix $(SYS_MODS_DIR)/, $(addsuffix .gcm, $(call sed_sys_mods,$(1))))

.SECONDEXPANSION:
gcm.cache/%.gcm : $$(call grep_mod_exporter,$$*) $$(call parse_mod_deps,$$(call grep_mod_exporter,$$*))
	$(eval EXPORTER := $(call grep_mod_exporter,$(basename $(notdir $@))))
	$(CXX) $(CXXFLAGS)   -c -o $(patsubst %.cpp,%.o,$(EXPORTER)) $(EXPORTER)

$(SYS_MODS_DIR)/%.gcm:
	$(CXX) $(CXXFLAGS) -xc++-system-header $(basename $(notdir $@))

LIB_SOURCE = $(shell find src -name '*.cpp')
LIB_OBJECTS = $(LIB_SOURCE:.cpp=.o)
LIB = libneuralnets.a
TEST_SOURCE = $(shell find tests -name '*.cpp')
TEST_OBJECTS = $(TEST_SOURCE:.cpp=.o)
OBJECTS = $(LIB_OBJECTS) $(TEST_OBJECTS)
TESTS = $(TEST_SOURCE:.cpp=)

$(LIB): $(LIB_OBJECTS)
	ar rcs $@ $^
	ranlib $@

.PHONY: tests
tests: $(TESTS)

$(TESTS) : % : %.o $(LIB)

$(OBJECTS) : %.o : $$(call parse_mod_deps,$$*.cpp)

.PHONY: clean
clean:
	rm -rf $(MODS_DIR) $(OBJECTS) $(TESTS) $(LIB)
