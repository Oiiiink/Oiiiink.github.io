def print_sum(x) :
    print(x)
    def next_sum(y) :
        return print_sum(x + y)
    return next_sum
#print_sum(1)(2)(3)(100)

# recursive function
def sum_digit(x) :
    if x == 0 :
        return 0
    else :
        return x % 10 + sum_digit(x // 10)
#print(sum_digit(1111))

# whening considering Recursion , don't think about how he do , but what should he do

# mutual recursion 
# Luhn sum

def luhn_sum(n) :
    if n < 10 :
        return n 
    else :
        all_but_last , last = n // 10 , n % 10
        return luhn_sum_double(all_but_last) + last 
def luhn_sum_double(n):
    all_but_last , last = n // 10 , n % 10
    luhn_digit = sum_digit(last)
    if n < 10 :
        return luhn_digit 
    else :
        return luhn_sum(all_but_last) + luhn_digit
    
# tree recursion
grow = lambda n : f_then_g(grow , print , n // 10)
shrink = lambda n : f_then_g(print , shrink , n // 10)
def inverse_cascade(n) :
    grow(n)
    print(n)
    shrink(n)
def f_then_g(f , g , n) :
    if n :
        f(n)
        g(n)
#inverse_cascade(123456)
times = 0
def trace(fn) :
    def f(*args) :
        global times
        times += 1
        print("function " , fn , "on argument" , *args)
        return fn(*args)
    return f
@ trace
def fib(n) :
    if n == 0:
        return 0 
    elif n == 1 :
        return 1
    else :
        return fib(n - 1) + fib(n - 2)
for i in range(1 , 35) :
    fib(i)
    print("fib(" , i ,")" , " used " , times)
    times = 0
