package org.example;

import Simulation.LagerSimulation;
public class LagerApp {

    public static void main(String[] args) {

        int inventoryNumber = 12;       // Anzahl der Inventur. Für ein Jahr wäre den 12
        int taskFrequency = 2;         // Zeitraum der Inventur in Sekunde

        LagerSimulation simulation = new LagerSimulation(inventoryNumber, taskFrequency);
        simulation.start();


    }
}