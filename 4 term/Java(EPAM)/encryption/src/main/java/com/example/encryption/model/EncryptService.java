package com.example.encryption.model;


import com.example.encryption.controllers.StartControllers;
import com.example.encryption.exceptions.URLArgumentsException;

import java.util.logging.Logger;

public class EncryptService {

    private static final Logger logger = Logger.getLogger(StartControllers.class.getName());

    public static String encrypt(String text , int n ) {

        if (n <= 0 || text == null || text.isEmpty()) {
            logger.info("Word cant encrypt!");
            return text;
        }

        StringBuilder firstPart = new StringBuilder();
        StringBuilder secondPart = new StringBuilder();
        for (int i = 0; i < text.length(); i++) {
            char aChar = text.charAt(i);
            if (i % 2 == 1) {
                firstPart.append(aChar);
            } else {
                secondPart.append(aChar);
            }
        }
        logger.info("Encrypt is good!");
        return encrypt(firstPart.append(secondPart).toString(), --n);

    }

    public static String decrypt(final String encryptedText, int n) {
        if (n <= 0 || encryptedText == null ||  encryptedText.isEmpty()) {
            logger.info("Word cant decrypt!");
            return encryptedText;
        }

        StringBuilder text = new StringBuilder();
        final int half = encryptedText.length() / 2;
        for (int i = 0; i < half; i++) {
            text.append(encryptedText.charAt(half + i)).append(encryptedText.charAt(i));
        }
        if (encryptedText.length() % 2 == 1) {
            text.append(encryptedText.charAt(encryptedText.length() - 1));
        }
        logger.info("Word decrypt!");
        return decrypt(text.toString(), --n);
    }


    public static boolean checkSrting(String str) throws URLArgumentsException {

        char[] strToChars = str.toCharArray();

        for (int i = 0; i < strToChars.length; i++) {
            if (strToChars[i] >= '0' && strToChars[i] <= '9') {
                logger.info("String has number!");
                throw new URLArgumentsException("You entered numbers!");
            }
        }
        return true;
    }

}