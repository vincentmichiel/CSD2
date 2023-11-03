#! /usr/bin/env python

# Python function that acts as an IIR combfilter.
# Pieter Suurmond, sept 6, 2019.
#
# Difference equation:  y[n] = x[n] + 0.5 y[n-6]
#
# Block diagram:        x ---> + -----------------------------------> y
#                              ^                          |
#                              |    -----------------     v
#                               ---| 6 samples delay |<-- x <-- 0.5
#                                   -----------------

# Allocate an array for 6 floating point numbers (circular buffer):
num = 2                             # Number of samples delay.
mem = [0.0] * num                   # Memory (num floating point samples).
idx = 0                             # Index into that array (0 to num-1).

# Function that acts as an infinite impulse response (IIR) combfilter:
# each single input-sample (x) yields a single output-sample (y).
def iir(x):
    global num, mem, idx            # 3 global variables.

    y = x + mem[idx]                # Read from delay line and calculate output.
    mem[idx] = -0.5 * y              # Store 50% of the output in the delay line.
    idx = (idx + 1) % num           # Advance and wrap idx to the next position.

    return y

# Print impulse response:
for n in range(-3, 14):
    if n == 0:
        x = 1.0
    else:
        x = 0.0
    print ("%4d: %4.4f"% (n, iir(x)) )