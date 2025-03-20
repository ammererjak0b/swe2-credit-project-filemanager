# swe2-credit-project-filemanager

## Instructions:
Implementierung eines Dateiverwaltungssystems mit Binärbaum, verketteten Listen und Sockets in C
In diesem Projekt soll es sich um eine C-Anwendung handeln, die folgende Funktionen umfassen muss:
File-Handling: Lesen und Schreiben von Daten in eine Textdatei.
Dynamische Speicherverwaltung: Verwendung von malloc(), free(), usw. um Strukturen auf dem Heap zu erstellen.
Binärer Suchbaum: Speicherung der geladenen Daten in einem selbst implementierten binären Suchbaum. Duplikate sollen nicht überschrieben werden, sondern innerhalb des entsprechenden Knotens als einfach verkettete Liste gespeichert werden.
Verkettete Listen: Neben dem binären Suchbaum muss eine doppelt verkettete Liste implementiert werden, in die die Daten optional übertragen werden können.
Datenstruktur-Wechsel: Es muss möglich sein, die Daten per Kommando zwischen binärem Suchbaum und doppelt verketteter Liste zu konvertieren.
(Bonus) Sockets: Eine einfache TCP- oder UDP-Kommunikation soll implementiert werden, mit der die Daten zwischen zwei Instanzen der Anwendung übertragen werden können.
Benutzeroberfläche: Eine einfache CLI (Command Line Interface) zur Interaktion mit dem System, inklusive Menüoptionen für das Einfügen, Löschen und Suchen von Daten.

## Output:
Grundlegend soll der User über die CLI:
Eine Datei zum Lesen/Schreiben auswählen.
Daten aus der Datei in den Binärbaum oder die doppelt verkettete Liste laden.
Die Datenstruktur nach Belieben wechseln.
Neue Einträge hinzufügen. (Es soll noch die Möglichkeit geben, neue Einträge einzufügen und dann die Daten (so, dass Liste oder Baum wiederhergestellt werden können) in eine Textdatei zu speichern.)
Die Daten so speichern, dass sie später wieder in den Baum oder die Liste geladen werden können.
(Bonus) Eine Netzwerkverbindung (Sockets) herstellen und Daten zwischen zwei Instanzen der Anwendung übertragen.
