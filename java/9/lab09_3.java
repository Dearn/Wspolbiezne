class Widelec{
   public boolean podniesiony;
   private static int liczba = 0;
   public int numer;

   {
       podniesiony=false;
       numer=liczba;
       liczba++;
   }

   public synchronized void podnies(){
       while(podniesiony){
           try{
               wait();
           }catch(InterruptedException ie){}
       }
           podniesiony=true;

           notify();


   }

   public synchronized void odloz(){
       podniesiony=false;
       notify();
   }
}


class Filozof extends Thread{
   private Widelec lewy, prawy;
   private static int liczba = 0;
   private int numer;

   public Filozof(Widelec lewy, Widelec prawy){
       this.lewy=lewy;
       this.prawy=prawy;
       numer=liczba;
       liczba++;
       //System.out.println("mam widelce: "+this.lewy.numer+"
       "+this.prawy.numer);
   }

   @Override
   public void run(){
       for(int i=0;i<100;i++){
           lewy.podnies();
           prawy.podnies();
           //System.out.println("fil: "+numer+"podnioslem: "+lewy.numer+" i
           "+prawy.numer);

           if(lewy.podniesiony && prawy.podniesiony){
               System.out.println("fil: "+numer+"podnioslem: "+lewy.numer+"
               i "+prawy.numer);
               try{
                   sleep((int)(Math.random()*100));
               }catch(InterruptedException ie){}

               lewy.odloz();
               prawy.odloz();
               System.out.println("fil: "+this.numer+"odlozylem:
               "+lewy.numer+" i "+prawy.numer);
               try{
                   sleep((int)(Math.random()*100));
               }catch(InterruptedException ie){}
           }
       }
   }

}

public class fil{

   public static void main(String [] argv){
       String opcja = JOptionPane.showInputDialog("imie: ");
       int size=5;
       ArrayList <Widelec> widelce = new ArrayList <Widelec>();
       ArrayList <Filozof> filozofowie = new ArrayList <Filozof>();

       for(int i=0;i<size;i++){
           widelce.add(new Widelec());
       }

       for(int i=0;i<size;i++){
           if(i != size-1)
               filozofowie.add(new Filozof(widelce.get(i),
               widelce.get(i+1)));
           else
               filozofowie.add(new Filozof(widelce.get(i),
               widelce.get(0)));
       }

       for(Filozof wasyl:filozofowie){
           wasyl.start();
       }

   }
}
