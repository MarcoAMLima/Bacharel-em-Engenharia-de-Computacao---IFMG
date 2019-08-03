package com.example.m.agendacontato;

import android.content.Intent;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.*;
import android.widget.*;

//biblioteca do banco
import android.database.sqlite.*;
import android.database.*;

import com.example.m.agendacontato.app.MessageBox;
import com.example.m.agendacontato.database.DataBase;
//importar o pacote que opera a pesquisa
import com.example.m.agendacontato.dominio.RepositorioContato;
import com.example.m.agendacontato.dominio.entidades.Contato;


//Adpter view ẃ para seleção de itens em lisas spinner e outros
public class ActContato extends AppCompatActivity implements View.OnClickListener,AdapterView.OnItemClickListener {

    //botão de adicionar contato
    private Button btnAdicionar;
    //edt de pesquisa
    private EditText edtPesquisa;
    //lista da tela adicionar
    private ListView lstContatos;
    //objeto do tipo do bd
    private DataBase database;
    //objeto para fazer a conexão com o bd
    private SQLiteDatabase conn;
    //Array adapter
    private ArrayAdapter<Contato> adpContatinhos;
    //objeto do tipo repositorio contato
    private RepositorioContato repositorioContato;

    //variavel estática para passagem de parametro do contato A TABELA GARANTE QUE O PARAMETRO NÃO SEJA PASSADO ERRADO, SE ISSO DER ERRAD DÁ MUITA MERDA
    public static final String PAR_CONTATO = "CONTATO";

    private FiltrarDados filtrarDados;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.act_contato);

        //instanciar os objetos, recuperar os objetos do layout
        btnAdicionar = (Button)findViewById(R.id.btnAdicionar);
        edtPesquisa = (EditText)findViewById(R.id.edtPesquisa);
        lstContatos = (ListView)findViewById(R.id.lstContatos);
        btnAdicionar.setOnClickListener(this);

        //vincular a lista ao evento de click
        lstContatos.setOnItemClickListener(this);

        //instaciando e testando o bd
        try {
            database = new DataBase(this);
            conn = database.getReadableDatabase();//criando e abrindo o bd
            //criando o repositorio para pesquisa
            repositorioContato =  new RepositorioContato(conn);

            adpContatinhos = repositorioContato.BuscaContatinhos(this);

            //linkar o ArrayAdpter com o listView
            lstContatos.setAdapter(adpContatinhos);
            filtrarDados = new FiltrarDados(adpContatinhos);//associar os contatos ao metodo de filtragem
            edtPesquisa.addTextChangedListener(filtrarDados);//associar o metod de filtrar dados a caixa de pesquisa

        }catch (SQLException ex){
            //passa o a referencia do activity+o titulo+mensagem
            MessageBox.show(this, "Erro","Erro na criação do BD"+ ex.getMessage());
        }
    }

    @Override
    public void onClick(View view) {
        //para chamar o activity de adicionar um novo contato
        Intent it = new Intent(this, ActCadContatos.class);
        startActivityForResult(it, 0);//atualizar o list view apos a realização de inserção
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        adpContatinhos = repositorioContato.BuscaContatinhos(this);
        filtrarDados.setArrayAdapter(adpContatinhos);//atualizar o array para que nãoa trapalhe a consulta
        //linkar o ArrayAdpter com o listView
        lstContatos.setAdapter(adpContatinhos);
    }

    //primeiro parametro reorna uma referencia para o comonene adpter,referencia do componente que disparou a chamada, posição do item selecionado, e o id do item
    @Override
    public void onItemClick(AdapterView<?> adapterView, View view, int position, long id) {
        Contato contato =  adpContatinhos.getItem(position);//recuperar o item selecionado

        Intent it = new Intent(this, ActCadContatos.class);

        //passar parametros de um activity para o outro
        it.putExtra(PAR_CONTATO,contato);

        startActivityForResult(it, 0);
    }

    private class FiltrarDados implements TextWatcher{

        private ArrayAdapter<Contato> arrayAdapter;

        private FiltrarDados(ArrayAdapter<Contato> arrayAdapter){//construtor
            this.arrayAdapter = arrayAdapter;
        }

        public void setArrayAdapter(ArrayAdapter<Contato> arrayAdapter){
            this.arrayAdapter = arrayAdapter;
        }

        @Override
        public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {

        }

        @Override//captura os dados quando o usuario tiver digitando algo na caixa de texto
        public void onTextChanged(CharSequence charSequence, int start, int before, int count) {
            arrayAdapter.getFilter().filter(charSequence);//filtra os dados digitados pelo user
        }

        @Override
        public void afterTextChanged(Editable editable) {

        }
    }
}
