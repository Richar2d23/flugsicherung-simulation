# Flugsicherung-simulation
## Überblick
Das Programm dient der Simulation von mehreren Flugzeugen im Luftraum, sowie der Erkennung und Behebung möglicher Abstand Konflikte.
## Konflikterkennung
Die Konflikterkennung prüft jede simulierte Minute alle einzigartigen Paare auf den vertikalen und horizontalen Mindestabstand. Ist der vertikale Abstand kleiner als 1000 ft und gleichzeitig der horizontale Abstand unter 5 NM, steigt das höhere Flugzeug auf einen Höhenunterschied von 1000 ft.
## Aufbau
Flugzeuge werden in der Klasse `Flugzeug` gefasst. Ihre Daten (Flugnummer, Höhe, Position und Geschwindigkeit) sind privat und werden durch einen Konstruktor zugewiesen. Von außen lesbar sind Flugnummer und Höhe über `getFlugnummer()` und `getHoehe()`. Die Höhe ändert sich nur über `steige()`, die Position nur über `bewege()`. Weitere Elementfunktionen prüfen den vertikalen Konflikt und berechnen den horizontalen Abstand zweier Flugzeuge, verbunden werden beide Prüfungen über die Funktion `konflikt`. Die Mindestabstände stehen als Konstanten `MIN_HOEHENABSTAND_FT` und `MIN_HORIZONTALABSTAND_NM` am Anfang der Datei.

Zum Programmstart laufen vier automatische Test, die die Konflikt Vorhersage, das Steigen und die Abstandsrechnung mit erwarteten Ergebnissen prüft. Nach Start werden zuerst Flugzeuge in einem Vektor gespeichert, bevor vor der eigentlichen Simulation eine Vorhersage mittels Kopien aus dem Vektor gestartet wird, ob ein Konflikt auftreten wird. Nach dessen Abschluss startet die Simulation innerhalb einer Minutenschleife und bewegt nun die originalen Flugzeuge im Vektor. Konflikte werden dann durchs Steigen des höheren Flugzeug behoben.
## Eingabe
Die Eingabe erfolgt über eine separate Datei flugzeuge.txt, in welcher Flugzeug in Reihenfolge mit Flugnummer, Höhe in Fuß, x-Koordinate und y-Koordinate in nautischen Meilen, sowie Bewegung vx und vy in NM pro Minute gespeichert sind. Das Einlesen der Datei erfolgt über eine while Schleife in den Vektor. Es steht pro Zeile ein Flugzeug, z.B.: 'LH123 35000 0 0 7.5 0'
## Verbesserungen
Verbesserungswürdig ist die Konfliktauflösung, die bis jetzt nur durch das Steigen um den exakt fehlenden Betrag zu 1000 ft Unterschied Konflikte löst. Letzteres wurde bewusst zur Vereinfachung umgesetzt. Außerdem enthält das Programm noch eine Reihe an festen Werten, welche mit Variablen ersetzt werden könnten, wie etwa die Dauer der Vorhersage und die der Simulation.

## Ausführen:
Im Terminal:
main.cpp und flugzeuge.txt in einen Ordner legen. Ordner öffnen. Weitere Befehle im Terminal ausführen.
```
g++ -std=c++20 main.cpp -o simulation
./simulation
```

Alternativ main.cpp und flugzeuge.txt in Replit oder OnlineGDB einfügen und 'Run' drücken.

## Beispielausgabe:
```
Warnung: LH123 und DL321 in 1 Minute(n) im Konflikt
Minute 1: LH123 und DL321: Konflikt Abstand 3.3541 NM
 -> Flugzeug Nummer DL321 steigt um 600 ft
LH123: Höhe: 35000 ft
BA456: Höhe: 30000 ft
AF789: Höhe: 40000 ft
DL321: Höhe: 36000 ft
```
