from math import floor, pi, sqrt

start = 0
end = 500000
searching = True

while(searching):
    print('Searching from', start, 'to', end, '...\n')
    for k in range(start+1, end, 1):
        if(k % 2 == 0): # if k is even
            A = 4 * k**2 * pi
        else:
            A = pi*(4*k**2 + 4*k + 1)
        r = sqrt(A/pi)

        if(floor(A) == A and floor(r) == r): # if Area is an integer value
            print('A \'perfect\' circle with radius', sqrt(A)/sqrt(pi), 'and area', A, 'was found.')

    ans = input('Continue searching? [q to exit] --> ').lower()
    if(ans == 'q'):
        searching = False
    else:
        start = end
        end += 500000