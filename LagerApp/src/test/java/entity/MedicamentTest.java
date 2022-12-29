package entity;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class MedicamentTest {

    int id = 1234;
    int quantity = 65;
    int soldQuantity = 3;
    int currentQuantity = quantity;
    int totalUnitSold = 0;
    Medicament medicament = new Medicament(id, quantity, soldQuantity,currentQuantity,totalUnitSold);

    @Test
    public void quantityTest(){
        int idValue = 98867;
        medicament.setQuantity(idValue);
        assertEquals(idValue, medicament.getQuantity());
    }

    @Test
    public void soldQuantityTest(){
        int soldCount = 10;
        medicament.setSoldQuantity(soldCount);
        assertEquals(soldCount, medicament.getSoldQuantity());
    }

    @Test
    public void currentQuantityText(){
        int current = 7;
        medicament.setCurrentQuantity(current);
        assertEquals(current, medicament.getCurrentQuantity());
    }

    @Test
    public void totalUnitSold(){
        int total = 4;
        medicament.setTotalUnitSold(total);
        assertEquals(total, medicament.getTotalUnitSold());
    }



}