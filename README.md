# MergeSort

Merge Sort is an O(N log N) algorithm with arrays.
With linked lists I don't think this changes whole lot because the main problem with linked lists 
is having to travsers through the array to get where we want to go. 

Merge Sort will definitley take more time in the split function.
For merge sort with linked lists we can't use the left, right, and mid indexing that 
we do with arrays because linked lists have long traversal time because you have to go through
each element before the one you want, which is an O(N) operation. 

I would say it takes about O(N) to get to the element
to split at and then O(1) to change the pointers. The merge function is a basic
comparator function which should take about O(log N) time. 
Merging the lists back together does not take long as all so I think the 
cost for that would be O(1) to change the pointers around and such. 

So the total time it takes for the algorithm to perform merge sort on a
singly linked lists is O(N log N). The initial configuration of the array does 
not matter for merge sort because it divides and conquers the LinkedList to sort
it in order!
