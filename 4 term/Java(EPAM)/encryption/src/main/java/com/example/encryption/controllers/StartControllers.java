package com.example.encryption.controllers;

import com.example.encryption.exceptions.URLArgumentsException;
import org.json.JSONException;
import org.json.JSONObject;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.Arrays;
import java.util.logging.Logger;

@RestController
public class StartControllers {


    private static final Logger logger = Logger.getLogger(StartControllers.class.getName());

    @GetMapping("/encrypt")
    public String ecryption(@RequestParam("string") String string, @RequestParam("operation") boolean operation) throws JSONException, URLArgumentsException {

        String result = "";

        if (operation) {
            checkSrting(string);
            result = encrypt(string,string.length());
        } else {
            result = decrypt(string,string.length());
        }


        JSONObject obj = new JSONObject();

        obj.put("result: ", result);


        logger.info("good");

        return obj.toString();

    }


    public static String encrypt(String text , int n ) {



        if (n <= 0 || text == null || text.isEmpty()) {
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

        return encrypt(firstPart.append(secondPart).toString(), --n);

    }


    public static String decrypt(final String encryptedText, int n) {
        if (n <= 0 || encryptedText == null ||  encryptedText.isEmpty()) {
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

        return decrypt(text.toString(), --n);
    }


    public static boolean checkSrting(String str) throws URLArgumentsException {

        char[] strToChars = str.toCharArray();

        for (int i = 0; i < strToChars.length; i++) {
            if (strToChars[i] >= '0' && strToChars[i] <= '9') {
                throw new URLArgumentsException("You entered numbers!");
            }
        }
        return true;
    }
}
