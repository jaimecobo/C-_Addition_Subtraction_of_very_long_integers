//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <stdlib.h>
#include <dstring.h>
#include <string.h>
#pragma hdrstop

#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
tnumero num1, num2, resultado;

//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
int estaen(char c, char *s)
{
  int i = 0;
  int esta = 0;

  while( (s[i] != 0) && ( !esta ) ){
    if (s[i] == c) esta = 1;
    i++;
  }
  return esta;
};

int cadenavalida(AnsiString cad)
{
 int n = cad.Length();
 if(n == 0) return 0;
 for(int i=1; i<=n; i++){
   if(i == 1){
     if(!estaen(cad[i],"+-0123456789") )
       return 0;// no valida
   }
   else{
    if ( !estaen(cad[i],"0123456789") )
     return 0;// no valida
   }
 };
 return 1;
};

AnsiString eliminarcerosizq(AnsiString cad)
{
  AnsiString aux = cad;

  while( (aux.Length()>0) &&  estaen(aux[1],"+-0") ){
    aux = aux.SubString(2,cad.Length()-1);
  }
  if(cad[1] == '-')
    aux = "-" + aux;
  if(aux.Length()==0) aux="0";

  return aux;
}

int milenght(char *cad)
{
  int i = 0;
  while( (cad[i]!=0) && (i<255) )
    i++;
  return i;
}

//---------------------------------------------------------------------------
tnodo::tnodo()
{
  info = 0;
  izq = der = 0;
}
//---------------------------------------------------------------------------
/* Inicializa todos la clase tnumero */
tnumero::tnumero()
{
  cabeza = 0;
};

void tnumero::insertarder(tnodo *p, int x)//ori
{
  tnodo *r, *q;

  if (p == 0){
   ShowMessage("Inserción en puntero nulo.");
  }
  else{
    q = new tnodo;
    if (q != 0){
      q->info = x;
      r = p->der;
      r->izq = q;
      q->der = r;
      q->izq = p;
      p->der = q;
    }
    else
      ShowMessage("Memoria insuficiente.");
  }
};

void tnumero::insertarizq(tnodo *p, int x)//clon
{
  tnodo *r, *q;

  if (p == 0){
   ShowMessage("Inserción en puntero nulo.");
  }
  else{
    q = new tnodo;
    if (q != 0){
      q->info = x;
      r = p->izq;
      r->der = q;
      q->izq = r;
      q->der = p;
      p->izq = q;
    }
    else
      ShowMessage("Memoria insuficiente.");
  }
};

void tnumero::borrar(tnodo *p,int& x)
{
  tnodo *r, *q;

  if (p==0){
    ShowMessage("Borrado de puntero nulo.");
  }
  else{
    x = p->info;
    q = p->izq;
    r = p->der;
    q->der = r;
    r->izq = q;
    delete p;
  };
};

void tnumero::borrartodo(void)
{
  tnodo *e, *q;

  if(cabeza != 0){
    q = cabeza->der;
    while( (q != cabeza) && (q != 0) ){
      e = q;
      q = q->der;
      delete e;
    };//while
    delete cabeza;
    cabeza = 0;
  };
};

void tnumero::asignarcabeza(tnodo *nuevacabeza)
{
  borrartodo();
  cabeza = nuevacabeza;
};

void tnumero::asignarvalor(AnsiString cadnum)
{
  int numnodo, i, k, nnodos = 0, n = cadnum.Length();
  tnodo *p;
  AnsiString aux, absnum;

  if( cadenavalida(cadnum) )
    cadnum = eliminarcerosizq(cadnum);// quitar los 0s del texto
  else{
    cadnum = "0";
    ShowMessage("Número invalido.");
  };

  borrartodo();  // borra toda la lista  (punteros)
  cabeza = new tnodo;
  p = cabeza->izq = cabeza->der = cabeza;

  if( (cadnum[1]=='-') || (cadnum[1]=='+') )// quitar el signo
    absnum = cadnum.SubString(2,n-1);
  else
    absnum = cadnum;
  if(absnum=="0"){
    cabeza->info = 0;
    return;
  }

  i = n = absnum.Length();
  while(i>0){
    if( i-4>0 ){
      i = i - 4;
      aux = absnum.SubString(i,5);
    }
    else{
      aux = absnum.SubString(1,i);
      i = 1;
    };
    numnodo = aux.ToInt();
    insertarder(p, numnodo);
    nnodos++;
    p = p->der;
    i--;
  };
  if(cadnum[1]=='-')
    cabeza->info = -nnodos;
  else
    cabeza->info = nnodos;
};

