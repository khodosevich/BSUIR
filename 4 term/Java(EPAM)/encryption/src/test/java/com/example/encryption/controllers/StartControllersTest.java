package com.example.encryption.controllers;

import com.example.encryption.exceptions.URLArgumentsException;
import com.example.encryption.model.EncryptService;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;


public class StartControllersTest {

    @Test
    void checkParam() {
        Assertions.assertThrows(URLArgumentsException.class, () -> {
            EncryptService.checkSrting("hell55o");
        });
    }

    //encrupt/dec
    //logger error
}
