package com.example.m.agendacontato.app;

import android.content.Context;
import android.support.v7.app.AlertDialog;

/**
 * Created by m on 16/12/17.
 */


//Classe responsável por exibir mensagens
public class MessageBox {

    public static void showInfo(Context ctx, String title, String msg) {//exibe um alerta de informação
        show(ctx,title,msg,android.R.drawable.ic_dialog_info);//icone padrão do android
    }

    public static void showAlert(Context ctx, String title, String msg) {//exibe um alerta
        show(ctx,title,msg,android.R.drawable.ic_dialog_alert);//icone padrão do android
    }

    public static void show(Context ctx, String title, String msg) {//exibe um alerta
        show(ctx,title,msg,0);//sem icone
    }

    //exibir mensagem caso haja erro de inserção exclusão e alterar, passando o contexto, titulo, mensagem
    public static void show(Context ctx, String title, String msg, int iconId){
        AlertDialog.Builder dlg = new AlertDialog.Builder(ctx);
        dlg.setIcon(iconId);
        dlg.setTitle(title);
        dlg.setMessage(msg);
        dlg.setNeutralButton("OK", null);
        dlg.show();
    }
}
