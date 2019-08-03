package com.example.m.agendacontato.database;

/**
 * Created by m on 10/12/17.
 */

public class ScriptSQL {

    //é um metodo estatico para que não precise criar  uma instacia dessa classe
    public static String getCreateContato(){
        //tabela que contém os campos do registro de umnovo contato
        //concatenar uma grande string com a instrução sql
        StringBuilder sqlbuilder = new StringBuilder();
        sqlbuilder.append("CREATE TABLE IF NOT EXISTS CONTATO( ");
        sqlbuilder.append(" _id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, ");
        sqlbuilder.append("NOME                               VARCHAR(200), ");
        sqlbuilder.append("TELEFONE                            VARCHAR(14), ");
        sqlbuilder.append("TIPOTELEFONE                         VARCHAR(1), ");
        sqlbuilder.append("EMAIL                              VARCHAR(255), ");
        sqlbuilder.append("TIPOEMAIL                            VARCHAR(1), ");
        sqlbuilder.append("ENDERECO                           VARCHAR(255), ");
        sqlbuilder.append("TIPOENDERECO                         VARCHAR(1), ");
        sqlbuilder.append("DATASESPECIAIS                             DATE, ");
        sqlbuilder.append("TIPOSDATASESPECIAIS                  VARCHAR(1), ");
        sqlbuilder.append("GRUPOS                            VARCHAR(255)); ");
        //retorno a variável com o script
        return sqlbuilder.toString();
    }
}
