package pdp;

import java.util.ArrayList;

public class Usuario implements Runnable{

    int id;
    int models;
    PrintServer printServer; 


    public Usuario(int id, PrintServer printServer) {
	this.id = id;
	this.printServer = printServer;
	this.models = 0;
    }

    public void newModel() {
	this.models++;
    }

    @Override // thread
    public void run() {
	System.out.println("User " + this.id + "is sending a job request\n");
	this.printServer.jobRequest();
    }
}
