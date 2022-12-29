package Controller;

import entity.Medicament;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class MedicamentListGeneratorTest {

    int id = 43453;
    int quantity = 43;
    int soldQuantity = 43;
    int currentQuantity = 5;
    int totalUnitSold = 0;

    Medicament med = new Medicament(id, quantity, soldQuantity,currentQuantity, totalUnitSold);
    MedicamentListGenerator mlg = new MedicamentListGenerator();
    @Test
    public void addMedicamentTest() {
        mlg.addMedicament(med);
        assertEquals(3, mlg.count());
    }

    @Test
    public void getMedicamentTest() {
        mlg.addMedicament(med);
        int idGet = mlg.getMedicament(2).getId();
        int quantityGet = mlg.getMedicament(2).getQuantity();
        int soldQuantityGet = mlg.getMedicament(2).getSoldQuantity();
        int currentQuantityGet = mlg.getMedicament(2).getCurrentQuantity();
        int totalUnitSoldGet = mlg.getMedicament(2).getTotalUnitSold();

        assertEquals(id, idGet);
        assertEquals(quantity, quantityGet);
        assertEquals(soldQuantity, soldQuantityGet);
        assertEquals(currentQuantity, currentQuantityGet);
        assertEquals(totalUnitSold, totalUnitSoldGet);
    }





}