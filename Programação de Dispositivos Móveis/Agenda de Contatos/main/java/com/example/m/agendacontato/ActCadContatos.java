package com.example.m.agendacontato;

import android.app.DatePickerDialog;
import android.content.Intent;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.Spinner;

import com.example.m.agendacontato.app.MessageBox;
import com.example.m.agendacontato.app.ViewHelper;
import com.example.m.agendacontato.database.DataBase;
import com.example.m.agendacontato.dominio.RepositorioContato;
import com.example.m.agendacontato.dominio.entidades.Contato;
import com.example.m.agendacontato.util.DateUtils;

import java.text.DateFormat;
import java.util.Calendar;
import java.util.Date;

public class ActCadContatos extends AppCompatActivity {
    //edits texto
    private EditText edtNome;
    private EditText edtEmail;
    private EditText edtEndereco;
    private EditText edtTelefone;
    private EditText edtGrupos;
    private EditText edtDatas;

    //spinners de opções
    private Spinner spnTelefone;
    private Spinner spnEmail;
    private Spinner spnDatas;
    private Spinner spnEndereco;

    //ArrayAdaters para criar as opções do sppiners
    private ArrayAdapter<String> adpTelefone;
    private ArrayAdapter<String> adpEmail;
    private ArrayAdapter<String> adpDatas;
    private ArrayAdapter<String> adpEndereco;


