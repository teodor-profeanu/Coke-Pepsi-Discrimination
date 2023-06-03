# **_Pepsi vs Cola - Discriminare_**
>Procesarea Imaginilor
>
>Studenți: Teodor Profeanu, Adela Tatar
>
>Facultatea: Automatică și Calculatoare
>
>Profesor îndrumător: Vicaș Cristian
>
> https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination


## 1. Descrierea proiectului:
Clasificarea pe bază de histogramă de culoare a unor imagini cu sticle/doze de pepsi și cola în categoria din care fac parte. 

Implementarea clasificatorului (noi am ales knn): 
- Acesta primește un set antrenat de poze și o poză de test pe care o clasifică în funcție de hue (culoare) în categoria pepsi sau cola. 
- Antrenarea se face cu 340 de poze etichetate (170 cu pepsi si 170 cu cola), iar pentru testare avem 60 de poze (cate 30 din fiecare).
- Clasificatorul folosește un prag minim de saturație, pentru a ignora culorile cum ar fi alb sau negru.
- Pentru a calula distanța dintre puncte avem două variante, distanța euclidiană și distanța cosinus. 
- Numărul de vecini ai clasificatorului Knn nu este unul fix, ci poate fi variat pentru a vedea diferite rezultate în funcție de numărul de puncte din apropiere cu care este comparată noul punct. 
- Numărul de bin-uri din histogramă poate fi și el variat.

## 2. Testare:
### 2.1 Rezultatele după antrenarea inițială: 

![TrainPepsi](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/TrainPepsi.jpeg?raw=true)

![TrainCola](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/TrainCola.jpeg?raw=true)

Cele două grafice reprezintă rezultatele în urma antrenării pe setul de poze cu pepsi (albastru) și pe setul de poze cu cola (roșu), în ambele cazuri saturația minimă fiind 0, numărul de bin-uri 1 și distanța euclidiană. Se poate observa că punctele sunt dispersate, iar zonele grupate au margini foarte neclare.

În continuare vom încerca să modificăm valorile care pot fi variate, astfel încât să obținem puncte cât mai grupate, iar performanța clasificatorului să fie cât mai mare.  

### 2.2 Rata de succes în funcție de numărul de vecini: 

![Samples](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/VariationNoSamples.jpeg?raw=true)

În acest grafic am încercat să ilustrăm cum se modifică rata de succes a clasificării, atunci când variem valoarea lui k (valori între 1 si 29, numere impare). Restul parametrilor fiind cei default și anume: distanța euclidiană, pragul saturației este 0 și numărul de bin-uri este 1. 

Se poate observa că, atât pentru cola cât și pentru pepsi, rata maximă de succes este atunci când valoarea lui k este 13. 

### 2.3 Rata de succes în funcție de pragului de saturație: 

![Saturation](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/VariationSaturation.jpeg?raw=true)

Luând în considerare rezultatele anterioare, am variat saturația între 0 și 175, păstrând k egal cu 13. Se poate observa că pentru imaginile cu cola valoarea saturației minime la care s-a obținut rata de succes maximă (100%) a fost la valorile mai mari de 140. Pentru pepsi, valoarea cea mai bună a saturației începe de la 80, urmând ca pentru restul valorilor să avem o rată de succes constantă (86.6%). Putem deduce că valorile aproape maxime ale saturației au rezultate mai bune.

### 2.4 Rata de succes în funcție de dimensiunea unui bin: 

![Bins](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/VariationBins.jpeg?raw=true)

Ținând cont de testările anterioare am trecut la a varia dimensiunea binurilor histogramei, pornind de la 0 până la 90 (de la 180 binuri până la 2), din 10 în 10. Am păstrat valoarea 13 pentru k și valoarea 150 pentru saturație (acestea erau valorile cele mai bune pentru ambele categorii) și se poate observa că pentru dimensiunea 60 a unui bin avem rata cea mai bună de succes (3 binuri/histogramă). 

### 2.5 Testări cu variații multiple a tuturor parametrilor: 

Ulterior, pentru a afla cea mai bună combinație de parametrii, am creat o funcție care pentru fiecare dintre cele două distanțe: euclidiană și cosinus, variază pragul saturației între 125 și 175 din 5 în 5, valoarea lui k de la 1 la 29, din doi în doi și valoarea bin-urilor între 5 și 90, din 5 în 5, rezultând 5940 de teste. 

În urma acestora am obținut cel mai bun procent de 98.33% cu următorii parametrii: Saturație = 170, K = 3, bins = 60 și distanța euclidiană, iar cel mai mic procent de 58.33% cu valorile: Saturație = 0, K = 1, bins = 55 și distanța euclidiana.

Totodată am observat că modificarea lui k nu are un impact atât de puternic precum modificarea bin-urilor, așa că în continuare nu vom mai pune atât de mult accent pe valoarea lui k. 

![ColaSaturatie170bins60](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/ColaSaturatie170bins60.jpeg?raw=true)
![PepsiSaturatie170bins60](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/PepsiSaturatie170bins60.jpeg?raw=true)

În imagine avem saturația minimă 170 și numărul de binuri fiind 3 (dimensiunea unui bin 60). În comparație cu distribuirea punctelor din primele imagini prezentate (rezultatele antrenării cu valorile: saturație = 0, bin-uri = 180 și distanța euclidiană) se pot observa îmbunătățiri majore în ceea ce privește gruparea punctelor în ambele cazuri.

## 3. Exemplificarea pașilor:

Folosind cele mai bune valori rezultate din testele anterioare, vom prezenta toți pașii de clasificare a unei imagini. 

![PepsiImage](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/PepsiImage.jpeg?raw=true)

Având pragul saturației de 170 și numărul de bin-uri fiind 3, histograma rezultată este următoarea:

![Histograma](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/Histograma.jpeg?raw=true)

În continuare am arătat unde se încadrează pe grafic imaginea noastră față de cele folosite pentru antrenare:

![ImagineTestIntegrata](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/ImagineTestIntegrata.jpeg?raw=true)

Am dat zoom pe graficul rezultat înainte pentru a evidenția cele mai apropiate 17 puncte de noul punct adăugat (imaginea de test). 9 dintre ele sunt etichetate "Pepsi" și 8 sunt etichate "Cola". În final clasificatorul ne va spune că în magine apare "Pepsi"

![Cele17Puncte](https://github.com/teodor-profeanu/Coke-Pepsi-Discrimination/blob/main/graphs/Cele17Puncte.jpeg?raw=true)

