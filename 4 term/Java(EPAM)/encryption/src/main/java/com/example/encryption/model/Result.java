package com.example.encryption.model;


import jakarta.persistence.*;

@Entity
@Table(name = "coder")
public class Result {


    @Id
    @Column(name = "id")
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    public Result(){
    }

    @Column(name = "code")//original
    private String code;
    @Column(name = "decode")
    private String decode;

    public Result(String code,String decode) {
        this.code = code;
        this.decode = decode;
    }

    public void setId(int id) {this.id = id;}

    public void setCode(String code) {this.code = code;}

    public void setDecode(String decode) {this.decode = decode;}

    public int getId() {return id;}

    public String getCode() {return code;}

    public String getDecode() {return decode;}


    @Override
    public String toString() {
        return "Result{" +
                "id=" + id +
                ", code='" + code + '\'' +
                ", decode='" + decode + '\'' +
                '}';
    }
}
