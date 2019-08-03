package com.example.m.agendacontato;

import android.content.Context;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import com.example.m.agendacontato.dominio.entidades.Contato;

/**
 * Created by m on 16/12/17.
 */

//está classe é para fazer um layout pesonalizavel para o ArrayAdapter
public class ContatoArrayAdapter extends ArrayAdapter<Contato> {

    private int resource = 0;
    //o objeto view irá armazenar o novo layout criado
    private LayoutInflater inflater;
    private Context context;//esse objeto me permite alerar o conteudo da pasta res

    public ContatoArrayAdapter(Context context, int resource){
        super(context,resource);
        inflater = (LayoutInflater)context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);//essa linha irá gerar uma interface para cada contato da minha listview
        this.resource = resource;
        this.context = context;
    }

    @Override
    public View getView(int position,View convertView,ViewGroup parent) {
        View view = null;
        ViewHolder viewHolder = null;
        if(convertView == null){
            //instancia a classe viewHolder
            viewHolder = new ViewHolder();
            view = inflater.inflate(resource,parent,false);
            viewHolder.txtCor = (TextView)view.findViewById(R.id.txtCor);
            viewHolder.txtNome = (TextView)view.findViewById(R.id.txtNome);
            viewHolder.txtTelefone = (TextView)view.findViewById(R.id.txtTelefone);
            view.setTag(viewHolder);
            convertView = view;
        }else{
            viewHolder = (ViewHolder)convertView.getTag();
            view = convertView;
        }

        Contato contato = getItem(position);
        //viewHolder.txtCor.setBackground();
        viewHolder.txtNome.setText(contato.getNome());
        viewHolder.txtTelefone.setText(contato.getTelefone());


        return view;
    }

    static class ViewHolder{
        //recuperar os itens do meu layout personalizavel
          TextView txtCor;
          TextView txtNome;
          TextView txtTelefone;
    }
}
