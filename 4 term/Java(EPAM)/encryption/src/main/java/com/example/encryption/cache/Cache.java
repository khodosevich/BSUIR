package com.example.encryption.cache;

import org.springframework.stereotype.Component;

import java.util.HashMap;
import java.util.Map;

@Component
public class Cache<K,V> {
    Map<K,V> cache = new HashMap<K,V>();

    public boolean contains(K key){
        return cache.containsKey(key);
    }

    public void push(K key, V value) {
        if(!cache.containsKey(key)){
            cache.put(key,value);
        }
    }

    public V pop(K key) {
       return cache.get(key);
    }


}
