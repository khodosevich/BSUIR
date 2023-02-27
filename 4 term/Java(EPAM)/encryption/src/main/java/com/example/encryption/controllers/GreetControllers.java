package com.example.encryption.controllers;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class GreetControllers {

    @GetMapping("/greet")
    public String greeting(@RequestParam("string") String name){
        return "Hello " + name ;
    }

}
