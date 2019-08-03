package com.example.m.agendacontato.dominio;

import android.content.ContentValues;
import android.content.Context;
import android.database.*;
import android.database.sqlite.*;
import android.widget.ArrayAdapter;
import android.widget.*;

import com.example.m.agendacontato.ContatoArrayAdapter;
import com.example.m.agendacontato.dominio.entidades.Contato;

import com.example.m.agendacontato.R;

import java.util.Date;

/**
 * Created by m on 13/12/17.
 */

public class RepositorioContato {

    private SQLiteDatabase conn;

    //construtor
    //criar a conexão com o banco de dados
    public RepositorioContato(SQLiteDatabase conn){
        this.conn = conn;
    }

    //criado pois inserir e alterar utilizam os memos values
    private ContentValues preencheContentValues(Contato contato)
    {
        //classe responsavel por armazenar registros
        ContentValues values = new ContentValues();

        values.put(Contato.NOME, contato.getNome());
        values.put(Contato.TELEFONE, contato.getTelefone());
        values.put(Contato.TIPOTELEFONE, contato.getTipoTelefone());
        values.put(Contato.EMAIL, contato.getEmail());
        values.put(Contato.TIPOEMAIL, contato.getTipoEmail());
        values.put(Contato.ENDERECO, contato.getEndereco());
        values.put(Contato.TIPOENDERECO, contato.getTipoEndereco());
        values.put(Contato.DATAS, contato.getDatas().getTime());
        values.put(Contato.TIPOSDATAS, contato.getTipoDatas());
        values.put(Contato.GRUPOS, contato.getGrupos());

        return values;
    }

    //metodo para excluir um contato, passa apenas a chave primaria da tabela
    public void ExcluirContato(long id){
        //passa a tabela e o id da tabela
        conn.delete(Contato.TABELA, " _id = ? ", new String[]{String.valueOf(id)});
    }

    public void AlterarContatos(Contato contato){
        //classe responsave por armazenar registros
        ContentValues values = preencheContentValues(contato);
        //atualizando os dados na tabela, nome da tabela, o objeto, o filtro de operação ou seja o indentificador do registro
        conn.update(Contato.TABELA,  values, " _id = ? ", new String[]{String.valueOf(contato.getId_())}); //é preciso conveter o id para string
    }

    //metodo de inserção de registros
    public void InserirContatos(Contato contato){
        ContentValues values = preencheContentValues(contato);
        //inserindo o dado na tabela, nome da tabela, chave primaria auto increment, e o objeto
        conn.insertOrThrow(Contato.TABELA, null, values);
    }

    //vai retornar lá no list view a lista de contatos(tela de contatos principal)
    public ContatoArrayAdapter BuscaContatinhos(Context context){

        ContatoArrayAdapter adpContatinhos = new ContatoArrayAdapter(context,R.layout.item_contato);//lista de objetos do tipo de Contato com o layout personalizados

        //Classe Cursor Responsavel por armazenar todos os registros armazenados
        //metodo que retornar os dados da tabela, passando o nome da tabela e se quiser mais algo(Consulta)
        Cursor cursor = conn.query(Contato.TABELA, null, null, null, null, null, null);

        //se houver retorno na pesquisa
        if (cursor.getCount()>0){

            //colocar o cursor no primeiro registro
            cursor.moveToFirst();

            do {//para percorrer o banco de dados enquanto haja contatos

                Contato contato = new Contato();
                //Exibir os dados
                //o columnindex recupeara automaticamente sem precisar passar a posição na tabela
                contato.setId_(cursor.getLong(cursor.getColumnIndex(Contato.ID)));
                contato.setNome(cursor.getString(cursor.getColumnIndex(Contato.NOME)));
                contato.setTelefone(cursor.getString(cursor.getColumnIndex(Contato.TELEFONE)));
                contato.setTipoTelefone(cursor.getString(cursor.getColumnIndex(Contato.TIPOTELEFONE)));
                contato.setEmail(cursor.getString(cursor.getColumnIndex(Contato.EMAIL)));
                contato.setTipoEmail(cursor.getString(cursor.getColumnIndex(Contato.TIPOEMAIL)));
                contato.setEndereco(cursor.getString(cursor.getColumnIndex(Contato.ENDERECO)));
                contato.setTipoEndereco(cursor.getString(cursor.getColumnIndex(Contato.TIPOENDERECO)));
                contato.setDatas(new Date(cursor.getLong(cursor.getColumnIndex(Contato.DATAS))));
                contato.setTipoDatas(cursor.getString(cursor.getColumnIndex(Contato.TIPOSDATAS)));
                contato.setGrupos(cursor.getString(cursor.getColumnIndex(Contato.GRUPOS)));


                adpContatinhos.add(contato);
            }while(cursor.moveToNext());
        }
        return adpContatinhos;
    }
}
