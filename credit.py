from cs50 import get_int


def main():
    cc_no = get_int("Enter your credit card number:")

    checksum = 0
    first_two_digits = 0
    mult_by_two = false
    cc_no_length = 0

    AMEX_1 = 34
    AMEX_2 = 37
    AMEX_LENGTH = 15

    FIRST_MC = 51
    LAST_MC = 55
    MC_LENGTH = 16

    FIRST_VISA = 40
    LAST_VISA = 49
    VISA_LENGTH1 = 13
    VISA_LENGTH2 = 16

    # iterate over digits
    while (cc_no > 0):
        # for each digit, starting from the last:
        cur_digit = cc_no % 10

        # add the new digit to the checksum, doubling if necessary
        if (mult_by_two):
            # accounting for the case where need to add digits together
            if cur_digit < 5:
                checksum += (cur_digit * 2)
            else:
                checksum += (cur_digit * 2 - 9)
        else:
            checksum += cur_digit

        # keep track of beginning of number to identify credit card company
        first_two_digits = cur_digit * 10 + (first_two_digits / 10)

        # update state and drop last digit
        mult_by_two = not mult_by_two
        cc_no = cc_no / 10
        cc_no_length = cc_no_length + 1

    # validate checksum, company identifier, and number length
    if (checksum % 10):
        print("INVALID")
    elif (((first_two_digits == AMEX_1) or (first_two_digits == AMEX_2)) and (cc_no_length == AMEX_LENGTH)):
        print("AMEX")
    elif ((first_two_digits >= FIRST_VISA) and (first_two_digits <= LAST_VISA) and ((cc_no_length == VISA_LENGTH1) or (cc_no_length == VISA_LENGTH2))):
        print("VISA")
    elif ((first_two_digits >= FIRST_MC) and (first_two_digits <= LAST_MC) and (cc_no_length == MC_LENGTH)):
        print("MASTERCARD")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()