README Tema2 - Dogaru Laurentiu
-Am definit o structura de tip nod care are urmatoare campuri: tabla - care
reprezinta tabla de joc la un moment dat, fii - un vector de noduri ce
reprezinta fiii, un camp de tip nod pentru parinte, un camp de tip intreg
pentru nivelul nodului in arbore, un camp de tip intreg val1 ce diferentiaza
nodurile "SI" de nodurile "SAU",si un camp de tip caracter,  pentru eticheta 
"T" sau "F" de la cerinta 2.

-Am definit o functie ce initializeaza un nod, primind ca parametri o matrice
de caractere ce reprezinta tabla de joc si parintele nodului nou creat.

-Am definit functii pentru : alocarea memoriei pentru un numar dat de fii, 
citirea matricei de inceput din fisier, si verificarea daca o matrice data
reprezinta castigul unuia dintre jucatori.

-Functia "goluri" returneaza numarul de pozitii necompletate dintr-o matrice
primita ca parametru

-Functia "modif" returneaza o matrice modificata, punand caracterul primit pe 
o pozitie anume

-Functia "construire" primeste ca parametri nodul radacina, care contine tabla
de start a jocului, si jucatorul care are prima mutare, si construieste
arborele de joc

-Functia "pre_order" primeste ca parametru radacina unui arbore si il afiseaza
in preordine

-Functia "free_tree" elibereaza memoria alocata pentru table si noduri, primind
radacina arborelui ca parametru

-Functia "depth" atribuie variabilei globale "adancime" valoarea adancimii
unui arbore cu o anume radacina

-Functia "atribuire frunze" atribuie tuturor frunzelor unui arbore in campul
"val2" "T" sau "F", in functie de rezultatul de castig pentru un anume
jucator.

-Functia "atribuire" atribuie "T" sau "F" nodurilor de pe un anumit nivel
conform regulii din cerinta( daca nodurile sunt tip "SI" sau "SAU" )

-Functia "atribuire_tree" apeleaza functia "atribuire_frunze" si dupa,
functia "atribuire" pentru fiecare nivel din arbore, in ordine descrescatoare

-Functia "afisare" afiseaza in preordine campurile "val2" ale arborelui



