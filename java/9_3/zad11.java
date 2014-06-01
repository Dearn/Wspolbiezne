import java.util.concurrent.*;

class Filozof implements Runnable
{
    Widelec w1,w2;
    int nazwa;
    Filozof(Widelec w1, Widelec w2,int i)
    {
	this.w1 = w1;
	this.w2 = w2;
	nazwa= i;
    }
	
    public void run()
    {
	for(int i=0;i<=100;i++)
	    {
		if(w1.podnies() == true || w2.podnies() == true)
		    {
			System.out.println("Filozof: " + nazwa + " podniosl widelec: " + w1.nr + " " + w2.nr);
			try
			    {
				Thread.sleep((int)Math.random()*100);
			    }
			catch(Exception e){}
				
			w1.odloz();
			w2.odloz();
			System.out.println("Filozof: " + nazwa + " odlozyl widelec: " + w1.nr + " "+ w2.nr);
		    }
	    }
	Thread.yield();
    }
}

class Widelec 
{
    int licznik = 0;
    int nr;
    boolean podniesiony = false;
    Widelec(int n)
    {
	nr = n;
    }
	
    public synchronized boolean podnies()
    {
	if(licznik >= 4)
	    {
		return false;
	    }
	while(podniesiony)
	    {
		try
		    {
			wait();
		    }
		catch(Exception e){}
	    }
	podniesiony = true;
	licznik++;
	return true;
    }
	
    public synchronized boolean odloz()
    {
	licznik--;
	podniesiony = false;
	notifyAll();
	return true;
		
    }
	
}

public class zad11
{
    public static void main(String args[])
    {
	Widelec []w = new Widelec[5];
	for(int i=0;i<5;i++)
	    {
		w[i] = new Widelec(i+1);
	    }
		
	/*for(int i=0;i<4;i++)
	  {
	  new Thread(new Filozof(w[i],w[i+1],i+1)).start();
	  }
	  new Thread(new Filozof(w[4],w[0],5)).start();
	*/
		
	ExecutorService exec = Executors.newFixedThreadPool(4);
	
	for(int i=0;i<4;i++)
	    {
		exec.execute(new Filozof(w[i],w[i+1],i+1));
	    }
	exec.execute(new Filozof(w[4],w[0],5));
	exec.shutdown();
    }
}