    //objeto do tipo do bd
    private DataBase database;
    //objeto para fazer a conexão com o bd
    private SQLiteDatabase conn;
    //objeto do tipo repositorio contato
    private RepositorioContato repositorioContato;
    //objeto do tipo contato para relaizar a inserção
    private Contato contato;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.act_cad_contatos);


        //instanciar os objetos, recuperar os objetos da tela de adcionar o contato
        edtDatas = (EditText)findViewById(R.id.edtDatas);
        edtEmail = (EditText)findViewById(R.id.edtEmail);
        edtEndereco = (EditText)findViewById(R.id.edtEndereco);
        edtGrupos = (EditText)findViewById(R.id.edtGrupos);
        edtTelefone = (EditText)findViewById(R.id.edtTelefone);
        edtNome = (EditText)findViewById(R.id.edtNome);

        spnDatas = (Spinner)findViewById(R.id.spnDatas);
        spnEmail = (Spinner)findViewById(R.id.spnEmail);
        spnEndereco = (Spinner)findViewById(R.id.spnEndereco);
        spnTelefone = (Spinner)findViewById(R.id.spnTelefone);

        //Configurando o arrayAdater dos Sppiners, chamando a classe ViewHelper que foi criada para isso
        adpEmail = ViewHelper.createArrayAdapter(this,spnEmail);
        adpEndereco = ViewHelper.createArrayAdapter(this,spnEndereco);
        adpTelefone = ViewHelper.createArrayAdapter(this,spnTelefone);
        adpDatas = ViewHelper.createArrayAdapter(this,spnDatas);


        /*adpTelefone = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1);
        adpTelefone.setDropDownViewResource(R.layout.support_simple_spinner_dropdown_item);

        adpEmail = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1);
        adpEmail.setDropDownViewResource(R.layout.support_simple_spinner_dropdown_item);

        adpEndereco = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1);
        adpEndereco.setDropDownViewResource(R.layout.support_simple_spinner_dropdown_item);

        adpDatas = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1);
        adpDatas.setDropDownViewResource(R.layout.support_simple_spinner_dropdown_item);

        //Associar os spinners aos arraysAdptars
        spnDatas.setAdapter(adpDatas);
        spnEmail.setAdapter(adpEmail);
        spnEndereco.setAdapter(adpEndereco);
        spnTelefone.setAdapter(adpTelefone);*/

        //Adicionando as opções nos Arrays dos sppiners
        adpEmail.add("Trabalho");
        adpEmail.add("Pessoal");
        adpEmail.add("Outros");

        adpTelefone.add("Principal");
        adpTelefone.add("Casa");
        adpTelefone.add("Celular");
        adpTelefone.add("Trabalho");
        adpTelefone.add("Outros");

        adpEndereco.add("Casa");
        adpEndereco.add("Trabalho");
        adpEndereco.add("Outros");

        adpDatas.add("Aniversário");
        adpDatas.add("Data Comemorativa");
        adpDatas.add("Outros");

        ExibeDataListener listener = new ExibeDataListener();
        edtDatas.setOnClickListener(listener);
        edtDatas.setOnFocusChangeListener(listener);

        //retornar a referencia passada pelo intent anteriror
        Bundle bundle = getIntent().getExtras();
        //ESSA COMPARAÇÃO AI SERVIR PARA QUE EU SAIBA, O QUE EU FAREI INSERIR OU ALTERAR
        if((bundle != null)&&(bundle.containsKey(ActContato.PAR_CONTATO))){//se isso for verdade eu vou recuperar o objeto
            contato = (Contato)bundle.getSerializable(ActContato.PAR_CONTATO);
            preencheDados();//chama a função para preencher os dados
        }else
            //instancia um novo contato
            contato = new Contato();

        //criando a conexão com o banco de dados
        //instaciando e testando o bd
        try {
            database = new DataBase(this);
            conn = database.getReadableDatabase();//criando e abrindo o bd
            //criando o repositorio para pesquisa
            repositorioContato =  new RepositorioContato(conn);
        }catch (SQLException ex){
            MessageBox.show(this, "Erro","Erro na criação do BD"+ ex.getMessage());
        }
    }

    //configuração do menu, associando o menu a essa classe
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        //classe responsavel pela assciação do menu com o acivity
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.menu_act_cad_contatos, menu);

        if (contato.getId_() != 0){//apenas se eu não tiver iinserindo
            //fazer com que o menu de exclusão fique visivel, o excluir é o indice 1
            menu.getItem(1).setVisible(true);
        }

        return super.onCreateOptionsMenu(menu);
    }

    //configura quais itens serão selecionados no menu
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {

        switch (item.getItemId()){
            case R.id.acao_1:
                SalvarContatinhos();//chamar o metod para salvar ou alterar o conatinho
                finish();//metodo para finalizar a operação e voltar para o fragment anterior
                break;
            case R.id.acao_2:
                ExcluirContatinho();//chama o metodo de exclusão
                finish();
                break;
        }

        return super.onOptionsItemSelected(item);
    }

    //esse metodo fará com que quando eu selecionar um contato, preencha os dados do contato
    private void preencheDados() {
        edtNome.setText(contato.getNome());
        edtTelefone.setText(contato.getTelefone());
        spnTelefone.setSelection(Integer.parseInt(contato.getTipoTelefone()));//quando é inserido um item no spinner é atribuido uma posiçao do tipo string, e para recuperar a posição do sppiner eu preciso passar a posição em inteiro, toma no cu!fiquei uma hora nisso aqui.
        edtEmail.setText(contato.getEmail());
        spnEmail.setSelection(Integer.parseInt(contato.getTipoEmail()));
        edtEndereco.setText( contato.getEndereco());
        spnEndereco.setSelection(Integer.parseInt(contato.getTipoEndereco()));

        //é preciso converter essa maldita denovo
        DateFormat format = DateFormat.getDateInstance(DateFormat.SHORT);
        String dt = format.format(contato.getDatas());
        edtDatas.setText(dt);
        spnDatas.setSelection(Integer.parseInt(contato.getTipoDatas()));

        edtGrupos.setText(contato.getGrupos());

    }

    //esse metodo chamara o metod de exclusão
    private void ExcluirContatinho(){
        try {
            repositorioContato.ExcluirContato(contato.getId_());
        }catch (Exception ex){
            MessageBox.show(this, "Erro","Erro de Exclusão"+ ex.getMessage());
        }
    }

    //metodo para recuperar o que o user vai digitar e armazenar no banco de dados ou alterar o conteudo
    private void SalvarContatinhos(){
        //referencia do tipo do contato
        //edits texto
        try {
            contato.setNome(edtNome.getText().toString());
            contato.setTelefone(edtTelefone.getText().toString());
            contato.setEmail(edtEmail.getText().toString());
            contato.setEndereco(edtEndereco.getText().toString());

            contato.setGrupos(edtGrupos.getText().toString());

            //sppiners recuperar a opção selecionada
            contato.setTipoDatas(String.valueOf(spnDatas.getSelectedItemPosition()));
            contato.setTipoEmail(String.valueOf(spnEmail.getSelectedItemPosition()));
            contato.setTipoTelefone(String.valueOf(spnTelefone.getSelectedItemPosition()));
            contato.setTipoEndereco(String.valueOf(spnEndereco.getSelectedItemPosition()));

            if(contato.getId_()==0){//se igual a 0 chama o metodo de inserção
                repositorioContato.InserirContatos(contato);
            }else{//senão chama o metodo de alteração
                repositorioContato.AlterarContatos(contato);
            }
        }catch (Exception ex){
            MessageBox.show(this, "Erro","Erro ao salvar"+ ex.getMessage());
        }
    }


    //as três funções abaixo são para exibir o calendário no campo calendário
    private void exibeData(){
        Calendar calendar = Calendar.getInstance();

        int ano =  calendar.get(Calendar.YEAR);
        int mes =  calendar.get(Calendar.MONTH);
        int dia =  calendar.get(Calendar.DAY_OF_MONTH);

        DatePickerDialog dlg = new DatePickerDialog(this, new SelecionaDataListener(), ano, mes, dia);
        dlg.show();
    }

    private class ExibeDataListener implements View.OnClickListener, View.OnFocusChangeListener{
        @Override
        public void onClick(View v) {
            exibeData();
        }

        @Override
        public void onFocusChange(View v, boolean hasFocus) {
            if (hasFocus)
                exibeData();
        }

    }

    private class SelecionaDataListener implements DatePickerDialog.OnDateSetListener{
        @Override
        public void onDateSet(DatePicker view, int year, int monthOfYear, int dayOfMonth) {
            String dt = DateUtils.dateToString(year,monthOfYear,dayOfMonth);//converte a data em string

            Date data = DateUtils.getDate(year,monthOfYear,dayOfMonth);//retornar a data do computador

            edtDatas.setText(dt);
            contato.setDatas(data);

        }

    }

}
