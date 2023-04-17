package com.example.encryption.async;


import com.example.encryption.calculation.Calculation;
import com.example.encryption.model.EncryptService;
import com.example.encryption.model.Result;
import com.example.encryption.service.EncryptionService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.concurrent.CompletableFuture;

@Component
public class ResultAsync {
    private final EncryptionService resultService;
    public final EncryptService encryptService;

    @Autowired
    public ResultAsync(EncryptionService resultSerivce,EncryptService encryptService){
        this.resultService = resultSerivce;
        this.encryptService = encryptService;
    }


    public int createAsync(Result result){
        Result result1 = new Result();

        result1.setCode(result.getCode());
        resultService.save(result1);

        return result1.getId();
    }

    public CompletableFuture<Integer> computeAsync(int id){
        return CompletableFuture.supplyAsync(() ->{
           try{
               Result result = resultService.findOne(id);

               Thread.sleep(15000);
               result.setDecode(EncryptService.encrypt(result.getCode(),1));

               resultService.save(result);
               return result.getId();
           } catch (InterruptedException e) {
               throw new RuntimeException(e);
           }
        });
    }



}
