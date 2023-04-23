package com.example.encryption.controllers;

import com.example.encryption.async.ResultAsync;
import com.example.encryption.cache.Cache;
import com.example.encryption.calculation.Calculation;
import com.example.encryption.counter.Counter;
import com.example.encryption.counter.CounterThread;
import com.example.encryption.exceptions.URLArgumentsException;
import com.example.encryption.model.Result;
import com.example.encryption.service.EncryptionService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.logging.Logger;

import static com.example.encryption.model.EncryptService.*;

@RestController
public class EncryptionControllers {

    private final Cache<String, String> cache;
    private final Calculation calculation;
    private static final Logger logger = Logger.getLogger(EncryptionControllers.class.getName());
    private final ResultAsync resultAsync;
    private final EncryptionService encryptionService;

    @Autowired
    public EncryptionControllers(Cache<String, String> cache, Calculation calculation, ResultAsync resultAsync, EncryptionService encryptionService) {
        this.cache = cache;
        this.calculation = calculation;
        this.resultAsync = resultAsync;
        this.encryptionService = encryptionService;

    }

    @GetMapping("/encrypt")
    public ResponseEntity<?> ecryption(@RequestParam("string") String string,
                                       @RequestParam("operation") boolean operation) throws URLArgumentsException {

        logger.info("check string");
        checkSrting(string);

        CounterThread threadCounter = new CounterThread();
        threadCounter.start();

        String result;

        logger.info("Work cache!");


        logger.info(" persons visit our service ");
        logger.info("count = " + Counter.getCounter());

        if (operation) {
            if (!cache.contains(string)) {

                logger.info("encrypt start");
                result = encrypt(string, 1);
            } else {
                logger.info("get string from cache");
                result = cache.pop(string);
            }
        } else {
            if (!cache.contains(string)) {
                logger.info("decrypt start");
                result = decrypt(string, 1);
            } else {
                logger.info("get decrypt string from cache");
                result = cache.pop(string);
            }
        }


        logger.info("push to cache");
        cache.push(string, result);

        logger.info("program end!");

        Result result1 = new Result(string,result);



        encryptionService.save(result1);

        return ResponseEntity.ok(result1 + "\nCounter: " + Counter.getCounter());

    }

    @PostMapping("/encrypt")
    public ResponseEntity<?> bulkEncrypt(@RequestBody List<String> listOfString) {
        List<String> resultList = listOfString.stream().map(x -> encrypt(x, 1)).toList();


        int max = calculation.findMax(listOfString);
        int min = calculation.findMin(listOfString);
        double avg = calculation.findAverage(listOfString);

        return new ResponseEntity<>("result" + resultList + "\nMax: " + max + "\nMin: " + min + "\nAverage: " + avg , HttpStatus.OK);
    }

    @PostMapping("/decrypt")
    public ResponseEntity<?> bulkDecrypt(@RequestBody List<String> listOfString) {
        List<String> resultList = listOfString.stream().map(x -> decrypt(x, 1)).toList();

        return new ResponseEntity<>("result" + resultList, HttpStatus.OK);
    }

    @PostMapping("/counter")
    public ResponseEntity<?> counter() {

        CounterThread threadCounter = new CounterThread();
        threadCounter.start();

        return ResponseEntity.ok(Counter.getCounter());
    }


    @PostMapping("/createNewDecode")
    public Integer methodDecode(@RequestBody Result result) throws URLArgumentsException {
        checkSrting(result.getCode());

        Result result1 = encryptionService.findOneByCode(result.getCode());

        if(result1 == null){
            int id = resultAsync.createHalfEmptyModel(result);
            resultAsync.computeAsync(id);
            return id;
        }
        else{
            return result1.getId();
        }

    }

    @PostMapping("/createNewCode")
    public Integer methodCode(@RequestBody Result result) throws URLArgumentsException {
        checkSrting(result.getDecode());

        Result result1 = encryptionService.findOneByDecode(result.getDecode());

        if(result1 == null){
            int id = resultAsync.createHalfEmptyModelToDecode(result);
            resultAsync.computeAsyncSecond(id);
            return id;
        }
        else{
            return result1.getId();
        }

    }

    @GetMapping("/find/{id}")
    public Result result(@PathVariable("id") int id){
        return encryptionService.findOne(id);
    }

}
