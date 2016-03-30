package pdp;

import java.util.ArrayList;
import java.util.List;

public class PrintServer implements Runnable {

	Impressora impressora;
	int packetSize;  
	int pendingRequests;

	public PrintServer(int p, Impressora i) {
		this.packetSize = p;
		this.impressora = i;
		this.pendingRequests = 0;
	}

	public synchronized boolean jobRequest() {
		if(!this.impressora.isAble())
			return false;

		this.pendingRequests++;

		return true;
	}

	@Override
		public void run() {
			// fica na main	
			while(this.impressora.isAble()) {
				if(this.pendingRequests >= this.packetSize) {
					this.pendingRequests -= packetSize;
					this.impressora.printJobs();
					System.out.println("PrintServer is sending a packet to the printer...\n");
					try {
						this.wait();
					} catch (InterruptedException e) {
						return null;
					}
					System.out.println("PrintServer is free again, requeuing jobs...\n");
					this.pendingRequests += packetSize;	
				}
			}
		}

}
