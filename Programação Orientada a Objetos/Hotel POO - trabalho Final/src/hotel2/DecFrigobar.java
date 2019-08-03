
package hotel2;

public class DecFrigobar extends Decorator{
    
   Quarto quarto;
   
   public DecFrigobar(Quarto quarto){
       this.quarto = quarto;
   }
   
   @Override
   public String getDescricao(){
       return quarto.getDescricao() + ", Frigobar";
   }
   
   @Override
   public double custoQuarto(){
       return 50.00 + quarto.custoQuarto();
   }
    
}
