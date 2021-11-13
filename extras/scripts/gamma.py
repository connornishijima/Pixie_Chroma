## Creates a gamma-corrected lookup table
import math

def gamma(nsteps, gamma):
    gammaed_up = [math.pow(x, gamma) for x in range(nsteps)]
    return [x/max(gammaed_up) for x in gammaed_up]

def rounder(top_value, gammas):
    return [min(top_value, round(x*top_value)) for x in gammas]

if __name__ == "__main__":
    in_gamma = 2.314
    steps = 256
    out_string = ""
    out_string += ("/* %d-step brightness table: gamma = %s */ \n\n" % (steps, in_gamma))
    out_string += ("const uint8_t gamma_table[%d] = {\n" % steps)
    for value in rounder(255, gamma(steps, in_gamma)):
        out_string += ("\t %d,\n" % value)
    out_string += ("};\n")
    
    print(out_string)