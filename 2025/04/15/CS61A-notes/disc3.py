def swipe(n) :
    if n < 10 :
        print(n) 
    else :
        all_but_last , last = n // 10 , n % 10
        print(last)
        swipe(all_but_last)
        print(last)
#swipe(int(input()))
def is_prime(n):
    """Returns True if n is a prime number and False otherwise.
    >>> is_prime(2)
    True
    >>> is_prime(16)
    False
    >>> is_prime(521)
    True
    """
    "*** YOUR CODE HERE ***"
    assert n > 1
    def plus(n , i) :
        if i >= n :
            return True
        elif n % i == 0 :
            return False
        else :
            return plus(n , i + 1) 
    return plus(n , 2)

def is_prime_iter(n) :
    assert  n > 1
    k = 2
    while k < n :
        if n % k == 0 :
            return False
        k += 1
    return True

def judge(f , g ) :
    for i in range(2 , 1000) :
        if g(i) != f(i) :
            print(i)
            return False
    return True
#print(judge(is_prime , is_prime_iter))

# game Sevens
def sevens(n, k):
    """Return the (clockwise) position of who says n among k players.

    >>> sevens(2, 5)
    2
    >>> sevens(6, 5)
    1
    >>> sevens(7, 5)
    2
    >>> sevens(8, 5)
    1
    >>> sevens(9, 5)
    5
    >>> sevens(18, 5)
    2
    """
    def f(i, who, direction):
        if i == n:
            return who
        else :
            if i % 7 == 0 or has_seven(i) :
                direction = -direction
            who += direction
            if who <= 0 : 
                who = k
            elif who > k :
                who = 1
            return f(i + 1 , who , direction)
    return f(1, 1, 1)

def has_seven(n):
    if n == 0:
        return False
    elif n % 10 == 7:
        return True
    else:
        return has_seven(n // 10)
print(sevens(int(input()) , int(input())))

#Karel the Robot