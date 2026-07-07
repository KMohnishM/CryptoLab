from functools import reduce

def crt(moduli, remainders):
    # Product of all moduli
    M = reduce(lambda a, b: a * b, moduli)
    result = 0
    for m, r in zip(moduli, remainders):
        Mi = M // m
        # Modular inverse of Mi mod m
        inv = pow(Mi, -1, m)
        result += r * Mi * inv
    return result % M
