child(jack, mike).
child(sarah, mike).
child(jack, joan).
child(sarah, joan).
child(joan, judith).
child(alison, judith).
child(susan, judith).
child(mike, evelyn).
child(brian, evelyn).

siblings(Child1, Child2) :- child(Child1, Parent), child(Child2, Parent).
