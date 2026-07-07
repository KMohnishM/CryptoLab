from functools import reduce

def modinv(a, m):
    """Compute modular inverse using Extended Euclidean Algorithm."""
    def egcd(x, y):
        if y == 0:
            return x, 1, 0
        g, s, t = egcd(y, x % y)
        return g, t, s - (x // y) * t
    g, x, _ = egcd(a, m)
    if g != 1:
        raise ValueError(f"Error: Modular inverse does not exist for modulus {m}")
    return x % m


def crt(moduli, remainders):
    # Validation
    if not moduli or not remainders:
        raise ValueError("Error: No congruences provided")
    if len(moduli) != len(remainders):
        raise ValueError("Error: Number of moduli and remainders must match")

    # Product of all moduli
    M = reduce(lambda a, b: a * b, moduli)
    result = 0

    for m, r in zip(moduli, remainders):
        Mi = M // m
        inv = modinv(Mi, m)  # safe modular inverse
        result += r * Mi * inv

    return result % M


def main():
    try:
        n = int(input("Enter the number of congruences: "))
        if n <= 0:
            print("Error: Number of congruences must be positive")
            return

        moduli = []
        remainders = []
        for i in range(n):
            try:
                m = int(input(f"Enter modulus m{i+1}: "))
                if m <= 0:
                    print("Error: Moduli must be positive integers")
                    return
                r = int(input(f"Enter remainder r{i+1}: "))
            except ValueError:
                print("Error: Inputs must be integers")
                return

            moduli.append(m)
            remainders.append(r)

        result = crt(moduli, remainders)
        print("Result:", result)

    except ValueError as e:
        print(e)


if __name__ == "__main__":
    main()
