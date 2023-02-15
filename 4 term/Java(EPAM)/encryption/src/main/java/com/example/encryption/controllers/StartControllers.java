package com.example.encryption.controllers;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class StartControllers {

    @GetMapping("/ecrypt")
    public String ecryption(@RequestParam("string") String string,
                            @RequestParam("operation") boolean operation) {



        return string;
    }

}
