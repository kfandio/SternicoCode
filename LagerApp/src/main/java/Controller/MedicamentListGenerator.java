package Controller;

import entity.Medicament;

import java.util.ArrayList;
import java.util.List;

public class MedicamentListGenerator {

    private final List<Medicament> listOfMedicine;

    public MedicamentListGenerator (){
        this.listOfMedicine = new ArrayList<>();
        this.listOfMedicine.add(new Medicament(4324188, 123, 0, 123,0));
        this.listOfMedicine.add(new Medicament(1126111, 78, 0,  78, 0));

    }

    public void addMedicament(Medicament medicine){
        this.listOfMedicine.add(medicine);
        count();
    }

    public int count(){
        return this.listOfMedicine.size();
    }

    public Medicament getMedicament(int index){
        return this.listOfMedicine.get(index);
    }


}