void tnumero::obtvalor(char *cad)
{
  tnodo *p;
  char cadaux[6], cadceros[6];
  int i, k, n;

  if(cabeza==0) return;
  p = cabeza->izq;
  strcpy(cad,"");
  if(p == cabeza){
    strcpy(cad,"0");
    return;
  }
  if(cabeza->info < 0) strcat(cad,"-");
  while(p != cabeza){
    sprintf(cadaux,"%d",p->info);
    n = milenght(cadaux);
    if( (n < 5) && (p!=cabeza->izq) ){
      for(i=0; i<5-n; i++) //Rellenar con ceros, deben ser cinco digitos
        cadceros[i]='0';
      cadceros[5-n] = 0;
      strcat(cad,cadceros);
    }
    strcat(cad,cadaux);
    p = p->izq;
  };
};

void tnumero::cambiarsigno(void)
{
  if (cabeza !=0)
    cabeza->info = cabeza->info * -1;
};

void tnumero::recorrernodos(void)
{
  tnodo *q;

  q = cabeza->der;

  while(q != cabeza){
    q = q->der;
  };
};

int tnumero::compabs(tnumero *n1, tnumero *n2)
{
  tnodo *r, *s, *p, *q;
  bool equal;

  p = n1->cabeza;    // 1 n1 es mayor a n2
  q = n2->cabeza;   //  0 n1 es igual a n2
                   // -1 n1 es menor a n2
  
  // compara los contadores
  if ( abs(p->info) > abs(q->info) ){
    return 1; //greaterthan
  }
  else{
    if ( abs(p->info) < abs(q->info) ){
      return -1; //lessthan
    }
    else{// son de igual longitud
      r = p->izq;
      s = q->izq;
      equal = true;
      // recorra la lista a partir del digito mas significante
      while ( (r!=p) && (equal == true) ){
        if ( r->info > s->info){
          equal = false;
          return 1; ///greaterthan
        };
        if( r->info < s->info){
          equal = false;
          return -1; //lessthan
        };
        if(r->info == s->info){
          r = r->izq;
          s = s->izq;
        };
      };//while (r<>p) and (equal)
      return 0; //equalto
    };//if abs(node[p].info) < abs(node[q].info)
  };
};

tnodo *tnumero::addiff(tnumero *n1, tnumero *n2)
{
  tnodo *r, *s, *zeroptr, *pptr, *qptr, *p, *q;
  bool zeroflag;
  int borrow;
  int diff, count;

  count = 0;     // inicializar variables
  borrow = 0;
  zeroflag = false;
  p = n1->cabeza;
  q = n2->cabeza;


  r = new tnodo;   // genera un nodo de encabezado para la suma
  r->izq = r;
  r->der = r;

  pptr = p->der; // recorre las dos listas
  qptr = q->der;

  while(qptr!=q){  ///Recore lista mas pequena
    diff = pptr->info - borrow - qptr->info;  //borrow es igual a prestamo
    if(diff>=0){
      borrow = 0;
    }
    else{
      diff = diff + hunthou;
      borrow = 1;
    };
    // genera un nuevo nodo y los inserta a la
    // izquierda del encabezamiento en la suma
    insertarizq(r,diff);
    count = count + 1;
    // pruebas para nodo cero
    if(diff == 0){
      if( !zeroflag )
        zeroptr = r->izq;
      zeroflag = true;
    }
    else
      zeroflag = false;
    pptr = pptr->der;
    qptr = qptr->der;
  };// while qptr<>q do begin

  // recorra el resto de la lista p
  while(p!=pptr){ // Recorre el rexto de la lista mas grande
    diff = pptr->info - borrow;
    if(diff >= 0){
      borrow = 0;
    }
    else{
      diff = diff + hunthou;
      borrow = 1;
    };
    insertarizq(r, diff);
    count = count + 1;
    if(diff == 0){
      if( !zeroflag)
        zeroptr = r->izq;
      zeroflag = true;
    }
    else
      zeroflag = false;
    pptr = pptr->der;
  };// while p<> pptr do begin
  if(zeroflag == true){// eliminar los ceros delanteros
    while(zeroptr!=r){
      s = zeroptr;
      zeroptr = zeroptr->der;
      borrar(s, diff);
      count = count - 1;
    };
  };
  //inserte contador y signo en el encabezamiento
  if(p->info>0)   //p es el signo del numero mas grande
    r->info = count;
  else
    r->info = -count;
  return r;
};

