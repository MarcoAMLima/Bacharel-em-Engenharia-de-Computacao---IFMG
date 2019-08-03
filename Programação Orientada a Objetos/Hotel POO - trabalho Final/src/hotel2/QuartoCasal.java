package hotel2;

public class QuartoCasal extends Quarto {
   public QuartoCasal(){
       descricao = "Quarto de Casal";
   }
   
   @Override
   public double custoQuarto(){
       return 150.00;
   }
}
