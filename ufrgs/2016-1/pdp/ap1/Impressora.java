package pdp;

import java.util.ArrayList;
import java.util.List;

public class Impressora implements Runnable {

	int maxPressTime; // Java time
	int maxPress;
	int nofPrints;

	public Impressora(int mt, int x) {
		this.maxPressTime = mt;
		this.maxPress = x;
	}

	public int getMaxPressTime() {
		return this.maxPressTime;
	}

	public int getMaxPress() {
		return this.maxPress;
	}

	public boolean printJobs() {
		// sleep nofJobs * 5s
		// return etc
		System.out.println("Printer is printing a packet...\n");
		try {
		Thread.sleep(this.maxPressTime*1000);
		} catch (InterruptedException e) {return false;}
		this.nofPrints++;
		System.out.println("Printer is done...\n");
		this.notifyAll();

		return true;
	}

	public boolean isAble() {
		if((this.maxPress - this.nofPrints) <= 0)
			return false;
		return true;
	}

	@Override
		public void run() {
			while(isAble())
				;
			System.out.println("PRINTER: max number of prints per day reached...\n");
		}

}
