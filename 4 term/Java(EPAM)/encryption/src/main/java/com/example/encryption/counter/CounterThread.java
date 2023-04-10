package com.example.encryption.counter;

import org.springframework.stereotype.Component;

@Component
public class CounterThread extends Thread {

    @Override
    public void start() {
        Counter.increment();
    }
}
