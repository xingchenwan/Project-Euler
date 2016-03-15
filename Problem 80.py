# Problem 80
import math


def sq_root_digit_sum(num, p, step, digits):
    if step < 100:
        p = str_to_int(step, digits)
        i = 1
        while i * (p * 20 + i) <= num:
            i += 1
        i -= 1
        digits[step] = i
        y = i*(p*20+i)
        return sq_root_digit_sum((num-y)*100, p, step+1, digits)

    else:
        val_sum = 0
        for i in range(0, 100):
            val_sum += digits[i]
        return val_sum


def str_to_int(num_size, digits):
    n = num_size - 1
    return_val = 0
    for m in range(0, num_size):
        return_val += (digits[m]*(10**n))
        n -= 1
    return return_val


if __name__ == '__main__':
    val_sum = 0
    for i in range(2, 100):
        digit_array = [0 for x in range(0, 100)]
        if math.sqrt(i) == int(math.sqrt(i)):
            pass
        else:
            print ("%d: Sum of first 100 digits = %d" % (i, sq_root_digit_sum(i, 0, 0, digit_array)))
            val_sum += sq_root_digit_sum(i, 0, 0, digit_array)
    print ('Total Sum = %d' % val_sum)

# Ans: 40886
# Digit-by-digit square-root finding algorithm