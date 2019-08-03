package hotel2;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class GerarNota {
    
    Cliente cliente = new Cliente();

    public static void escritor(String path) throws IOException {
        BufferedWriter buffWrite = new BufferedWriter(new FileWriter(path));
        String linha = "";
        Scanner in = new Scanner(System.in);
        System.out.println("Boleto Criado!");
        System.out.println();
        
        
        buffWrite.append(linha + " Cliente: ");
        
        buffWrite.close();
    
 
    }
}
