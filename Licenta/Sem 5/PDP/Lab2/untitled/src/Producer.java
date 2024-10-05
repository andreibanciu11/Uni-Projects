public class Producer implements Runnable {
    private final int[] vectorA;
    private final int[] vectorB;
    private final Product product;

    public Producer(int[] vectorA, int[] vectorB, Product product) {
        this.vectorA = vectorA;
        this.vectorB = vectorB;
        this.product = product;
    }

    @Override
    public void run() {
        for (int i = 0; i < vectorA.length; i++) {
            product.set(vectorA[i] * vectorB[i]);
            System.out.println("[PRODUCER]: Product of pair: " + i + " is " + vectorA[i]*vectorB[i]);
        }
    }
}
