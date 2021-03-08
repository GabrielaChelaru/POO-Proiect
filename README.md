
tratarea exceptiilor
utilizarea variabilelor și functiilor statice
utilizarea conceptelor de Dynamic_Cast și Static_Cast
utilizarea sabloanelor
citirea informațiilor complete a n obiecte, memorarea și afisarea acestora
cerinte generale aplicate fiecarei teme din acest fisier:
- să se identifice și să se implementeze ierarhia de clase;
- clasele sa conțină constructori, destructori, =, funcție prietena de
citire a datelor;
- clasa de baza sa conțină funcție virtuala de afisare, rescrisa în
clasele derivate;
- clasele derivate trebuie sa contina cel constructori parametrizati
prin care sa se evidentieze transmiterea parametrilor către
constructorul din clasa de baza.

# Descrierea proiectului

Firma X are un domeniu de business unde este necesar să se urmărească modul în care clientii plătesc (numerar, cec sau card de credit).
 Indiferent de modul de plata, firma X știe în ce data s-a efectuat plata și ce suma a fost primita. Dacă se plătește cu cardul, atunci se cunoaște și numărul cardului de credit.
 Pentru cash, nu e necesara identificarea clientului care a făcut plata.
Cerinta suplimentara:
     - Sa se construiasca clasa template Gestiune care sa conțină numărul total de plati (incrementat  automat la adaugarea unei noi chitante)
      și un vector de pointeri la obiecte de tip Plata, alocat dinamic. Sa se supraincarce operatorul += pentru inserarea
unei plati în lista, indiferent de tipul acesteia.
- Sa se construiasca o specializare pentru tipul char* care sa stocheze numarul de clienti, impreuna cu numele acestora.
structura
-  abstract clasa Plata(data, suma)
-derivata numerar, cec(cnp), card de credit(cod)--fiecare derivata
--clasa templatee trebuie sa contina un vectori de pointeri la clasa Plata//vecator de tip typeid

