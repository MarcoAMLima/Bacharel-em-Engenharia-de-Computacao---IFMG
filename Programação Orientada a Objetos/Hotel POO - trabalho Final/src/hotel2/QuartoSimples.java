package hotel2;

public class QuartoSimples extends Quarto {
   public QuartoSimples(){
       descricao = "Quarto Simples";
   }
   
   @Override
   public double custoQuarto(){
       return 75.00;
   }
}
