class Lokaj
{
	int ilu=0;
	public synchronized void wejdz(){
	
	while(ilu==4){	
		System.out.println("################################## Lokaj czeka"+Thread.currentThread());
		try{
			wait();
			}catch(Exception e){}
	
	}	
		this.ilu++;
		System.out.println("Lokaj "+Thread.currentThread()+" usiadl do stolu. Przy stole siedzi "+ilu+" filozofow ");
	}
	public synchronized void wyjdz(){
	this.ilu--;
	System.out.println("Lokaj "+Thread.currentThread()+" odchodzi od stolu. Przy stole siedzi "+ilu+" filozofow ");
	notifyAll();
	}
}

class Widelec
{
	static int licznik=0;
	int id=licznik++;
	boolean lezy=true;
	
    public String toString() {
    return "Widelec"+id;
    }
	public synchronized void get(){
		while(lezy==false){
						try{
			wait();
			}catch(Exception e){}
		}
		lezy=false;

	}
	public synchronized void put(){
	lezy=true;
	notifyAll();
	}

}

class Filozof extends Thread{
	static int licznik=0;
	int id=licznik++;
	Widelec lewy;
	Widelec prawy;
	Lokaj L;
	public String toString(){
	return "Filozof"+id;
	}
	public Filozof(Widelec lewy, Widelec prawy, Lokaj L)
	{
		this.lewy=lewy;
		this.prawy=prawy;
		this.L=L;
		this.start();
	}

    public void run (){
        while(true){
			L.wejdz();
			System.out.println(this+" wszedl ");
			lewy.get();
			System.out.println(this+" podniosl "+lewy);
			prawy.get();
			System.out.println(this+" podniosl "+prawy);
			try{
			System.out.println(this+" zajada ");
			sleep((int)(Math.random()*30));
			}
			catch(Exception e){}
			lewy.put();
			System.out.println(this+" odlozyl "+lewy);
			prawy.put();
			System.out.println(this+" odlozyl "+prawy);
			L.wyjdz();
			System.out.println(this+" wyszedl ");
			try{
				sleep((int)(Math.random()*50));
			}catch(Exception e){}
		}
	}
}


public class jadalnia2
{
	public static void main(String[] args) {
	Widelec[]w=new Widelec[5];
	for(int i=0;i<5;i++){
		w[i]=new Widelec();
	}
	Lokaj[]l=new Lokaj[5];
	for(int i=0;i<5;i++){
		l[i]=new Lokaj();
	}
	Filozof[]f=new Filozof[5];
		for(int i=0;i<5;i++){
		f[i]=new Filozof(w[i],w[(i+1)%5],l[i]);
	}
	}
}
