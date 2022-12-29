package Service;

import Controller.MedicamentListGenerator;
import com.itextpdf.kernel.colors.DeviceRgb;
import com.itextpdf.kernel.pdf.PdfDocument;
import com.itextpdf.kernel.pdf.PdfWriter;
import com.itextpdf.layout.Document;
import com.itextpdf.layout.borders.Border;
import com.itextpdf.layout.element.Cell;
import com.itextpdf.layout.element.Paragraph;
import com.itextpdf.layout.element.Table;
import com.itextpdf.layout.properties.TextAlignment;
import com.itextpdf.layout.properties.VerticalAlignment;


import entity.Medicament;

import java.io.*;
import java.util.Random;

public class LagerService {

    private int countFile = 1;

    MedicamentListGenerator mlg = new MedicamentListGenerator();

    // Funktion, die ermöglicht, neue Medikament in der Lister einzufügen.
    public void addMedicament(){
        Random rdw = new Random();
        int maxId = 9999999;
        int minId = 1000000;
        int idItems = rdw.nextInt((maxId - minId) + 1) + minId;
        int maxQuantity = 200;
        int minQuantity = 50;
        int quantity = rdw.nextInt((maxQuantity - minQuantity) + 1) + minQuantity;

        Medicament medicine = new Medicament(idItems, quantity, 0, quantity,0);
        this.mlg.addMedicament(medicine);
    }
    /* Funktion zur Überprüfung der AddMedicament() Funktion.
                  Abruf in Test Klasse LagerServiceTest*/
    public int medCount(){
        return mlg.count();
    }
    // Funktion die, die verkaufte Anzahl generiert.
    public void sellQuantity(){
        for (int i = 0; i < this.mlg.count(); i++) {
            Medicament medicine = this.mlg.getMedicament(i);
            if (medicine.getSoldQuantity() ==0){
                Random rdw = new Random();
                int sellQuantity = rdw.nextInt((medicine.getQuantity() -1)+1) + 1;
                medicine.setSoldQuantity(sellQuantity);
                int currentQuantity = medicine.getQuantity() - medicine.getSoldQuantity();
                medicine.setCurrentQuantity(currentQuantity);
            }
        }
        allUnitSold();
    }
    /* Funktion zur Überprüfung der sellQuantity() Funktion.
                Abruf in Test Klasse LagerServiceTest*/
    public int getSell(int index){
        return mlg.getMedicament(index).getSoldQuantity();
    }

    // Funktion die, die gesamte verkaufte Anzahl von Medikament nach jeder Inventur generiert.
    // Wird abgerufen in sellQuantity Funktion.
    public void allUnitSold(){
        for (int i = 0; i < this.mlg.count(); i++) {
            Medicament medicine = this.mlg.getMedicament(i);
            if (medicine.getSoldQuantity() !=0){
                int allSold = medicine.getSoldQuantity() + medicine.getTotalUnitSold();
                medicine.setTotalUnitSold(allSold);
            }
        }
    }
    /* Funktion zur Überprüfung der allUnitSold()Funktion.
                Abruf in Test Klasse LagerServiceTest*/
    public int getAllSell(int index){
        return mlg.getMedicament(index).getTotalUnitSold();
    }


