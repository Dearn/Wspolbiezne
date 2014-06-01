// class filozof, widelec(buffor), 5 widelec, 5 obiekt fil, 5 watek,


class Widelec
{
    
    int nr;
    boolean wziety = false;


    Widelec(int nr)
    {
	this.nr = nr;

    }

    public synchronized void podnies()
    {
	while(wziety)
	    {

		try
		    {
			wait();
		    }
		catch(Exception e){}

	    }
	this.wziety = true;
	try
	    {
		Thread.sleep((int)(Math.random()*200)+100);
	    }
	catch(Exception e){}

	notify();
    }

    public synchronized void odloz()
    {

	this.wziety = false;
	notify();
	

    }


}


class Filozof extends Thread
{
    int nr;
    Widelec lewy;
    Widelec prawy;
    boolean je = false;

    Filozof(int nr, Widelec lewy, Widelec prawy)
    {
	this.nr = nr;
	this.lewy = lewy;
	this.prawy = prawy;
	System.out.println("Nr " + nr + " Lewy: " + lewy.nr + " Prawy: " + prawy.nr);
    }
    void jedz()
    {
        this.je = true;
	lewy.podnies();
	prawy.podnies();
	System.out.println("Filozof" + this.nr + "| Jem uzywajac lewy: " + lewy.nr + " prawy: " + prawy.nr);
	this.je = false;
	lewy.odloz();
	prawy.odloz();
	System.out.println("Filozof" + this.nr + "| Odlozylem Lewy: " + lewy.nr + " prawy: " + prawy.nr);
	
    }

    public void run()
    {

	for(int i = 0; i < 100; i++)
	    {
		System.out.println(i + " " + this.getName());
		jedz();
		System.out.println("############################");

    
	    }
    }

}

public class lab08
{
    public static void main(String[] args)
    {
	Widelec[] widelec = new Widelec[5];
	for(int i=0; i<5; i++)
	    {
		widelec[i] = new Widelec(i);
	
	    }
	Filozof[] filozof = new Filozof[5];

	for(int i=0; i<5; i++)
	    {
		if(i<4)
		    {
			filozof[i] = new Filozof(i, widelec[i], widelec[i+1]);
		    }
		else
		    {
			filozof[i] = new Filozof(i, widelec[4], widelec[0]);
		    }

	    }
	for(int i=0;i<5;i++)
	    filozof[i].start();
    }
}
