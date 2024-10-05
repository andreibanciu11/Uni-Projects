public final class Operation {
    public int sender;
    public int receiver;
    public String operationType;
    public int amount;
    public long timestamp;

    public Operation(String operationType, int sender, int receiver, int amount) {
        this.sender = sender;
        this.receiver = receiver;
        this.operationType = operationType;
        this.amount = amount;
    }

    public Operation(String operationType, int sender, int receiver, int amount, long timestamp) {
        this.sender = sender;
        this.receiver = receiver;
        this.operationType = operationType;
        this.amount = amount;
        this.timestamp = timestamp;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Operation operation = (Operation) o;
        return sender == operation.sender &&
                receiver == operation.receiver &&
                amount == operation.amount &&
                timestamp == operation.timestamp;
    }
}