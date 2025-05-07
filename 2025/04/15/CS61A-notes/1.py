def square(x) :
    return x * x
y = 2
def apply_twice(f , x) :
    return f(f(x)) * y
print(apply_twice(square , 2))