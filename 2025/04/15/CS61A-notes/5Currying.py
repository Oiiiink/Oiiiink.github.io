def curry2(f) : #parent : global
    def g(x) : #parent : curry
        def h(y) : #parent : g
            return f(x , y)
        return h
    return g
from operator import add
print("add(2 , 5) = " , add(2 , 5))
m = curry2(add) #bind m to g
print("m(2)(5) = " , m(2)(5))
# bind x to 2
# m(2) return g
#g(5) bind y to 5  than call f(x , y) y had been bind to 5  look for x 
# which is found in g frame been bind to 2 