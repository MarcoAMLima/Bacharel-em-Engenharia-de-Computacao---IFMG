package com.example.m.agendacontato.util;

import android.widget.DatePicker;

import java.text.DateFormat;
import java.util.Calendar;
import java.util.Date;

/**
 * Created by m on 16/12/17.
 */

//classe utilitária que pode ser usada por toda a aplicação
public class DateUtils {

    public static Date getDate(int year, int monthOfYear, int dayOfMonth){//retorna a data
        //retornar a data do pc
        Calendar calendar = Calendar.getInstance();
        calendar.set(year,monthOfYear,dayOfMonth);
        Date data = calendar.getTime();
        return data;//retornar a data
    }

    //converter a data para string
    public static String dateToString(int year, int monthOfYear, int dayOfMonth){
        //retornar a data do pc
        Calendar calendar = Calendar.getInstance();
        calendar.set(year,monthOfYear,dayOfMonth);
        Date data = calendar.getTime();
        DateFormat format = DateFormat.getDateInstance(DateFormat.SHORT);
        String dt = format.format(data);

        return dt;//retornar a data convertida
    }

    //converter a data especifica para o tipo date
    public static String dateToString(Date date){
        DateFormat format = DateFormat.getDateInstance(DateFormat.SHORT);
        String dt = format.format(date);
        return dt;//retornar a data convertida
    }
}
