class SimpleThread extends Thread {
    public SimpleThread(String str) {
	super(str);
    }
    public void dorme() throws InterruptedException {
      sleep((int)(Math.random() * 10));
    }
    public void run() {
	for (int i = 0; i < 10; i++) {
	    System.out.println(i + " " + getName());
            try {
		for (int j = 0; j < 100; j++){
			Object obj = new Object();
		}
		dorme();
		System.gc();
	    } catch (InterruptedException e) {}
	}
	System.out.println("DONE! " + getName());
    }
    public static void main (String args[]) {
        new SimpleThread("Jamaica").start();
        new SimpleThread("Fiji").start();
    }
}
