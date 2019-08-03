package com.example.m.agendacontato.dominio.entidades;

import java.io.Serializable;
import java.util.Date;

/**
 * Created by m on 13/12/17.
 */

//Serializable para trabalhar com dados de entrada e saida
public class Contato implements Serializable {

    //variaveis estaticas para facilitar na hora de rrecuperar o valor do campo da tabela
    public static String TABELA ="CONTATO"; //TODA EZ QUE EU USAR A TABELA COMO REFERENCIA EU POSSO PASSAR A VARIAVEL AO INVEZ DO NOME ISSO FACILITA TAMBEM NA HORA DE MUDAR O NOME DA TABELA
    public static String ID = "_id";
    public static String NOME = "NOME";
    public static String TELEFONE = "TELEFONE";
    public static String TIPOTELEFONE = "TIPOTELEFONE";
    public static String EMAIL = "EMAIL";
    public static String TIPOEMAIL = "TIPOEMAIL";
    public static String ENDERECO = "ENDERECO";
    public static String TIPOENDERECO = "TIPOENDERECO";
    public static String DATAS = "DATASESPECIAIS";
    public static String TIPOSDATAS = "TIPOSDATASESPECIAIS";
    public static String GRUPOS = "GRUPOS";

    //variaveis que compõe os campos dos registros
    private long id_;
    private String nome;
    private String telefone;
    private String TipoTelefone;
    private String email;
    private String TipoEmail;
    private String endereco;
    private String TipoEndereco;
    private Date datas;
    private String TipoDatas;
    private String grupos;

    //construtor
    public Contato(){
        //zerando o id para que sempre que criar um novo contato
        id_ = 0 ;
    }


    //metodos gets e sets dos atributos da classe
    public long getId_() {
        return id_;
    }

    public void setId_(long id_) {
        this.id_ = id_;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getTelefone() {
        return telefone;
    }

    public void setTelefone(String telefone) {
        this.telefone = telefone;
    }

    public String getTipoTelefone() {
        return TipoTelefone;
    }

    public void setTipoTelefone(String tipoTelefone) {
        TipoTelefone = tipoTelefone;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getTipoEmail() {
        return TipoEmail;
    }

    public void setTipoEmail(String tipoEmail) {
        TipoEmail = tipoEmail;
    }

    public String getEndereco() {
        return endereco;
    }

    public void setEndereco(String endereco) {
        this.endereco = endereco;
    }

    public String getTipoEndereco() {
        return TipoEndereco;
    }

    public void setTipoEndereco(String tipoEndereco) {
        TipoEndereco = tipoEndereco;
    }

    public Date getDatas() {
        return datas;
    }

    public void setDatas(Date datas) {
        this.datas = datas;
    }

    public String getTipoDatas() {
        return TipoDatas;
    }

    public void setTipoDatas(String tipoDatas) {
        TipoDatas = tipoDatas;
    }

    public String getGrupos() {
        return grupos;
    }

    public void setGrupos(String grupos) {
        this.grupos = grupos;
    }

    @Override
    public String toString(){
        return nome + " " + telefone;
    }
}
