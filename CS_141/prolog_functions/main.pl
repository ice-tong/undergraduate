my_reverse(L, R) :- rev(L, R, []).
rev([], Acc, Acc).
rev([H|T], Acc, R) :- rev(T, Acc, [H|R]).

my_length([], 0).
my_length([_|T], R) :- my_length(T, Tlength), R is Tlength+1.

my_subset(_, [], []).
my_subset(Term, [H|T], R) :- Bool =.. [Term, H], not(Bool), my_subset(Term, T, R).
my_subset(Term, [H|T], [H|R]) :- Bool =.. [Term, H], Bool, my_subset(Term, T, R).

my_member(X, [X|_]).
my_member(X, [_|T]) :- my_member(X, T).

my_intersect([], _, []).
my_intersect([H|T], L, R) :- not(my_member(H, L)), my_intersect(T, L, R).
my_intersect([H|T], L, [H|R]) :- my_member(H, L), my_intersect(T, L, R).

compute_change(0,0,0,0,0).
compute_change(Total, Q, D, N, P) :- Q is Total//25, T1 is mod(Total,25),
				     D is T1//10, T2 is mod(T1,10),
				     N is T2//5, P is mod(T2,5).

compose([], [], []).
compose(L,[],L).
compose([],L,L).
compose([H1|T1], [H2|T2], [H1,H2|RT]) :- compose(T1,T2,RT).

palindrome([],[]).
palindrome([X], [X,X]).
palindrome([H|T], P) :- append([H],PT,RBeginning), append(RBeginning,[H],P), palindrome(T,PT).
