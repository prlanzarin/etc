import java.util.Random;

class MyMonitor {
	
	private int data = 0;
	private int turn = 1;
   	// synchronize garante que metodo eh mutualmente exclusiv
	// threads ainda intercalam. Como arrumar? Variavel turn. 
	public synchronized void update(int id) throws InterruptedException {

	// wait & notify somente em bloco sincronizados	
        while(turn != id) // se a vez nao for da thread, bloqueia. 
		this.wait(); // eh while porque eh signal-and-continue
        System.out.println("Thread ID = " + id + " vai atualizar ...");
        data++; Thread.currentThread().sleep(new Random().nextInt(3000));
        System.out.println("Thread ID = " + id + " atualizou...");		
        turn = (turn + 1) % 2;	
        this.notify();	
	}
}

class MyThread extends Thread {
	
	int id;
	MyMonitor myMonitor;
	
	public MyThread(int id, MyMonitor myMonitor) {
		this.id = id;
		this.myMonitor = myMonitor;
	}
	
	public void run() {
		while (true) {
			try {
				myMonitor.update(id);
				Thread.currentThread().sleep(new Random().nextInt(3000));
			}
			catch (InterruptedException ie) { 
				ie.printStackTrace(); 
			}
		}
	}
}

public class MonitorTester {
	
	public static void main(String args[]) {
		
		MyMonitor myMonitor = new MyMonitor();
		
		MyThread t1 = new MyThread(0, myMonitor);
		MyThread t2 = new MyThread(1, myMonitor);
		
		t1.start();
		t2.start();		
	}
}
