class Watek extends Thread {

    static int l=0;
    int id = l++;

    public void run() 		// musi byc - kod wykonany przez nowy watek
    {

	// System.out.println("Nowy Watek " + Thread.currentThread().getName());
	System.out.println("Nowy Watek "+ this.getName() + " ID: " +  id);// this.getName()
			   



    }
}

 class Watek2 implements Runnable{
    static int l=0;
    int id = l++;
    public void run() 		// musi byc - kod wykonany przez nowy watek
    {

	// System.out.println("Nowy Watek " + Thread.currentThread().getName());
	System.out.println("Nowy Watek2 "  + "ID: " + id);// this.getName()

    }
     
}


public class Hello {


    public static void main(String args[])
    {
	Watek watek = new Watek();
	Watek watek2 = new Watek();
	Watek watek3 = new Watek();
	Watek2 w1 = new Watek2();
	Thread t1 = new Thread(w1);
	t1.start();
	// w1.start();
	watek.start();
	watek2.start();
	watek3.start();
	// System.out.println("Hello! " + Thread.currentThread().getName() );

    }


}
