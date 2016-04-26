birthday(jack, 1995).
birthday(matt, 1995).

same_birthday(X, Y) :- birthday(X, Year), birthday(Y, Year).
