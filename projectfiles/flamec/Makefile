# Paths to libraries and includes
BLAS_LIB   := $(HOME)/blis/lib/libblis.a
FLAME_LIB  := $(HOME)/libflame/lib/libflame.a
FLAME_INC  := $(HOME)/libflame/include
CBLAS_INC  := $(HOME)/openblas/include      # adjust if needed

# Compiler and flags
CC         := gcc
LINKER     := $(CC)
CFLAGS     := -O3 -Wall -I$(FLAME_INC) -I$(CBLAS_INC) -m64 -msse3
FFLAGS     := $(CFLAGS)
LDFLAGS    := -m64 -lm -fopenmp

# Experiment parameters
NREPEATS   := 3    # number of times each experiment is repeated
NFIRST     := 100  # smallest size to be timed
NLAST      := 1500 # largest size to be timed
NINC       := 100  # increment between sizes

# List of operations (base names, without “_driver” suffix)
OPS := \
	syrk_ln_blk_var1 \
	syrk_ln_unb_var1 \
	trmm_lunn_unb_var1 \
	trmm_lunn_blk_var1

# Derive executables: e.g. syrk_ln_blk_var1_driver.x
EXES := $(OPS:%=%_driver.x)

# Phony targets
.PHONY: all run_all test clean

# Default: build everything
all: $(EXES)

# Build each driver executable by compiling its .c and linking
# against the corresponding algorithm object (%.o).
# E.g. syrk_ln_blk_var1_driver.x ← syrk_ln_blk_var1_driver.o + syrk_ln_blk_var1.o
%_driver.x: %_driver.o %.o
	$(LINKER) $^ $(FLAME_LIB) $(BLAS_LIB) $(LDFLAGS) -o $@

# Compile any .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run all benchmarks; writes output_<op>.m for each
run_all: all
	@echo "=== Running all benchmarks ==="
	@for op in $(OPS); do \
	  exe=$${op}_driver.x; \
	  out=output_$${op}.m; \
	  printf "  -> %s\n" "$$exe"; \
	  printf "$(NREPEATS) $(NFIRST) $(NLAST) $(NINC)\n" | ./$$exe > $$out; \
	done
	@echo "All benchmarks complete. Outputs in output_<op>.m"

# Make 'test' alias run_all, for compatibility
test: run_all

# Clean up all build artifacts
clean:
	rm -f *.o *~ core *.x output_*.m
