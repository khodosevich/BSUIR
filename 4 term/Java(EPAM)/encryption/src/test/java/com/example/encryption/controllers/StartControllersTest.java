package com.example.encryption.controllers;

import com.example.encryption.exceptions.URLArgumentsException;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;


public class StartControllersTest {

    @Test
    void checkParam(){
        Assertions.assertThrows(URLArgumentsException.class,()->{
           StartControllers.checkSrting("hell55o");
        });
    }

}
