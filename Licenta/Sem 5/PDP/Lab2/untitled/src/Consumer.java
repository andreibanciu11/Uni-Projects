public class Consumer implements Runnable {
    private final int numberOfProducts;
    private final Product product;
    private int sum = 0;

    public Consumer(int numberOfProducts, Product product) {
        this.numberOfProducts = numberOfProducts;
        this.product = product;
    }

    @Override
    public void run() {
        for (int i = 0; i < numberOfProducts; i++) {
            sum += product.get();
            System.out.println("[CONSUMER]: SUM of products is currently: " + sum);
        }
        System.out.println("The scalar product is: " + sum);
    }
}
