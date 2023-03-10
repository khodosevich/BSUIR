package com.example.encryption.controllers;

import com.example.encryption.cache.Cache;
import com.example.encryption.counter.Counter;
import com.example.encryption.counter.CounterThread;
import com.example.encryption.exceptions.URLArgumentsException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.logging.Logger;

import static com.example.encryption.model.EncryptService.*;

@RestController
public class StartControllers {

    private final Cache<String,String> cache;
    private static final Logger logger = Logger.getLogger(StartControllers.class.getName());
    private final CounterThread counterThread;

    @Autowired
    public StartControllers(Cache<String,String> cache,CounterThread counterThread){
        this.cache = cache;
        this.counterThread = counterThread;
    }

    @GetMapping("/encrypt")
    public ResponseEntity<?> ecryption(@RequestParam("string") String string,
                                       @RequestParam("operation") boolean operation) throws URLArgumentsException {



        counterThread.run();
        String result = "";

        logger.info("Work cache!");


        logger.info(" persons visit our service ");

        if (operation) {
            if(!cache.contains(string)){
                logger.info("check string");
                checkSrting(string);
                logger.info("encrypt start");
                result = encrypt(string, 1);
            }
            else{
                logger.info("get string from cache");
               result = cache.pop(string);
            }
        } else {
            if(!cache.contains(string)){
                logger.info("decrypt start");
                result = decrypt(string, 1);
            }
            else{
                logger.info("get decrypt string from cache");
                result = cache.pop(string);
            }
        }

        cache.push(string,result);

        logger.info("program end!");

        Result result1 = new Result(result , Counter.getCounter());

        return ResponseEntity.ok(result1);

    }
}
