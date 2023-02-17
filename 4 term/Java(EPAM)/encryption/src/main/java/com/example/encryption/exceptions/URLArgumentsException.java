package com.example.encryption.exceptions;

import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.ResponseStatus;

@ResponseStatus(code = HttpStatus.BAD_REQUEST, reason = "invalid data")
public class URLArgumentsException extends Exception {
    public URLArgumentsException(String message){
        super(message);
    }
}
