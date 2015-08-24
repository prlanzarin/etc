// runnable eh preferivel a extends thread porque podemos querer
// estender uma business class
// alterar thread pra implementar runnable
class SimpleThread extends Thread {
	
	private String name;
	
	public SimpleThread(String name) {
		this.name = name;
	}

	public void run() {
		int i = 10;
		while (true) {
			System.out.println(name + " executando...");
			
			try { Thread.currentThread().sleep(100);}
			catch (InterruptedException ie) { ie.printStackTrace(); }
			
			i--;
		}
	}	
}

public class ThreadTester {
	
	public static void main(String args[]) {
		
		SimpleThread thr1 =  new SimpleThread("Joe");
		SimpleThread thr2 =  new SimpleThread("Paul");
		
		thr1.start();
		thr2.start();
	/*	
		try {
			thr1.join();
			thr2.join();
		} catch (InterruptedException ie) { 
			ie.printStackTrace(); 
		}
	*/	
		System.out.println("Main finalizando...");
	}
}
