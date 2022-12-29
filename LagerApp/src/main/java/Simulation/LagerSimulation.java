package Simulation;

import Service.LagerService;

import java.util.Timer;
import java.util.TimerTask;

public class LagerSimulation {
    private final Timer timer;
    LagerService ls = new LagerService();

    private int timeInSec;
    private final int taskFreq;
    public LagerSimulation(int inventory, int taskFreq){
        this.timer = new Timer();
        this.taskFreq = taskFreq;
        this.timeInSec = inventory * this.taskFreq;

    }

    public void AppFunction(){
        ls.sellQuantity();
        ls.csvWriter();
        ls.showAllMedicament();
        ls.addMedicament();
        ls.remainingQuantity();
    }
    public void start(){
        ls.showAllMedicament();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {

                System.out.println(timeInSec + " s");

                for (int i = timeInSec; i > 0; i--) {
                    if (timeInSec == (i* taskFreq)+1) {
                        AppFunction();
                    }
                }
                if (timeInSec == 0) {
                    ls.sellQuantity();
                    ls.showAllMedicament();
                    ls.csvWriter();
                    ls.pdfWriter();
                    cancel();
                }
                timeInSec--;
            }
        }, 1000, 1000);
    }
}
