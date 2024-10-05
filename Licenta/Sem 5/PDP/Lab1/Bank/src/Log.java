import java.util.ArrayList;
import java.util.List;

public final class Log {
    public List<Operation> operations;

    public Log() {
        operations = new ArrayList<>();
    }

    public void log(String operationType, int sum, int src, int dest, long timestamp){
        operations.add(new Operation(operationType,src, dest,sum,timestamp));
    }

}