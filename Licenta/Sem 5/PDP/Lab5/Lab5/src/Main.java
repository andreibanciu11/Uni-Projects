import model.Operation;
import model.Polynomial;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutionException;

public class Main {

    private static final List<String> times = new ArrayList<String>();

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        // write your code here
        Polynomial p = new Polynomial(1000);
        Polynomial q = new Polynomial(1000);

        System.out.println("P:" + p);
        System.out.println("Q:" + q);
        System.out.println("\n");

        //Simple
        System.out.println(simpleSequential(p, q).toString() + "\n");
        System.out.println(simpleThreaded(p, q).toString() + "\n");

        //Karatsuba
        System.out.println(karatsubaSequential(p, q).toString() + "\n");
        System.out.println(karatsubaThreaded(p, q).toString() + "\n");

        System.out.println(times);

    }

    private static Polynomial simpleSequential(Polynomial p, Polynomial q) {
        long startTime = System.currentTimeMillis();
        Polynomial result1 = Operation.simpleSequential(p, q);
        long endTime = System.currentTimeMillis();
        long time = endTime-startTime;
        System.out.println("Simple sequential multiplication of polynomials: ");
        System.out.println("Execution time: " + (endTime - startTime) + " ms");
        times.add("Simple sequential: " + time);
        return result1;
    }

    private static Polynomial simpleThreaded(Polynomial p, Polynomial q) throws InterruptedException {
        long startTime = System.currentTimeMillis();
        Polynomial result2 = Operation.simpleThreaded(p, q);
        long endTime = System.currentTimeMillis();
        long time = endTime-startTime;
        System.out.println("Simple parallel multiplication of polynomials: ");
        System.out.println("Execution time: " + (endTime - startTime) + " ms");
        times.add("Simple parallel: " + time);
        return result2;
    }

    private static Polynomial karatsubaSequential(Polynomial p, Polynomial q) {
        long startTime = System.currentTimeMillis();
        Polynomial result3 = Operation.karatsubaSequential(p, q);
        long endTime = System.currentTimeMillis();
        long time = endTime-startTime;
        System.out.println("Karatsuba sequential multiplication of polynomials: ");
        System.out.println("Execution time: " + (endTime - startTime) + " ms");
        times.add("Karatsuba sequential: " + time);
        return result3;
    }

    private static Polynomial karatsubaThreaded(Polynomial p, Polynomial q) throws ExecutionException,
            InterruptedException {
        long startTime = System.currentTimeMillis();
        Polynomial result4 = Operation.karatsubaThreaded(p, q, 1);
        long endTime = System.currentTimeMillis();
        long time = endTime-startTime;
        System.out.println("Karatsuba parallel multiplication of polynomials: ");
        System.out.println("Execution time: " + (endTime - startTime) + " ms");
        times.add("Karatsuba parallel: " + time);
        return result4;
    }


}