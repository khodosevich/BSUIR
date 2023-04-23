package com.example.encryption.service;

import com.example.encryption.model.Result;
import com.example.encryption.repositories.ResultRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Optional;

@Service
public class EncryptionService {

    private final ResultRepository resultRepository;

    @Autowired
    public EncryptionService(ResultRepository resultRepository){this.resultRepository = resultRepository;}


    public void save(Result result){
        resultRepository.save(result);
    }

    public Result findOne(int id){
        Optional<Result> foundResult = resultRepository.findById(id);
        return foundResult.orElse(null);
    }

    public Result findOneByCode(String code){
        Optional<Result> foundResult = Optional.ofNullable(resultRepository.findByCode(code));
        return foundResult.orElse(null);
    }

    public Result findOneByDecode(String decode){
        Optional<Result> foundResult = Optional.ofNullable(resultRepository.findByDecode(decode));
        return foundResult.orElse(null);
    }

}
