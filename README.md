Sample Code
===========

1) Book Index Generator
Given a book and a list of common words, generate the book's index.
More specifically, generate an alphabetical list of all "uncommon" words in the book, followed by the page numbers the book appears on.

NOTE:
This was my go-to open-ended pseudo-code problem that was my last interview question, after the candidate had passed all the easier stuff.
It allowed me to understand the candidate's thought process in detail.  Particularly:
-Were they able to deal with ambiguity and not get flustered?  Could they instead tease out the critical information necessary to define the program requirements?
-Did they have a decent practical sense of Big-O?  Were they able to make design decisions based on expected run-time?
-Did they have a decent practical sense of concurrency?  Were they able to make good design decisions once the problem evolved into "imagine you now have lots of CPUs instead of one.  Reconsider the question."

This got me thinking:  how would the program's run-time performance ACTUALLY pan out?  So I decided to implement it, in C++, first in order to brush up on syntax, but also to answer this question for myself.

