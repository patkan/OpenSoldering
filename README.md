OpenSoldering
=============

###Kurzbeschreibung
OpenSource Lötstation mit (hoffentlich mal) Unterstützung für verschiedene JBC-, Weller- und Ersa-Lötkolben


###Aufbau
Modular. Kommunikation über RS485 mit dem SB9-Bussystem

###Ziel
eine OpenSource Lötstation mit Basisstation und einzelnen Satellitenstationen, die jeweils ein Lötgerät (Kolben, Zange, Pinzette) ansteuern. Auch geeignet für Gruppen oder Werkstätten, die mehrere Lötplätze brauchen.


###Status Quo
- Modul für den JBC-Lötkolben T245A in Entwicklung.
- Thermospannung im Arbeitspunkt für C245 Kartusche 4,2mV; Aufnahme der Kennlinie fehlt noch.

###TODOs
- Aufbau und ausführliche Tests am Lötkolben, Programmierung der PI-Regelung mit Vorsteuerung, (vermutlich kein PID-Konzept nötig) und Bau der Kontrollstation.
- Planung für ein Weller-Modul für die modernen Lötspitzen des WXMP-Lötkolbens, die einen einfachen und günstigen Lötkolben versprechen.
- Planung der Kontrollstation:
	* Display: OLED? gLCD?
	* Eingabe: Drehknopf? Touchscreen?
	* zusätzliche Konnektivität: IoT? Bluetooth? Lötrauchabsaugung?
	* Reglerprofile: Optimierung auf Ausregelzeit/minimale Überschwingung?
