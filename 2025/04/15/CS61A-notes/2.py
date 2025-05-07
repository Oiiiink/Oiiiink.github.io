def f(x , y) : #parent frame : global
    return g(x)

def g(a) : #parent frame : global
    return a + y
y = 2
print(f(1 , 2))

  