tnodo *tnumero::addsame(tnumero *n1, tnumero *n2)
{
  tnodo *r, *s, *zeroptr, *pptr, *qptr, *p, *q;
//  bool zeroflag;
  int llevo;
  int suma, count;

  count = 0;     // inicializar variables
  llevo = 0;
//  zeroflag = false;
  p = n1->cabeza;
  q = n2->cabeza;


  r = new tnodo;   // genera un nodo de encabezado para la suma
  r->izq = r;
  r->der = r;

  pptr = p->der; // recorre las dos listas
  qptr = q->der;

  while(qptr!=q){
    suma = pptr->info + llevo + qptr->info;
    if( suma < hunthou ){
      llevo = 0;
    }
    else{
      suma = suma % hunthou;
      llevo = 1;
    };
    // genera un nuevo nodo y los inserta a la
    // izquierda del encabezamiento en la suma
    insertarizq(r,suma);
    count = count + 1;
    // pruebas para nodo cero
  /*  if(suma == 0){
      if( !zeroflag )
        zeroptr = r->izq;
      zeroflag = true;
    }
    else
      zeroflag = false;*/
    pptr = pptr->der;
    qptr = qptr->der;
  };// while qptr<>q do begin

  // recorra el resto de la lista p
  while(p!=pptr){
    suma = pptr->info + llevo;
    if( suma < hunthou ){
      llevo = 0;
    }
    else{
      suma = suma % hunthou;
      llevo = 1;
    };
    insertarizq(r, suma);
    count = count + 1;
  /*  if(suma == 0){
      if( !zeroflag)
        zeroptr = r->izq;
      zeroflag = true;
    }
    else
      zeroflag = false;*/
    pptr = pptr->der;
  };// while p<> pptr do begin
  if(llevo>0){
    insertarizq(r, llevo);
    count = count + 1;
  }
/*  if(zeroflag == true){// eliminar los ceros delanteros
    while(zeroptr!=r){
      s = zeroptr;
      zeroptr = zeroptr->der;
      borrar(s, suma);
      count = count - 1;
    };
  };*/
  //inserte contador y signo en el encabezamiento
  if(p->info>0)
    r->info = count;
  else
    r->info = -count;
  return r;
};

tnodo *tnumero::addint(tnumero *n1, tnumero *n2)
{
  tnodo *p, *q;

  p = n1->cabeza;
  q = n2->cabeza;
  // revise si los enteros son del mismo signo
  if( p->info * q->info > 0){
    if( compabs(n1,n2) == 1 )// n1 greaterthan n2
      return addsame(n1,n2);
    else
      return addsame(n2,n1);
  }
  else{ // revise para ver cual tiene el valo absoluto mayor
    if( compabs(n1,n2) == 1 )// greaterthan
      return addiff(n1,n2);
    else
      return addiff(n2,n1);
  }
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::ButtonMasClick(TObject *Sender)
{
  char cad[255];
  AnsiString ansicad;

  num1.asignarvalor(MemoDisplay1->Text);
  num2.asignarvalor(MemoDisplay2->Text);
  resultado.borrartodo();
  resultado.asignarcabeza( resultado.addint(&num1,&num2) );
  resultado.obtvalor(cad);
  MemoDisplay3->Text = cad;

}

//---------------------------------------------------------------------------

void __fastcall TFormMain::ButtonMenosClick(TObject *Sender)
{
  char cad[255];
  AnsiString ansicad;

  num1.asignarvalor(MemoDisplay1->Text);
  num2.asignarvalor(MemoDisplay2->Text);
  num2.cambiarsigno();
  resultado.borrartodo();
  resultado.asignarcabeza( resultado.addint(&num1,&num2) );
  num2.cambiarsigno();
  resultado.obtvalor(cad);
  ansicad = cad;
  MemoDisplay3->Text = ansicad;
}

//---------------------------------------------------------------------------


void __fastcall TFormMain::ButtonCEClick(TObject *Sender)
{
  MemoDisplay1->Text = "0";
  MemoDisplay2->Text = "0";
  MemoDisplay3->Text = "0";
  num1.asignarvalor(MemoDisplay1->Text);
  num2.asignarvalor(MemoDisplay2->Text);
  resultado.asignarvalor(MemoDisplay3->Text);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormActivate(TObject *Sender)
{
//                      12345678901234567890
  MemoDisplay1->Text = "0";
  num1.asignarvalor(MemoDisplay1->Text);
//                      12345678901234567890
  MemoDisplay2->Text = "0";
  num2.asignarvalor(MemoDisplay2->Text);
//                     12345678901234567890
  MemoDisplay3->Text = "0";
  resultado.asignarvalor(MemoDisplay3->Text);

}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button1Click(TObject *Sender)
{
        FormMain->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button2Click(TObject *Sender)
{
  num2.recorrernodos();         
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button3Click(TObject *Sender)
{
  resultado.recorrernodos();        
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button5Click(TObject *Sender)
{
  char cad[255];

  num1.asignarvalor(MemoDisplay1->Text);
  num1.obtvalor(cad);
  MemoDisplay1->Text = cad;

  num2.asignarvalor(MemoDisplay2->Text);
  num2.obtvalor(cad);
  MemoDisplay2->Text = cad;

  resultado.asignarvalor(MemoDisplay3->Text);
  resultado.obtvalor(cad);
  MemoDisplay3->Text = cad;
}
//---------------------------------------------------------------------------




