door_between(a,b).
door_between(a,c).
door_between(a,d).
door_between(b,c).
door_between(b,e).
door_between(d,c).
door_between(d,e).
door_between(e,c).

bidirectional(X,Y) :- door_between(X,Y).
bidirectional(X,Y) :- door_between(Y,X).

path_from(X,Y,R) :- helper(X,Y,[X],Temp), reverse(Temp,R).
helper(X,Y,V,R) :- bidirectional(X,Z), Z \== Y, \+member(Z,V), 
				helper(Z,Y,[Z|V],R).
helper(X,Y,Acc,[Y|Acc]) :- bidirectional(X,Y).


same_language(X, Y) :- X\==Y, speaks(X, Lang), speaks(Y, Lang).
both_male(X, Y) :- X\==Y, male(X), male(Y).
opp_gender(X, Y) :- male(X), female(Y).
opp_gender(X, Y) :- female(X), male(Y).
can_sit_together(X,Y) :- same_language(X, Y), both_male(X, Y).
can_sit_together(X,Y) :- same_language(X, Y), opp_gender(X, Y).

party_seating([A1,A2,A3,A4,A5,A6,A7,A8,A9,A10]) :- 
can_sit_together(A1,A2),
can_sit_together(A2,A3),
can_sit_together(A3,A4),
can_sit_together(A4,A5),
can_sit_together(A5,A6), 
can_sit_together(A6,A7), 
can_sit_together(A7,A8), 
can_sit_together(A8,A9), 
can_sit_together(A9,A10), 
can_sit_together(A1,A10), 
not(member(A1,[A2,A3,A4,A5,A6,A7,A8,A9,A10])),
not(member(A2,[A1,A3,A4,A5,A6,A7,A8,A9,A10])),
not(member(A3,[A1,A2,A4,A5,A6,A7,A8,A9,A10])),
not(member(A4,[A1,A2,A3,A5,A6,A7,A8,A9,A10])),
not(member(A5,[A1,A2,A3,A4,A6,A7,A8,A9,A10])),
not(member(A6,[A1,A2,A3,A4,A5,A7,A8,A9,A10])),
not(member(A7,[A1,A2,A3,A4,A5,A6,A8,A9,A10])),
not(member(A8,[A1,A2,A3,A4,A5,A6,A7,A9,A10])),
not(member(A9,[A1,A2,A3,A4,A5,A6,A7,A8,A10])),
not(member(A10,[A1,A2,A3,A4,A5,A6,A7,A8,A9])).

  

sim(X,X) :- number(X), !.

sim(0 + X, X) :- !.
sim(X + 0, X) :- !.
sim(X + Y, R) :- number(X), number(Y), R is X+Y, !.
sim(X + Y, X + Y) :- !.

sim(X - 0, X) :- !.
sim(0 - X, -X) :- !.
sim(X - Y, R) :- number(X), number(Y), R is X-Y, !.
sim(X- -(Y), X + Y) :- !. 
sim(X - Y, X - Y) :- !.

sim(0 * _, 0) :- !.
sim(_ * 0, 0) :- !.
sim(1 * X, X) :- !.
sim(X * 1, X) :- !.
sim(C * D, R) :- number(C), number(D), R is C*D, !.
sim(C1 * (C2 * X), CR * X) :- CR is C1*C2, !.
sim(C1 * (C2 * X ^ E), CR * X ^ E) :- CR is C1 * C2, !.
sim(X * Y, X * Y) :- !.

sim(0 / _, 0) :- !.
sim(_ / X, 1 / X) :- !.
sim(X / 1, X) :- !.
sim(X / X, 1) :- !.
sim(X / Y, X / Y) :- !.

sim(0 ^ _, 0) :- !.
sim(_ ^ 0, 1) :- !.
sim(1 ^ _, 1) :- !.
sim(X ^ 1, X) :- !.
sim(X ^ Y, X ^ Y) :- !.


deriv(C, 0) :- number(C).
deriv(x, 1) :- !.
deriv(C * V, R) :- number(C), deriv(V, D), sim(C * D, R), !.
deriv(V / C, R) :- number(C), deriv(V, D), sim(1/C * D, R), !.
deriv(C / x, -C / x^2) :- number(C), !.
deriv(V ^ C, R) :- number(C), deriv(V, A), sim(C * A, B),
		N is C - 1, sim(V ^ N, V1), sim(B * V1, R), !.
deriv(A + B, R) :- deriv(A, DA), deriv(B, DB), sim(DA + DB, R), !.
deriv(A - B, R) :- deriv(A, DA), deriv(B, DB), sim(DA - DB, R), !.
deriv(A * B, R) :- deriv(A, DA), deriv(B, DB),
		sim(A * DB, R1), sim(B * DA, R2), sim(R1 + R2, R).
deriv(A / B, R) :- deriv(A, DA), deriv(B, DB),
		sim(B * DA, R1), sim(A * DB, R2), sim(R1-R2, Top),
		sim(B ^ 2, Bottom), sim(Top / Bottom, R).
