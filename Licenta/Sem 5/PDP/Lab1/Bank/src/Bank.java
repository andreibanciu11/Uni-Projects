import java.util.*;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public final class Bank {
    public List<Account> accounts;
    private final int threadNumber;
    private final int accountNumber;
    private final int threadOperationNumber;
    private Lock mtx;
    public Bank(int threadNumber, int accountNumber, int threadOperationNumber) {
        this.accounts = new ArrayList<>();
        this.threadNumber = threadNumber;
        this.accountNumber = accountNumber;
        this.threadOperationNumber = threadOperationNumber;
        this.mtx = new ReentrantLock();
    }

    public void run() {
        for (int i=0;i<accountNumber;i++){
            accounts.add(new Account(i+1,200));
        }

        float start = (float) System.nanoTime() / 1000000;

        List<Thread> threads = new ArrayList<>();

        Timer timer = new Timer();

        initializeThreads(threads);
        Thread timeToTimeCheck = new Thread(() -> {
            mtx.lock();
            timer.schedule(new TimerTask() {
                @Override
                public void run() {
                    generalCheck();
                }
            }, 50);
            mtx.unlock();
        });

        for(Thread thread : threads)
            thread.start();

        timeToTimeCheck.start();
        for(Thread thread : threads)
            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        try {
            timeToTimeCheck.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        generalCheck();

        float end = (float) System.nanoTime() / 1000000;

        System.out.println("Time elapsed: " + (end-start)/1000 + " seconds");

    }

    private void initializeThreads(List<Thread> threads){
        for (int i=0;i<threadNumber;i++){

            int threadId = i;
            threads.add(new Thread(() -> {
                Random r = new Random();
                for(long j = 0; j <threadOperationNumber; ++j){
                    int sender = r.nextInt(accountNumber);
                    int receiver = r.nextInt(accountNumber);
                    while(sender == receiver)
                        receiver = r.nextInt(accountNumber);

                    int sum = r.nextInt(50);
                    accounts.get(sender).makeTransfer(accounts.get(receiver),sum);

                    System.out.println("[Thread " + threadId + "]: Account " + sender + " sent " + sum + "$ to Account " + receiver);
                }
            }));
        }
    }

    private void generalCheck() {
        int checkFails = 0;
        for(Account account : accounts){
            account.mtx.lock();
            if(!account.checkBalance())
                checkFails++;
        }

        for (Account account : accounts) {
            account.mtx.lock();
            for (Operation op : account.log.operations) {
                Account targetAccount = accounts.get(op.receiver-1);
                if (!targetAccount.log.operations.contains(new Operation("receive", op.receiver, op.sender, op.amount, op.timestamp))) {
                    checkFails++;
                }
            }
            account.mtx.unlock();
        }

        if (checkFails > 0){
            throw new RuntimeException("Check returned error!");
        }
        System.out.println("Check ended with no errors");
    }
}