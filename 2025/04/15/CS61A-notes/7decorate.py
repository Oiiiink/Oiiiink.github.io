def trace(fn) :
    def fn_traced(*args):
        print("Calling" , fn , "on argument" , end = ' ')
        print("(" , end = ' ')
        for i in args :
            print(i , end = ' ')
        print(')')
        return fn(*args)
    return fn_traced
@trace
def square(x) :
    return x * x 
@trace
def my_add(x , y) :
    print(x + y)
    return x + y
def sum_square_to_n(n) :
    k = 0
    total = 0
    while k <= n :
        total , k = total + square(k) , k + 1
    print(total)
    return total
my_add(1 , 2)