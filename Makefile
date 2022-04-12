CXX = g++-11
CC = g++-11
INCLUDES = -I /opt/homebrew/include -I externals/HighFive/include -I externals/H5Easy
CXXFLAGS = -std=c++20 -O0 -fmodules-ts $(shell pkg-config --cflags hdf5 2> /dev/null) $(INCLUDES)
LDLIBS = -lhdf5 -lhdf5_cpp
LDFLAGS = -L /opt/homebrew/lib $(shell pkg-config --libs-only-L --libs-only-other hdf5 2> /dev/null)

MODS_DIR = gcm.cache

hash := \# # escaping '#' inline seems to break things on Linux
sed_sys_mods = $(shell sed -En 's/^[[:space:]]*import[[:space:]]+<(.*)>[[:space:]]*\;/\1/p' $(1) 2> /dev/null)
sed_local_mods = $(shell sed -En 's/^[[:space:]]*(import|module)[[:space:]]+([[:alpha:]].*)[[:space:]]*\;/\2/p' $(1) 2> /dev/null)
grep_mod_exporter = $(shell grep -REl '^[[:space:]]*export[[:space:]]+module[[:space:]]+$(1)[[:space:]]*\;' . | head -n1)

find_sys_dir = $(shell echo '$(hash)include<$(mod)>' | g++-11 -M -xc++ - | tr " " "\n" | grep -E '/$(mod)$$')
find_mods = $(call sed_local_mods,$(1)) $(foreach mod,$(call sed_sys_mods,$(1)),$(find_sys_dir))
parse_mod_deps = $(addprefix $(MODS_DIR)/, $(addsuffix .gcm, $(call find_mods,$(1))))

$(MODS_DIR)//%.gcm: # double forward-slash hack distinguishes system headers (which we format in this way)
	$(CXX) $(CXXFLAGS)   -xc++-system-header $(basename $(notdir $@))

.SECONDEXPANSION:
$(MODS_DIR)/%.gcm : $$(call grep_mod_exporter,$$*) $$(call parse_mod_deps,$$(call grep_mod_exporter,$$*))	
	$(eval EXPORTER := $(call grep_mod_exporter,$(basename $(notdir $@))))
	# hack needed because the compiled module seems to break if relevant precompiled system headers are still present
	for SYSINC in $$(sed -En 's/^[[:space:]]*#include[[:space:]]+<(.*)>[[:space:]]*$$/\1/p' $(EXPORTER)); do find $(MODS_DIR)/*/ -name $$SYSINC.gcm -exec rm {} \; ; done
	$(CXX) $(CXXFLAGS)   -c -o $(patsubst %.cpp,%.o,$(EXPORTER)) $(EXPORTER)

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
