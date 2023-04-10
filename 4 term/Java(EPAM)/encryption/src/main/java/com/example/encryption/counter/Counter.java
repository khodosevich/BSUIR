package com.example.encryption.counter;

public class Counter {
    private static int COUNTER = 0;

    public synchronized static void increment(){
        COUNTER++;
    }
    public static int getCounter(){
        return COUNTER;
    }
}
