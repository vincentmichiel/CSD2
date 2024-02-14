#! /usr/bin/env python

# Python function that acts as a FIR combfilter.
# Pieter Suurmond, sept 6, 2019.
#
# Difference equation:  y[n] = x[n] + x[n-8]
#
# Block diagram:                 -----------------  
#                       x ----->| 8 samples delay |----> + ---> y
#                           |    -----------------       ^
#                           |                            |
#                            ----------------------------

# Allocate an array for 8 floating point numbers (circular buffer):
num = 1                             # Number of samples delay.
mem = [0.0] * num                   # Memory (num floating point samples).
idx = 0                             # Index into that array (0 to num-1).

# Function that acts as a finite impulse response (FIR) combfilter:
# each single input-sample (x) yields a single output-sample (y).
def fir(x):
    global num, mem, idx            # 3 global variables.

    y = -0.5 * x + 0.5 * mem[idx]                # Read from delay line and calculate output.
    mem[idx] = x                    # Store the new input in the delay line.
    idx = (idx + 1) % num           # Advance and wrap index to next position.

    return y

# Print impulse response:
for n in range(-3, 14):
    if n == 0:
        x = 1.0
    else:
        x = 0.0
    print ("%4d: %4.4f"% (n, fir(x)) )