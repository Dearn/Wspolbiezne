class Bufor {
    int wartosc = 0;
    public void put(int a)
    {
	if (wartosc ==0)
	    {
		wartosc = a;		
	    }
	
    }
    public int get()
    {
	int tmp=0;
	if(wartosc>0)
	    {
		tmp = wartosc;
		wartosc = 0;
	    }
	return tmp;
    }
}

class Producent extends Thread
{
    Bufor B;
    public Producent(Bufor B)
    {

	this.B = B;

    }

    public void run()
    {

	for (int i = 0; i < 100; i++)
	    {
		B.put(i);
		System.out.println("B.put umiescil: " + i + "  St pobral: " + St );

	    }	    

	try
	    {
		sleep((int)Math.ceil(Math.random()*100));
	    }
	catch(Exception e) {}
	

    }
}



class Konsument extends Thread
{
    Bufor B;
    int St = 0;
    public Konsument(Bufor B)
    {

	this.B = B;

    }

    public void run()
    {

	for (int i = 0; i < 100; i++)
	    {
		St+= B.get();
		System.out.println("ST pobral: " + St);

	    }	    

	try
	    {
		sleep((int)Math.ceil(Math.random()*100));
		
	    }
	catch(Exception e) {}
	

    }
}


public class lab1 {

    public static void main(String args[])
    {
	Bufor test = new Bufor();
	Konsument konsument = new Konsument(test);
	Producent producent = new Producent(test);

	// Thread t1 = new Thread(konsument);
	// Thread t2 = new Thread(producent);

	konsument.start();
	producent.start();
	
    }
}
       








