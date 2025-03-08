#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) { //2. Con que personas he jugado?

MYSQL *conn;
	int err;
	//estructura espacial para almacenar resultados de consultas
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	char lista[1000];
	char consulta_nombre[10];
	char nombre[10];
	char id_buscado[100];
	char consulta_participantes[100];
	char *token;
	char resultado[100];
	char *token2;
	char *token3;
	char *jugador;
	int encontrado=0;
	
	//creamos una conexion al servidor MYSQL
	conn=mysql_init(NULL);
	if(conn==NULL){
		printf("ERROR al crear la conexion: %u%s\n",
			   mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	//inicializar la conexion
	conn= mysql_real_connect(conn, "localhost","user","pass", "poker",0,NULL,0);
	if(conn==NULL){
		printf("Error al inicializar la conexion: %U %s\n",
			   mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	//consulta sql para obtener todos los datos de poker (BBDD)
	err=mysql_query(conn, "SELECT * FROM partidas");
	if(err!=0){
		printf("Error al consultar datos de la base %u %s\n",
			   mysql_errno(conn),mysql_error(conn));
		exit(1);
	}
	
	//recogemos el resultado de la consulta
	resultado= mysql_store_result(conn);
	
	row = mysql_fetch_row(resultado); //en la fila deberia haber 7 columnas (todos los datos de una partida)
	
	printf("Escribe tu nombre:\n");
	err=scanf("%s", nombre);
	if(err!=3){
			printf("Error al introducir los datos");
			exit(1);
	}
	
	strcpy(consulta_nombre, "select id_jugador from jugadores where nombre ='nombre'");
	
	err=mysql_query (conn, consulta_nombre);
		if (err!=0) {
			printf ("Error al consultar datos de la base %u %s\n",
					mysql_errno(conn), mysql_error(conn));
			exit (1);
		}
		resultado = mysql_store_result (conn);
		row = mysql_fetch_row (resultado);
		if (row == NULL)
			printf ("No se han obtenido datos en la consulta\n");
		else{
			// El resultado debe ser una matriz con una sola fila
			// y una columna que contiene el nombre
		strcpy(id_buscado,row[0]);
		
		srtcpy(consulta_participantes, "select id_jugador from participantes");
		err=mysql_query (conn, consulta_participantes);
		if (err!=0) {
			printf ("Error al consultar datos de la base %u %s\n",
					mysql_errno(conn), mysql_error(conn));
			exit (1);
		}
		resultado = mysql_store_result (conn);
		row = mysql_fetch_row (resultado);// tabla con el id_jugadores de cada partida
		
		int i=0;
		int total_filas = sizeof(tabla);
		while(i<total_filas){ 
		token = strtok(row[i],"/"); //Obtenemos el primer jugador de la partida
			while(token!=NULL){
			if(strcmp(id_buscado, token)==0){ //Es el jugador que estamos buscando?
			token2=strtok(row[i],"/"); 
			while(token2!=NULL){ 
				if(strcmp(token2,id_buscado)!=0){//Guardamos el jugador en resultado pero antes nos aseguramos de que no se haya añadido antes.
					strcpy(token3,token2);
					encontrado=0;
					jugador= strtok(resultado,",");
					while((jugador!=NULL)||(encontrado==0)){
						if(strcmp(token3,jugador)==0){
						encontrado=1;
						strcpy(token3,"\0");
						}
						jugador=strtok(NULL,",");
						if(jugador==NULL)
							encontrado=1;
					}
					if(encontrado==0)
						sprintf(resultado,"%s%s,",resultado,token2);
				}
				token2= strtok(NULL, "/");
			}
			}
			else
			token=strtok(NULL, "/");
			}
			i=i+1;
		}
		printf("Se ha jugado con:\n %s",resultado);
		}
		mysql_close (conn);
		exit(0);
	return 0;
		}
		
		
		
	
	
	
	
		
