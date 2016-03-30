/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pdp;

import java.util.*;

public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
    	List<Thread> usuarios;
	Impressora impressora = new Impressora(5, 6);
	PrintServer printServer = new PrintServer(10, impressora);
	Thread impThread = new Thread(impressora);
	Thread serverThread = new Thread(serverThread);

	impThread.start();
	serverThread.start();

	for(int i = 0; i < 20; i++) {
		Usuario u = new Usuario(i);	
		Thread ut = new Thread(u);
		usuarios.add(u);
		u.start();
	} 	
    }
    
}
