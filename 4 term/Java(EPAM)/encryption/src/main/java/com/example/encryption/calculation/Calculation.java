package com.example.encryption.calculation;

import org.springframework.stereotype.Component;

import java.util.List;

@Component
public class Calculation {

    public int findMax(List<String> listOfString) {
        int result = 0;

        if (!listOfString.isEmpty()) {
            result = listOfString.stream().mapToInt(s->s.length()).max().getAsInt();
        }
        return result;
    }

    public int findMin(List<String> listOfString) {
        int result = 0;

        if (!listOfString.isEmpty()) {
            result = listOfString.stream().mapToInt(String::length).min().getAsInt();
        }
        return result;
    }

    public double findAverage(List<String> listOfString) {
        double result = 0;

        if (!listOfString.isEmpty()) {
            result = listOfString.stream().mapToInt(String::length).average().getAsDouble();
        }
        return result;
    }

}
