## Creates a gamma-corrected lookup table
import math

def gamma(nsteps, gamma):
    gammaedUp = [math.pow(x, gamma) for x in range(nsteps)]
    return [x/max(gammaedUp) for x in gammaedUp]

def rounder(topValue, gammas):
    return [min(topValue, round(x*topValue)) for x in gammas]

if __name__ == "__main__":
    myGamma = 2.314
    steps = 256
    out_string = ""
    out_string += ("/* %d-step brightness table: gamma = %s */ \n\n" % (steps, myGamma))
    out_string += ("const uint8_t gamma_table[%d] = {\n" % steps)
    for value in rounder(255, gamma(steps, myGamma)):
        out_string += ("\t %d,\n" % value)
    out_string += ("};\n")
    
    print(out_string)