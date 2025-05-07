def square(x) : 
    return x * x 
def triple(x) :
    return 3 * x
def compose1(f , g) :
    def h(x) :
        return g(f(x))
    return h
print(compose1(square , triple)(4))