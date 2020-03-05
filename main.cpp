#include <iostream>
#include <string>
#include <stdlib.h>     
#include <time.h>   

using namespace std;

class Cliente {
private:	
	int tiempo;
public:
	Cliente(){}
	void setTiempo(int time)
	{
		tiempo=time;
	}
	int getTiempo()
	{
		return tiempo;
	}
};


class Cola {
private:
	int size;
	int tiempo;
	Cliente *ptr;
	int tipoCola;
	int actual; 
	int primero; 
	int ultimo;
public:
	Cola(int n):size(n){ 
		tiempo = 0; 
		ptr = new Cliente[size];
		primero = 0;
		ultimo = size-1;
		actual = 0;
	};
	
	~Cola()
	{
		delete [] ptr;
	}
	
	
	int getTamanio(){return size;}
	Cliente getCliente()
	{
		if(isEmpty());
			return ptr[primero];
			
	}
	
	
	bool isEmpty()
	{
		return actual;
	}
	
	void setTipoCola(int _tipo) { tipoCola=_tipo;}
	
	
	void agregar_clientes(const Cliente& cliente)
	{
		ultimo = (ultimo + 1) % size;
		actual++;
		ptr[ultimo] = cliente;
	}
	void borrar_cliente()
	{
		if(isEmpty())
		{	actual--;
			primero = (primero + 1)%size;
		}	
	}
	
};

class Cajero {
private:
	int tiempo;
public:
	Cajero(){}
	void setTiempo(int _tiempo)
	{
		tiempo=_tiempo;
	}	
	int atender() // resta un minuto de atencion.
	{
		return --tiempo;
	}
	int estaLibre()  // Devuelve el tiempo, si es 0 es False y si es un numero es verdadero
	{
		return tiempo;
	}	
};

class Banco {
private:
	string nombre;
	int tiempo_restante;
	int numcajeros;
	int n_clientes;
	Cajero *cajeros;
	Cola *clientes;
	int suma_total;
public:
	Banco(int n_cajeros, int n)
	{
		n_clientes=n;
		numcajeros=n_cajeros;
		cajeros=new Cajero[numcajeros];
		clientes=new Cola(n_clientes);
		tiempo_restante=1;
		suma_total=0;
	}	
	
	
	
	void setClientes()
	{
		srand (time(NULL));
		for(int i=0;i<n_clientes;i++)
		{	Cliente nuevo;
			nuevo.setTiempo(rand()%13 + 3);		
			clientes->agregar_clientes(nuevo);
			cout<<"C"<<i+1<<" ("<<nuevo.getTiempo()<<")"<<endl;
		}
		cout<<endl<<endl;
	}
	
	int simularAtencion() // simula proceso de atencion. En un bucle recorrer los cajeros y restar un minuto de atencion por cada cajero.
	{
		int i=0,continua;
		bool salir=false;
		
		while(clientes->isEmpty() && !salir)
		{	
			if(i<numcajeros)
			{
				Cliente actual;
				actual=clientes->getCliente();
				//cout<<"Tiempo c "<<actual.getTiempo()<<endl;
				cajeros[i].setTiempo(actual.getTiempo());
				cout<<"Cajero "<<i+1<<" (C"<<i+1<<")"<<"  T: "<<cajeros[i].estaLibre()<<endl;
				i++;
				clientes->borrar_cliente();
				
			}	
			
			else
			{	cout<<endl<<"Corriendo el tiempo 1m ..."<<endl;
				while(clientes->isEmpty())
				{	for(int i=0;i<numcajeros;i++)
					{
						cajeros[i].atender();
						suma_total++;
						cout<<"Cajero"<<i+1<<" Tiempo: "<<cajeros[i].estaLibre()<<endl;
						if(cajeros[i].estaLibre()==0 && clientes->isEmpty())
						{
							Cliente actual;
							actual=clientes->getCliente();
							cout<<"Asignar Cliente a Cajero "<<i+1<<endl;
							cajeros[i].setTiempo(actual.getTiempo());
							cout<<"Cajero "<<i+1<<" Tiempo: "<<cajeros[i].estaLibre()<<endl;
							clientes->borrar_cliente();
						}	
						
						if(!clientes->isEmpty())
						{	continua=i+1;
							break;
						}
																		  
					}
					cout<<endl;
				}	
				
				if(!clientes->isEmpty())
					salir=true;					
				
			}	
		}		
		
		cout<<"Cola vacia esperando vaciar cajeros tiempo 1m..."<<endl;
		for(int i=continua;i<numcajeros;i++)
		{
			cajeros[i].atender();
			cout<<"Cajero "<<i+1<<" Tiempo: "<<cajeros[i].estaLibre()<<endl;
		}
		
		cout<<endl;
		
		while(tiempo_restante!=0)
		{	
			tiempo_restante=0;
			for(int i=0;i<numcajeros;i++)
			{
				if(cajeros[i].estaLibre()!=0)
					cajeros[i].atender();
				
				suma_total++;
				cout<<"Cajero "<<i+1<<" Tiempo: "<<cajeros[i].estaLibre()<<endl;
				tiempo_restante=tiempo_restante+cajeros[i].estaLibre();
			}
			
			cout<<endl;
		}
		
		return suma_total;
	}
	
};



int main()
{
	int n_clientes, tiempo_tomado;
	cout<<"Ingrese numero de clientes: ";
	cin>>n_clientes; 
	
	Banco entidad(5,n_clientes);  
	entidad.setClientes(); 	
	tiempo_tomado=entidad.simularAtencion();  
	cout<<"Suma total del tiempo invertido "<<tiempo_tomado<<" minutos"<<endl;
	
	return 0;
}
