package hotel2;


public class DecBanheira extends Decorator{
    Quarto quarto;
   
   public DecBanheira(Quarto quarto){
       this.quarto = quarto;
   }
   
   @Override
   public String getDescricao(){
       return quarto.getDescricao() + ", Banheira de Hidromassagem";
   }
   
   @Override
   public double custoQuarto(){
       return 200.00 + quarto.custoQuarto();
   }
    
}
