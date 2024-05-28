% Facts: Define parent-child relationships.
parent(ram, priya).
parent(ram, anil).
parent(priya, amita).
parent(anil, anjali).
parent(shyam, ram).
parent(shyam, priya).


% Rules: Define sibling and grandparent relationships.
sibling(X, Y) :-
    parent(Z, X),
    parent(Z, Y),
    X \= Y.


grandparent(X, Y) :-
    parent(X, Z),
    parent(Z, Y).
