public class Product {
    private int value;
    private boolean isAvailable = false;

    // Synchronized with get method, acts as a mutex, locking and unlocking the resource
    public synchronized void set(int value) {
        while (isAvailable) {
            try {
                wait();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
        this.value = value;
        isAvailable = true;
        notify();
    }

    // Synchronized with set method, acts as a mutex, locking and unlocking the resource
    public synchronized int get() {
        while (!isAvailable) {
            try {
                wait();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
        isAvailable = false;
        notify();
        return value;
    }
}
