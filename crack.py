import sys
import crypt
from cs50 import get_int


def compare(hashedword, salt, key):
    answer = crypt.crypt(key, salt)
    if answer == hashedword:
        print(key)
        sys.exit()


def main():
    if(len(sys.argv) != 2):
        print("Invalid amount of command line arguements, stopping program...")
        return 1
    salt = "50"
    hashedword = sys.argv[1]
    key = ""
    symbols = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    for a in symbols:
        compare(hashedword, salt, a)
    for a in symbols:
        for b in symbols:
            compare(hashedword, salt, a + b)
    for a in symbols:
        for b in symbols:
            for c in symbols:
                compare(hashedword, salt, a + b + c)
    for a in symbols:
        for b in symbols:
            for c in symbols:
                for d in symbols:
                    compare(hashedword, salt, a + b + c + d)
    for a in symbols:
        for b in symbols:
            for c in symbols:
                for d in symbols:
                    for e in symbols:
                        compare(hashedword, salt, a + b + c + d + e)
    return 0


if __name__ == "__main__":
    main()