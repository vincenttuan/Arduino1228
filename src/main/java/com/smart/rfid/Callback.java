package com.smart.rfid;

public abstract class Callback {
    private boolean relayValue;
    public abstract void setValue(String fulldata);
    public void setRelayValue() {
        relayValue = !relayValue;
    }
    public boolean getRelayValue() {
        return relayValue;
    }
}
