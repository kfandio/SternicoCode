package Service;


import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvFileSource;

import static org.junit.jupiter.api.Assertions.*;

@TestInstance(TestInstance.Lifecycle.PER_CLASS)
class LagerServiceTest {
    LagerService ls = new LagerService();
    @BeforeAll
    public void generateTheCsvFile(){
        ls.csvWriter();
        ls.addMedicament();
    }

    @Test
    public void addMedicamentTest() {
        assertEquals(3, ls.medCount());
    }

    @Test
    public void sellQuantityTest() {
        ls.sellQuantity();
        assertTrue(ls.getSell(0)!=0);
        assertTrue(ls.getSell(1)!=0);
    }

    @Test
    public void allUnitSoldTest() {
        ls.sellQuantity();
        assertTrue(ls.getAllSell(0)!=0);
        assertTrue(ls.getAllSell(1)!=0);
    }
    @ParameterizedTest
    @CsvFileSource(resources = "/Daten1.csv",
                    numLinesToSkip = 1,delimiter = ';')
    public void csvWriterTest(String id, String quantity, String soldQuantity, String currentQuantity) {
        assertNotNull(id);
        assertNotNull(quantity);
        assertNotNull(soldQuantity);
        assertNotNull(currentQuantity);
    }


    @Test
    public void remainingQuantityTest() {
        int newMedQuantity = ls.getNewCurrentQuantity(0);
        int soldQuantity = ls.getSell(0);
        int newQuantity = 123 - soldQuantity;

        System.out.println(newMedQuantity);

        assertTrue(newMedQuantity !=0);
        assertEquals(newQuantity, newMedQuantity);
    }

    @Test
    public void increaseQuantityTest() {
        ls.sellQuantity();
        ls.remainingQuantity();
        int newQuantityIncrease = ls.getIncreaseQuantity(0);
        assertNotEquals(123, newQuantityIncrease);

    }

}