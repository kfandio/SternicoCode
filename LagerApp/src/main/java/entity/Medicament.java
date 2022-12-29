package entity;


public class Medicament {
    private final int idItems;  // Id der Medikamente
    private int quantity;       // Menge der Produkte, die zum Verkaufen bleibt.
    private int soldQuantity;   // Menge der verkauften Produkten
    private int currentQuantity;// Aktuelle Bestand jeder Medikamente
    private int totalUnitSold;  // Gesamte Menge der verkauften Produkten


    public Medicament(int idItems, int quantity, int soldQuantity, int currentQuantity, int totalUnitSold) {
        this.idItems = idItems;
        this.quantity = quantity;
        this.soldQuantity = soldQuantity;
        this.currentQuantity= currentQuantity;
        this.totalUnitSold = totalUnitSold;
    }


    public int getId() {
        return idItems;
    }

    public int getQuantity() {
        return quantity;
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

    public int getSoldQuantity(){
        return soldQuantity;
    }

    public void setSoldQuantity(int soldQuantity) {
        this.soldQuantity = soldQuantity;
    }

    public int getCurrentQuantity() {return currentQuantity;}

    public void setCurrentQuantity(int currentQuantity) {this.currentQuantity = currentQuantity;}
    public int getTotalUnitSold() {return totalUnitSold;}

    public void setTotalUnitSold(int totalUnitSold) {
        this.totalUnitSold = totalUnitSold;
    }


}
