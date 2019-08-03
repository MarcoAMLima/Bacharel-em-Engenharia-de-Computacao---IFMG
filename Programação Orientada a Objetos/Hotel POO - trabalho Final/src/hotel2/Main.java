package hotel2;

import static hotel2.Cliente.lista;
import java.util.ArrayList;
import java.util.Scanner;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;


public class Main { 
    public static void main(String[] args) throws IOException{
        CheckIn c = new CheckIn();
        Cliente cliente = new Cliente();
        Scanner ler = new Scanner (System.in);
        String nome,res = null;
        System.out.print("Quantos quartos de Casal estão disponíveis? ");
        c.setNumCasal(ler.nextInt());
        System.out.print("Quantos quartos Simples  estão disponíveis? ");
        c.setNumSimples(ler.nextInt());
        int op = 0;
        do{
            System.out.println("--------------------------------------------------\n"
                             + "------------------ Hotel Bambuí ------------------\n"
                             + "1 - Cadastrar cliente.\n"
                             + "2 - Consultar cliente.\n"
                             + "3 - Excluir cliente.\n"
                             + "4 - Fazer reserva.\n"
                             + "5 - pesquisar reserva.\n"
                             + "6 - Excluir reserva.\n"
                             + "7 - Gerar nota.\n"
                             + "8 - Sair.\n"
                             + "--------------------------------------------------\n");
            op = ler.nextInt();
            switch(op){
                case 1:
                    do{
                        cliente.inserir();
                        System.out.print("Deseja cadastrar mais um cliente?(S/N): ");
                        res = ler.next();
                    }while(res.equals("S") || res.equals("s"));
                  break;
                case 2:
                  System.out.print("Digite o nome a ser pesquisado: ");
                  nome = ler.next();
                  cliente.Consultar(nome);                
                  break;
                case 3:
                    System.out.print("Digite o nome a ser excluido: ");
                    nome = ler.next();
                    cliente.Excluir(nome);
                    break;
                case 4:
                    System.out.print("Digite o nome para quem quer reservar: ");
                    nome = ler.next();
                    c.reserva(nome);
                    break;
                case 5:
                    System.out.print("Digite o nome do autor da reserva: ");                    
                    nome = ler.next();
                    
                    c.ConsultarReserva(nome);
                    break;
                case 6:
                    System.out.print("Digite o nome do autor da reserva a ser excluida: ");
                    nome = ler.next();
                    c.ExcluirReserva(nome);
                    break;   
                case 7:
                    String path = "C:\\Users\\Laxus\\Desktop\\hotel3\\hotel2\\trab.txt";

        GerarNota.escritor(path);
                    
                    break;
                case 8:
                    System.out.println("-----Thanks-----");
                    break;
                default:
                    System.out.println("opção invalida!");
                    break;
            }
        }while(op != 8);       
    }     
}