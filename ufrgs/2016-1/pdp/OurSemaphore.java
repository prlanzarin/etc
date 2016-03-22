import java.util.*;

public class OurSemaphore {
    int S; 

    public OurSemaphore(int s) {
        this.S = s;
    }

    public int getPermits() {
        return S;
    }
    // synchronized
    public synchronized void proberen() throws InterruptedException {
        this.S = this.S - 1;
        if (this.S < 0)
                this.wait();
    }

    public synchronized void proberen(int permits) throws InterruptedException {
       for(int i = 0; i < permits; i++) {
            proberen();
       } 
    }

    // synchronized 
    public synchronized void verhogen() {
        this.S = this.S + 1;
        if (this.S <= 0) 
            this.notify(); 
    }

}
