package com.example.encryption.async;

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
    public ResultAsync(EncryptionService resultService,EncryptService encryptService){
        this.resultService = resultService;
        this.encryptService = encryptService;
    }


    public int createHalfEmptyModel(Result result){
        Result result1 = new Result();

        result1.setCode(result.getCode());
        resultService.save(result1);

        return result1.getId();
    }

    public int createHalfEmptyModelToDecode(Result result){
        Result result1 = new Result();

        result1.setDecode(result.getDecode());
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

    public CompletableFuture<Integer> computeAsyncSecond(int id){
        return CompletableFuture.supplyAsync(() ->{
                Result result = resultService.findOne(id);
                result.setCode(EncryptService.decrypt(result.getDecode(),1));
                resultService.save(result);
                return result.getId();
        });
    }



}
