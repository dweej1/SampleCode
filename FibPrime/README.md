Find the 7th fibonacci prime number.
----

definition:
A fibonacci prime is a fibonacci number that is prime.

----

Simple brute force method:
iterate over the fibonacci numbers and do a primality test on each

----

Another option: get a copy of the first, say million primes or so, load them into a key->value store, then generate fib numbers and do lookups, and stop when you hit the 7th successful lookup.


