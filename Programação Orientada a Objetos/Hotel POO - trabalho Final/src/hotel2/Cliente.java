package hotel2;

import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Scanner;

public class Cliente{
    public static ArrayList<Cliente> lista = new ArrayList<>();    
    Scanner ler = new Scanner (System.in);
    private String nome,res,email;
    private int idade,cpf;
    boolean reserva;
    public Cliente c;
    public Cliente(){
        
    }
    public Cliente(String nome,String email,int idade,int cpf){
        this.cpf = cpf;
        this.email = email;
        this.nome = nome;
        this.idade = idade;
    }
    
    public  int Consultar(String nome){//pesquisa um cliente passando o nome
        if (lista.isEmpty()){
            System.out.println("Não há clientes cadastrados.");
        }else{
            for (int i=0;i<lista.size();i++){
                if (lista.get(i).nome.equals(nome)){
                    System.out.println("-------------------------");
                    System.out.println("Cliente encontrado!!!");
                    System.out.println("Nome: "+lista.get(i).getNome());                            
                    System.out.println("CPF: "+lista.get(i).getCpf());
                    System.out.println("Email: "+lista.get(i).getEmail());
                    System.out.println("Idade: "+lista.get(i).getIdade()); 
                    return i;
                }  
            }
        }
        System.out.println("Cliente não encontrado");
        return -1;
    }
    
    public void Excluir(String nome){//Exclui um cliente passando o nome
        int i = Consultar(nome);
        if (i!= -1){
            System.out.print("Deseja realmente excluir?(S/N): ");
            res = ler.next();
            if(res.equals("S") || res.equals("s")){
                lista.remove(i);
            }
        }
    }
    
    public void inserir(){//inseri um cliente na lista cliente
       System.out.print("Digite um nome: ");
       this.nome = ler.next();
       System.out.print("Digite um email: ");
       this.email = ler.next();
       System.out.print("Digite a idade: ");
       try{
            this.idade = ler.nextInt();
        }
        catch(InputMismatchException e){
            System.out.print("Informe apenas números. Ex: 25: ");
            System.exit(0);
        }
       
       System.out.print("Digite o CPF: ");
       try{
            this.cpf = ler.nextInt();
        }
        catch(InputMismatchException e){
            System.out.print("Informe apenas números. Ex: 13243021600: ");
            System.exit(0);
        }
       lista.add(new Cliente(this.nome,this.email,this.idade,this.cpf));
    }   

    public static ArrayList<Cliente> getLista() {
        return lista;
    }

    public static void setLista(ArrayList<Cliente> lista) {
        Cliente.lista = lista;
    }

    public Scanner getLer() {
        return ler;
    }

    public void setLer(Scanner ler) {
        this.ler = ler;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public int getIdade() {
        return idade;
    }

    public void setIdade(int idade) {
        this.idade = idade;
    }

    public int getCpf() {
        return cpf;
    }

    public void setCpf(int cpf) {
        this.cpf = cpf;
    }  
}