    //  Funktion zum Schreiben der Daten in CSV-Dateien nach jeder Inventur
    public void csvWriter(){

        String id = "PharmaID";
        String quantity = "Stückzahl";
        String sellQuantity = "Verkaufte Menge";
        String currentQuantity = "Aktuelle Menge";

        try{
            //File file = new File("/Users/kevinfandio/Desktop/Java/LagerApp/Daten" + countFile + ".csv");
            File file = new File("/Users/kevinfandio/Desktop/Java/Test/SternicoCode/LagerApp/Daten" + countFile + ".csv");
            //File file = new File("/Users/kevinfandio/Desktop/Java//Test/SternicoCode/LagerApp/" +
            //                "src/test/java/resources/Daten" + countFile + ".csv");
            countFile++;
            /*
            System.out.println("Writing to " + file);
            if (!file.exists()) {
                file.createNewFile();
            }
            */
            FileWriter writer = new FileWriter(file);
            BufferedWriter bw = new BufferedWriter(writer);
            String line1 = String.format("%s;%s;%s;%s%n", id, quantity, sellQuantity, currentQuantity);
            bw.write(line1);

            for (int i = 0; i < this.mlg.count(); i++) {
                Medicament medicine = this.mlg.getMedicament(i);

                String line = String.format("%d;%d;%d;%d%n", medicine.getId(), medicine.getQuantity(),
                        medicine.getSoldQuantity(), medicine.getCurrentQuantity());

                bw.write(line);
            }
            bw.close();
            writer.close();
            System.out.println("Eine CSV-Datei wurde hergestellt.");

        } catch (IOException e){
            e.printStackTrace();
        }
    }

    // Funktion die ermöglicht, der neue Bestand nach dem Verkauf zu berechnet.
    public void remainingQuantity(){
        for (int i = 0; i < this.mlg.count(); i++) {
            Medicament medicine = this.mlg.getMedicament(i);

            if (medicine.getSoldQuantity() !=0){
                int currentQuantity = medicine.getQuantity() - medicine.getSoldQuantity();
                medicine.setQuantity(currentQuantity);
                medicine.setSoldQuantity(0);
            }
        }
        increaseQuantity();
    }

    /* Funktion zur Überprüfung der remainingQuantity() Funktion.
            Abruf in Test Klasse LagerServiceTest*/
    public int getNewCurrentQuantity(int index){
        return mlg.getMedicament(index).getCurrentQuantity();
    }


    /* Funktion ermöglicht, Medikamente aufzustocken, wenn der neue Bestand < 50 ist.
            Wird in Funktion remainingQuantity() abgerufen*/
    public void increaseQuantity(){
        for (int i = 0; i < this.mlg.count(); i++) {
            Medicament medicine = this.mlg.getMedicament(i);
            Random rdw = new Random();
            int maxIncrease = 200;
            int minIncrease = 50;
            int increase = rdw.nextInt((maxIncrease - minIncrease) + 1) + minIncrease;
            if (medicine.getQuantity() < minIncrease) {
                int newQuantity = medicine.getQuantity() + increase;
                medicine.setQuantity(newQuantity);
                int currentQuantity = medicine.getQuantity() - medicine.getSoldQuantity();
                medicine.setCurrentQuantity(currentQuantity);
            }else {
                medicine.setQuantity(medicine.getQuantity());
            }
        }
    }

    /* Funktion zur Überprüfung der increaseQuantity() Funktion.
            Abruf in Test Klasse LagerServiceTest*/
    public int getIncreaseQuantity(int index){
        return mlg.getMedicament(index).getQuantity();
    }


    // Funktion zur Darstellung jeder Schritte (sell, add or increase of Medicament) in der Console
    public void showAllMedicament(){
        System.out.println("Die Liste aller Medikamente lautet wie folgt :");
        System.out.println("PharmaID\tStz\tVer\tAS\tGV");

        for (int i = 0; i<this.mlg.count(); i++){
            Medicament medicine = this.mlg.getMedicament(i);
            System.out.println("0" + medicine.getId() + "\t" + medicine.getQuantity() + "\t" + medicine.getSoldQuantity()
                    + "\t"+ medicine.getCurrentQuantity() +"\t" + medicine.getTotalUnitSold());
        }

    }



