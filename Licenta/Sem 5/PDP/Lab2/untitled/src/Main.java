public class Main {
    public static void main(String[] args) {
        int[] vectorA = {3, 5, 7};
        int[] vectorB = {4, 6, 8};

        Product product = new Product();

        Thread producer = new Thread(new Producer(vectorA, vectorB, product));
        Thread consumer = new Thread(new Consumer(vectorA.length, product));

        producer.start();
        consumer.start();
    }
}