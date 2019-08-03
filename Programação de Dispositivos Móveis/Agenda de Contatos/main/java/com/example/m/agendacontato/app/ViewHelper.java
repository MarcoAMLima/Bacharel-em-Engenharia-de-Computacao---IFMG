package com.example.m.agendacontato.app;

import android.content.Context;
import android.widget.ArrayAdapter;
import android.widget.Spinner;

import com.example.m.agendacontato.R;

/**
 * Created by m on 16/12/17.
 */

//ajudar na criação de componentes de visualização
public class ViewHelper {

    public static ArrayAdapter<String> createArrayAdapter(Context ctx, Spinner spinner){
        ArrayAdapter arrayAdapter = new ArrayAdapter<String>(ctx, android.R.layout.simple_list_item_1);
        arrayAdapter.setDropDownViewResource(R.layout.support_simple_spinner_dropdown_item);

        spinner.setAdapter(arrayAdapter);//associando o spinner ao array adapter
        return arrayAdapter;
    }
}
