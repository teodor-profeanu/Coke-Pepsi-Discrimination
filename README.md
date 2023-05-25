## **_Pepsi vs Cola -- discriminare_**
Procesarea Imaginilor
Studenți: Teodor Profeanu, Adela Tatar
Facultatea: Automatică și Calculatoare
Profesor îndrumător: Vicaș Cristian

### 1. Descrierea proiectului:
Clasificarea, pe bază de histograma dupa culoare, a unor imagini cu sticle/doze de pepsi și cola în catedoria din care fac parte. 
Implementarea unui clasificator (noi am ales knn). Acesta primeste un set antrenat de poze si o poza de test pe care o clasifică în funcție de hue (culoare) in categoria pepsi sau cola. 
La clasificarea după saturație am luat un prag, care poate fi variat pentru a vedea diferențele, deoarece dorim sa luăm în considerare doar culori de roșu și albastru aprins, iar pentru asta e nevoie de un prag mai mare al saturației. 
Antrenarea se face cu 340 de poze etichetate (170 cu pepsi si 170 cu cola), iar pentru testare avem 60 de poze (cate 30 din fiecare).
Pentru a calula distanța dintre puncte avem două variante, distanța euclidiană și distanța cosinus. 
K-ul de la clasificatorul Knn nu este unul fix, ci poate fi variat pentru a vedea diferite rezultate în funcție de numărul de puncte din apropiere cu care este comparată noul punct. 
Numărul de bin-uri din histogramă poate fi și el variat.

### 2. Testare:
##### Rezultate antrenare set poze: 
![TrainPepsi](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/TrainPepsi.jpeg?raw=true)
![TrainCola](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/TrainCola.jpeg?raw=true)
Cele două grafice reprezintă rezultatele în urma antrenării pe setul de poze cu pepsi (albastru) și pe setul de poze cu (cola), în ambele cazuri saturația fiind 0, numărul de bin-uri 1 și distanța euclidiană. Se poate observa că punctele sunt dispersate, doar în anumite zone fiind mai grupate. 

În continuare vom încerca să modificăm valorile care pot fi variate, astfel încât să obținem puncte cât mai grupate, iar performanța clasificatorului să fie cât mai mare.  

##### Rezultate rată de succes cu varieri ale lui k: 
![Samples](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/VariationNoSamples.jpeg?raw=true)
În acest grafic am încercat să ilustrăm cum se modifică rata de succes a clasificării, atunci când variem valoarea lui k (valori între 1 si 29, numere impare). Restul parametrilor fiind cei default și anume: distanța euclidiană, pragul saturației este 0 și numărul de bin-uri este 1. 
Se poate observa că, atât pentru cola cât și pentru pepsi, rata maximă de succes este atunci când valoarea lui k este 13. 

##### Rezultate rată de succes cu varieri ale pragului de saturație: 
![Saturation](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/VariationSaturation.jpeg?raw=true)
Luând în considerare rezultatele anterioare, am variat saturația între 0 și 175, păstrând k egal cu 13. Se poate observa că pentru imaginile cu cola valoarea saturației la care s-a obținut rata de succes maximă (100%) a fost 140, iar dupa această valoare rata de succes a fot constantă. Pentru cola, valoarea cea mai bună a saturației este 80, urmând ca pentru restul valorilor să avem o rată de succes constantă (86.6%). 

##### Rezultate rată de succes cu varieri ale numărului de bin-uri: 
![Bins](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/VariationBins.jpeg?raw=true)
Ținând cont de testările anterioare am trecut la a varia valorile bin-urilor, pornind de la 0 până la 90, din 10 în 10. Am păstrat valoarea 13 pentru k și valoarea 150 pentru saturație (acestea erau valorile cele mai bune pentru ambele categorii) și se poate observa că pentru 60 de bin-uri avem rata cea mai bună de succes. 

##### Testări cu varieri multiple a tuturor parametrilor: 
Ulterior pentru a afla o combinație de valori cât mai bună, am creat o funcție care pentru fiecare dintre cele două distanțe: euclidiană și cosinus, variază pragul saturației între 125 și 175 din 5 în 5, valoarea lui k de la 1 la 29, din doi în doi și valoarea bin-urilor între 5 și 90, din 5 în 5, rezultând 5940 de teste. 

În urma acestora am obținut cel mai bun procent de 98.33% cu urmatoarele valori: Saturație = 170, K = 3, bins = 60 și distanța euclidiană, iar cel mai mic procent de 58.33% cu valorile: Saturație =0, K = 1, bins = 55 și distanța euclidiana.

Totodată am observat că modificarea lui k nu are un impact atât de puternic precum modificarea bin-urilor, așa că în continuare nu vom mai pune atât de mult accent pe valoarea lui k. 

##### Distribuirea punctelor cu cele mai bune valori obținute (saturație = 170, bin-uri = 60):
![ColaSaturatie170bins60](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/ColaSaturatie170bins60.jpeg?raw=true)
![PepsiSaturatie170bins60](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/PepsiSaturatie170bins60.jpeg?raw=true)
În comparație cu distribuirea punctelor din primele imagini prezentate (rezultatele antrenării cu valorile: saturație = 0, bin-uri = 1 și distanța euclidiană) se pot observa îmbunătățiri majore în ceea ce privește gruparea punctelor în ambele cazuri.

### 3. Exemplificarea pașilor pe care îi face clasificatorul pentru un caz concret:
Folosind cele mai bune valori rezultate din testele anterioare, vom prezenta toți pașii de clasificare a unei imagini. 

![PepsiImage](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/PepsiImage.jpeg?raw=true)

Având pragul saturației de 170 și numărul de bin-uri de 60 histograma rezultată este următoarea:

![Histograma](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/Histograma.jpeg?raw=true)

În continuare am arătat, pe graficul rezultat în urma antrenării cu cele mai bune valori găsite, unde este punctul ce reprezintă valoarea imaginii de test.

![ImagineTestIntegrata](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/ImagineTestIntegrata.jpeg?raw=true)

Am dat zoom pe graficul rezultat înainte pentru a evidenția cele mai apropiate 17 puncte de noul punct adăugat (imaginea de test).

![Cele17Puncte](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/Cele17Puncte.jpeg?raw=true)

