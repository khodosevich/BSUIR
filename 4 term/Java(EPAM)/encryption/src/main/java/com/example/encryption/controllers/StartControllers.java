package com.example.encryption.controllers;

import com.example.encryption.exceptions.URLArgumentsException;
import org.json.JSONException;
import org.json.JSONObject;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.logging.Logger;

@RestController
public class StartControllers {

    private static final Logger logger = Logger.getLogger(StartControllers.class.getName());
    private static final int key = 3;

    @GetMapping("/encrypt")
    public String ecryption(@RequestParam("string") String string,
                            @RequestParam("operation") boolean operation) throws  JSONException, URLArgumentsException {

        String result = "";

        if (operation) {
            checkSrting(string);
            result = encrypt(string);
        } else {
            result = decrypt(string);
        }


        JSONObject obj = new JSONObject();

        obj.put("result: ", result);


        logger.info("good");

        return obj.toString();

    }


    public static String encrypt(String wordToEncrypt){

        char []arr = new char[wordToEncrypt.length()];

        for (int i = 0; i < wordToEncrypt.length(); i++) {
            if( Character.isLetter(wordToEncrypt.charAt(i)) && Character.isUpperCase(wordToEncrypt.charAt(i)) ){
                arr[i] = (char) (((((int) (wordToEncrypt.charAt(i))) - 65 + key) % 26) + 65);
            }
            else if(Character.isLetter(wordToEncrypt.charAt(i)) && Character.isLowerCase(wordToEncrypt.charAt(i))){
                arr[i] = (char) (((((int) (wordToEncrypt.charAt(i))) - 97 + key) % 26) + 97);
            }
            else{
                arr[i] = wordToEncrypt.charAt(i);
            }
        }

        String newWord =  String.copyValueOf(arr);

        return newWord;
    }

    public static String decrypt(String encryptedtext) {

        char []arr = new char[encryptedtext.length()];

        for (int i = 0; i < encryptedtext.length(); i++) {

            if( Character.isLetter(encryptedtext.charAt(i)) && Character.isUpperCase(encryptedtext.charAt(i)) ){
                arr[i] = (char) (((((int) (encryptedtext.charAt(i))) - 65 - key) % 26) + 65);
            }

            else if(Character.isLetter(encryptedtext.charAt(i)) && Character.isLowerCase(encryptedtext.charAt(i))){
                arr[i] = (char) (((((int) (encryptedtext.charAt(i))) - 97 - key) % 26) + 97);
            }
            else{
                arr[i] = encryptedtext.charAt(i);
            }

        }

        String newWord =  String.copyValueOf(arr);

        return newWord;


    }


    public static boolean checkSrting(String str) throws URLArgumentsException {

        char []strToChars = str.toCharArray();

        for (int i = 0 ; i < strToChars.length ; i++){
            if(strToChars[i] >= '0' && strToChars[i] <= '9'){
                throw new URLArgumentsException("You entered numbers!");
            }
        }
        return true;
    }
}
