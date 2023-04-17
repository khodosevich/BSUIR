package com.example.encryption.service;


import com.example.encryption.model.Result;
import com.example.encryption.repositories.ResultRepository;
import jakarta.transaction.Transactional;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Optional;

@Service
public class EncryptionService {

    private final ResultRepository resultRepository;

    @Autowired
    public EncryptionService(ResultRepository resultRepository){this.resultRepository = resultRepository;}


    @Transactional
    public void save(Result result){
        resultRepository.save(result);
    }

    @Transactional
    public Result findOne(int id){
        Optional<Result> foundResult = resultRepository.findById(id);
        return foundResult.orElse(null);
    }

}
