/*
    This file is part of jrastro.

    jrastro is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    jrastro is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
    for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with jrastro; if not, write to the Free Software Foundation, Inc.,
	51 Franklin Street, Fifth Floor, Boston, MA 02111 USA.
*/
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
