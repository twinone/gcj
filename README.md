# gcj
My Google Code Jam solutions


### Problem 1

The easy opening problem. You don't even have to optimize this one, really.
Swap the last occurrence of `CS` to `SC`, removing the highest power beam to half. Try again until your shield holds or you run out of attempts. Easy.



### Problem 2

I found this problem interesting, you have to see that it's actually 2 separate vectors corresponding to even/odd positions.
Once you find that, you can sort both vectors independently in `O(n log n)` instead of simulating the `O(n^2)` and the problem becomes solvable.

This problem reminded me of a mergesort, but splitting the vectors instead of merging them.


### Problem 3

I failed this problem at first because I swapped x and y (always happens x/y vs row/col). It was an ok problem though.
The naive approach would be to fill up a square like (2,2) until all 9 surrounding squares are full, and then move to the
next 3x3 block. This will leave you with about 130/200 filled squares after 1000 tries.

I thought shape doesn't matter and tested it calculating the average number of tries over 100 simulations:

```
$ ./a.out 
4x50: 491.98 (100 cases)
5x40: 494.57 (100 cases)
8x25: 496.52 (100 cases)
10x20: 490.5 (100 cases)

```

So the solution is to always go to the square with the least number of filled surrounding squares, to maximize your success rate.
You can simply keep track of it in a matrix. A solved matrix would look like this:

```
5 3 3 3 3 3 3 5 
3 0 0 0 0 0 0 3 
3 0 0 0 0 0 0 3 
5 3 3 3 3 3 3 5 
```

### Problem 4

This one was pretty interesting. I even used OpenSCAD to do some checks and calculations before I submitted. My reasoning and detailed explanation are in the [code itself](https://github.com/twinone/gcj/blob/master/qualification/4-CubicUFO.cc).


