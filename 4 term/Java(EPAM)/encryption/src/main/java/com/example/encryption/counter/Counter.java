package com.example.encryption.counter;

public class Counter {
    private static int COUNTER;

    synchronized public static void increment(){
        COUNTER++;
    }

    synchronized public static int getCounter(){
        return COUNTER;
    }
}