    /* Funktion die ermöglicht, der Anzahl der verkauften Medikamente im Laufe des Jahres
    in einer PDF-Datei zu speichern */
    public void pdfWriter() {

        try {
            String path = "/Users/kevinfandio/Desktop/Java//Test/SternicoCode/LagerApp/Bilanz.pdf";
            PdfWriter pdfWriter = new PdfWriter(path);

            PdfDocument pdfDocument = new PdfDocument(pdfWriter);
            //pdfDocument.addNewPage();
            Document document = new Document(pdfDocument);


            float[] columHeadWidth = {280f, 280f};
            Table table1 = new Table(columHeadWidth);
            table1.setBackgroundColor(new DeviceRgb(142, 231, 249));
            table1.addCell(new Cell().add(new Paragraph("Jährliche Bilanz")
                    .setFontSize(20).setBold()
                    .setTextAlignment(TextAlignment.CENTER)
                    .setMarginTop(30f)
                    .setMarginBottom(30f)).setBorder(Border.NO_BORDER).setVerticalAlignment(VerticalAlignment.MIDDLE));

            table1.addCell(new Cell().add(new Paragraph("Haeger Consulting\nKontakt\nBrunnenallee 6\n53177 Bonn\ninfo@haeger-consulting.de")
                    .setTextAlignment(TextAlignment.RIGHT)
                    .setMarginTop(30f)
                    .setMarginBottom(30f)
                    .setMarginRight(10f)).setBorder(Border.NO_BORDER));

            document.add(table1);
            document.add(new Paragraph("\n"));

            float[] columnEmploy = {80, 300, 100, 80};
            Table table2 = new Table(columnEmploy);

            table2.addCell(new Cell(0, 4).add(new Paragraph("Mitarbeiter").setBold().setFontSize(15)).setBorder(Border.NO_BORDER));
            table2.addCell(new Cell().add(new Paragraph("Name:")).setBorder(Border.NO_BORDER));
            table2.addCell(new Cell().add(new Paragraph("Kevin Fandio")).setBorder(Border.NO_BORDER));
            table2.addCell(new Cell().add(new Paragraph("Datum:")).setBorder(Border.NO_BORDER));
            table2.addCell(new Cell().add(new Paragraph("01-01-2023")).setBorder(Border.NO_BORDER));

            document.add(table2);
            document.add(new Paragraph("\n"));


            float[] columnWidth = {50f, 255f, 255f};

            Table table = new Table(columnWidth);

            Cell col = new Cell();
            col.add(new Paragraph("Nr.").setBold())
                    .setFontSize(20).setBackgroundColor(new DeviceRgb(125, 125, 125));
            table.addCell(col);

            Cell col1 = new Cell();
            col1.add(new Paragraph("PharmaID").setBold())
                    .setFontSize(20).setBackgroundColor(new DeviceRgb(125, 125, 125));
            table.addCell(col1);

            Cell col2 = new Cell();
            col2.add(new Paragraph("Verkaufte Menge").setBold())
                    .setFontSize(20).setBackgroundColor(new DeviceRgb(125, 125, 125));
            table.addCell(col2);


            for (int i = 0; i < this.mlg.count(); i++) {
                Medicament medicine = this.mlg.getMedicament(i);
                if ((i % 2) == 0) {
                    table.addCell(new Cell().add(new Paragraph(String.valueOf(i+1))
                            .setBackgroundColor(new DeviceRgb(255, 255, 255))));
                    table.addCell(new Cell().add(new Paragraph(String.valueOf(medicine.getId()))
                            .setBackgroundColor(new DeviceRgb(255, 255, 255))));
                    table.addCell(new Cell().add(new Paragraph(String.valueOf(medicine.getTotalUnitSold()))
                            .setBackgroundColor(new DeviceRgb(255, 255, 255))));
                } else {
                    table.addCell(new Cell().add(new Paragraph(String.valueOf(i+1))
                            .setBackgroundColor(new DeviceRgb(142, 142, 142))));
                    table.addCell(new Cell().add(new Paragraph(String.valueOf(medicine.getId()))
                            .setBackgroundColor(new DeviceRgb(142, 142, 142))));
                    table.addCell(new Cell().add(new Paragraph(String.valueOf(medicine.getTotalUnitSold()))
                            .setBackgroundColor(new DeviceRgb(142, 142, 142))));
                }
            }

            document.add(table);
            document.close();
            System.out.println("Eine Pdf-Datei wurde hergestellt.");
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    }
