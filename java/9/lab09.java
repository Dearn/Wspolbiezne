class Ksiazka
{
    int wartosc = 0;
    boolean pisana = false;
    int czytana = 0;
    boolean napisana = false;

    public synchronized void napisz(int a)
    {
	while(pisana || (czytana > 0))
	    {
		try {
		    wait();
		}
		catch (Exception e) {
		}


	    }
	this.pisana = true;
	wartosc = a;
	try
	    {
		Thread.sleep((int)(Math.random()*200)+100);
		
	    }
	catch (Exception e) {
	    
	}

	this.pisana = false;
	this.napisana = true;
	notify();
    }

    public synchronized int czytaj()
    {
	while(pisana)
	    {
		try {
		    wait();
		}
		catch (Exception e) {
		    
		}
	    }
	this.czytana++;
	wartosc = 1;
	try {
	    Thread.sleep((int)(Math.random()*200)+100);
	}
	catch (Exception e) {
	    
	}

	int tmp = 0;
	if(wartosc>0)
	    {
		tmp = wartosc;
		wartosc = 0;
	    }
	this.czytana--;


	notify();
	return tmp;
    }
}



class Pisarz extends Thread
{
    
    Ksiazka K;


    public Pisarz(Ksiazka K)
    {
	this.K = K;

    }

    public void run()

    {
	for(int i=0; i<100; i++)
	    {
		K.napisz(i);
		System.out.println(this.getName() + " napisal " + i);

	    }
	
    }
}


class Czytelnik extends Thread
{
    Ksiazka K;
    public Czytelnik(Ksiazka K)
    {
	this.K = K;

    }

    public void run()

    {
	for(int i=0; i<100; i++)
	    {
		K.czytaj();
		System.out.println(this.getName() + " przeczytal " + i);
	    }
    }
}




public class lab09
{

    public static void main(String args[])
    {
	Ksiazka ksiazka = new Ksiazka();
	Pisarz[] pisarz = new Pisarz[5];
	for(int i=0; i<5; i++)
	    {
		pisarz[i] = new Pisarz(ksiazka);
		pisarz[i].start();
	    }
	Czytelnik[] czytelnik = new Czytelnik[3];
	for(int i=0; i<3; i++)
	    {
		czytelnik[i] = new Czytelnik(ksiazka);
		czytelnik[i].start();
	    }




	
    }
}
