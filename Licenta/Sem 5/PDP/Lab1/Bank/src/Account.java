import java.util.Objects;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public final class Account {
    public int id;
    public int balance;
    public Log log;
    public int initialBalance;
    public Lock mtx;

    public Account(int id, int balance) {
        this.id = id;
        this.initialBalance = balance;
        this.balance = balance;
        this.mtx = new ReentrantLock();
        this.log = new Log();
    }

    public void makeTransfer(Account other, int sum){
        if (sum>balance){
            return;
        }
        this.mtx.lock();
        other.mtx.lock();

        balance-=sum;
        other.balance+=sum;
        long timestamp = System.currentTimeMillis();
        logTransfer("send",this.id, other.id,sum, timestamp);
        other.logTransfer("receive",other.id, this.id, sum, timestamp);

        this.mtx.unlock();
        other.mtx.unlock();

    }

    public void logTransfer(String operationType, int src, int dest, int sum, long timestamp){
        log.log(operationType,sum, src, dest, timestamp);
    }

    public boolean checkBalance() {
        int initBalance = this.initialBalance;
        for (Operation operation: this.log.operations){
            if (Objects.equals(operation.operationType, "send"))
                initBalance-=operation.amount;
            else
                initBalance+=operation.amount;
        }
        return initBalance==this.balance;
    }
}