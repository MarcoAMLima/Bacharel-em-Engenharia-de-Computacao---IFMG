package com.example.m.agendacontato.database;

/**
 * Created by m on 10/12/17.
 */

//library do banco de dados
import android.database.sqlite.*;
import android.content.Context;


//SqliteOpenHelper é uma classe abstrata logo ela precisa herdar de alguem
public class DataBase extends SQLiteOpenHelper {

    //construtor
    public DataBase(Context context){
        //chamando o construtor da classe pai
        //referencia da classe, nome do bd,terceira nada pois não será alterado o parametro,versão do bd
        //sempre que houver alterações no bd deve-se alterar a versão
        super(context,"Contatinhos",null,1);

    }


    //responsavel pela criação das tabelas
    @Override
    public void onCreate(SQLiteDatabase db) {
        //passando o script de criação da tabela
        db.execSQL(ScriptSQL.getCreateContato());
    }

    //responsavel pela atualização das tabelas
    @Override
    public void onUpgrade(SQLiteDatabase sqLiteDatabase, int i, int i1) {

    }
}
