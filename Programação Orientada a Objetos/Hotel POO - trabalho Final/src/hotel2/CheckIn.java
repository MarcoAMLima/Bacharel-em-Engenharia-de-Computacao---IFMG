package hotel2;

import static hotel2.CheckIn.reserve;
import java.util.Scanner;
import hotel2.Quarto;
import java.util.ArrayList;

public class CheckIn {
    Scanner ler = new Scanner (System.in);
    private int numSimples,numCasal,TipoQuarto,bagaca,cod;
    private String resp, resp3,nome;
    Cliente cliente = new Cliente();
    private double Total;
    public static ArrayList<CheckIn> reserve = new ArrayList<>();

    public CheckIn() {     
    }
    
    public CheckIn(int TipoQuarto,String nome,double Total,int cod){
        this.TipoQuarto = TipoQuarto;
        this.nome = nome;
        this.Total = Total;
        this.cod = cod;
    }
    
    public int ConsultarReserva(String nome){//consultar uma reserva passando o nome
        int q=0;
        if (reserve.isEmpty()){
            System.out.println("Não há reservas cadastradas");
        }else{
            for(int i=0;i<reserve.size();i++){
                if (reserve.get(i).nome.equals(nome)){
                    q = reserve.get(i).getTipoQuarto();
                    System.out.println("-------------------------");
                    System.out.println("Reserva encontrada!!!");
                    System.out.println("Nome: "+reserve.get(i).getNome());
                    System.out.println("Codigo: "+reserve.get(i).getcod());
                    if(q==1){
                        System.out.println("Tipo de quarto: Simples");
                    }else{
                        System.out.println("Tipo de quarto: Casal");
                    }
                    System.out.println("Total a pagar: "+reserve.get(i).getTotal());
                }
            }
            return 1;
        }
        System.out.println("Reserva não encontrada");
        return -1;
    }
    
    /*Essa função pesquisa se a reserva existe pelo nome do cliente, depois pesquisa e exclui pelo codigo da reserva*/
    public void ExcluirReserva(String nome){
        int cod=0;
        int i = ConsultarReserva(nome);
        if (i != -1){ //não tá entrando
            System.out.print("Para confirmar a exclusão digite o codigo da reserva: ");
            cod = ler.nextInt();
            int j = Consultar2(cod);
            reserve.remove(j);
        }
        
    }
    
    //metodo para retornar a posição pesquisando pelo codigo pois pode ter mais de uma reserva no nome do cliente
    public int Consultar2(int cod){
        if(reserve.isEmpty()){
            System.out.println("Não há reservas Cadastradas!");
        } else {
            for(int i=0; i<reserve.size();i++){
                if(reserve.get(i).cod == cod){
                   return i; 
                }  
            }
        }
        return -1;
    }
    
    
    // essa função faz uma reserva
    public void reserva(String nome){// essa função faz uma reserva
        do{
            bagaca = cliente.Consultar(nome);//tratamento se o cliente não for cadastrado
            if(bagaca == -1){
                System.out.println("O cliente não está cadastrado "
                    + "para efetuar uma reserva, ele precisa estar cadastrado. "
                    + "Deseja efetuar cadastrato?(S/N)");
                resp = ler.next();
                if((resp.equals("S")) || (resp.equals("s"))){
                    cliente.inserir();
                }else{
                    return;
                }
            }
            
        if(bagaca != -1){
                this.nome = nome;
        }
        }while(bagaca == -1);
        do{                        
            System.out.println("\nQual o tipo de quarto escolhido? \n 1: Quarto Simples \n 2: Quarto Casal");
            TipoQuarto = ler.nextInt();
            if(TipoQuarto==1){
                Quarto quarto = new QuartoSimples();
                System.out.print("Deseja adicionar frigobar?(S/N): ");
                resp3 = ler.next();
                    if((resp3.equals("S")) || (resp3.equals("s"))){
                        quarto = new DecFrigobar(quarto);
                    } 
                System.out.print("Deseja adicionar banheira?(S/N): ");
                resp3 = ler.next();
                    if(resp3.equals("S") || (resp3.equals("s"))){
                        quarto = new DecBanheira(quarto);
                    }
                System.out.println(quarto.getDescricao()+". Total a pagar: R$"+ quarto.custoQuarto());
                Total = quarto.custoQuarto();
                numSimples--;
                cod++;
                
            } else{
                if(TipoQuarto==2){
                    Quarto quarto = new QuartoCasal();
                    System.out.print("Deseja adicionar frigobar?(S/N): ");
                    resp3 = ler.next();
                        if((resp3.equals("S")) || (resp3.equals("s"))){
                           quarto = new DecFrigobar(quarto);
                          } 
                    System.out.print("Deseja adicionar banheira?(S/N): ");
                    resp3 = ler.next();
                        if((resp3.equals("S")) || (resp3.equals("s"))){
                            quarto = new DecBanheira(quarto);
                        }              
                    System.out.println(quarto.getDescricao()+ ". Total a pagar: R$"+ quarto.custoQuarto());
                    numCasal--;
                    cod++;
                    Total = quarto.custoQuarto();
                    
                } else{ 
                    System.out.println("Quarto não especificado");//tá entrando aqui mesmo se o quarto for especificado
                }
            }
                
                System.out.print("Concluir Reserva?(S/N): ");
                resp = ler.next();
                if ((resp.equals("s")) || (resp.equals("S"))){
                    reserve.add(new CheckIn(this.TipoQuarto,this.nome,this.Total,this.cod));
                }
                
                
                System.out.println("Temos disponíveis "+numSimples+" Quartos Simples e " +numCasal+" Quartos para Casais.");
                System.out.print("Deseja efetuar outra reserva para este cliente?(S/N): ");
                resp = ler.next();
      }while(resp.equals("S") || (resp.equals("s")));
    }
    
    public int getNumSimples(){
        return numSimples;
    }

    public void setNumSimples(int numSimples) {
        this.numSimples = numSimples;
    }

    public int getNumCasal() {
        return numCasal;
    }

    public void setNumCasal(int numCasal) {
        this.numCasal = numCasal;
    }

    public int getTipoQuarto() {
        return TipoQuarto;
    }

    public void setTipoQuarto(int TipoQuarto) {
        this.TipoQuarto = TipoQuarto;
    }

    public String getResp() {
        return resp;
    }

    public void setResp(String resp) {
        this.resp = resp;
    }

    public String getResp3() {
        return resp3;
    }

    public void setResp3(String resp3) {
        this.resp3 = resp3;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public double getTotal() {
        return Total;
    }

    public void setTotal(double Total) {
        this.Total = Total;
    }

    public static ArrayList<CheckIn> getLista() {
        return reserve;
    }

    public static void setLista(ArrayList<CheckIn> lista) {
        CheckIn.reserve = lista;
    }
    
    public int getcod() {
        return cod;
    }

    public void setcod(int cod) {
        this.cod = cod;
    }
            
}  
