package com.example.encryption.controllers;


import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/start")
public class StartApp {

    @GetMapping
    public String hello(@RequestParam("name") String name){
        return "hello " + name + " !";
    }
}
