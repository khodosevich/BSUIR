package com.example.encryption.controllers;

import com.example.encryption.exceptions.URLArgumentsException;
import org.json.JSONException;
import org.json.JSONObject;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.spec.SecretKeySpec;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.nio.charset.Charset;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.util.Base64;

@RestController
public class StartControllers {

    @GetMapping("/encrypt")
    public String ecryption(@RequestParam("string") String string,
                            @RequestParam("operation") boolean operation) throws NoSuchPaddingException,
            IllegalBlockSizeException, NoSuchAlgorithmException,
            BadPaddingException, InvalidKeyException, JSONException, IOException, URLArgumentsException {



        final String key = "knowledgefactory";
        String result;

        if (operation) {
            checkSrting(string);
            result = encrypt(string, key);
        } else {
            result = decrypt(string, key);
        }

        JSONObject obj = new JSONObject();

        obj.put("result: ", result);

        return obj.toString();

    }


    public static String encrypt(String password, String key) throws
            NoSuchAlgorithmException, NoSuchPaddingException,
            InvalidKeyException, IllegalBlockSizeException,
            BadPaddingException, UnsupportedEncodingException {

        byte[] KeyData = key.getBytes();

        SecretKeySpec KS = new SecretKeySpec(KeyData, "Blowfish");

        Cipher cipher = Cipher.getInstance("Blowfish");
        cipher.init(Cipher.ENCRYPT_MODE, KS);

        String encryptedtext = Base64.getEncoder().
                encodeToString(cipher.doFinal(password.getBytes("UTF-8")));

        return encryptedtext;
    }

    public static String decrypt(String encryptedtext, String key)
            throws NoSuchAlgorithmException, NoSuchPaddingException,
            InvalidKeyException, IllegalBlockSizeException,
            BadPaddingException {

        byte[] KeyData = key.getBytes();

        SecretKeySpec KS = new SecretKeySpec(KeyData, "Blowfish");

        byte[] ecryptedtexttobytes = Base64.getDecoder().decode(encryptedtext);

        Cipher cipher = Cipher.getInstance("Blowfish");
        cipher.init(Cipher.DECRYPT_MODE, KS);

        byte[] decrypted = cipher.doFinal(ecryptedtexttobytes);
        String decryptedString = new String(decrypted, Charset.forName("UTF-8"));

        return decryptedString;

    }


    public static boolean checkSrting(String str) throws URLArgumentsException {

        char []strToChars = str.toCharArray();

        for (int i = 0 ; i < strToChars.length ; i++){
            if(strToChars[i] >= '1' && strToChars[i] <= '9'){
                throw new URLArgumentsException("You entered numbers!");
            }
        }

        return true;
    }


}
