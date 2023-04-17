package com.example.encryption.exceptions;

import com.example.encryption.controllers.EncryptionControllers;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.ResponseStatus;

import org.apache.logging.log4j.Logger;
import org.apache.logging.log4j.LogManager;


@ResponseStatus(code = HttpStatus.BAD_REQUEST, reason = "invalid data")
public class URLArgumentsException extends Exception {

    private static final Logger logger = LogManager.getLogger(EncryptionControllers.class.getName());

    public URLArgumentsException(String message) {
        super(message);
        logger.error("exception:" + message);
    }

}
