Nuestros códigos los correremos en el clúster de ingeniería. Para conectarse debemos usar SSH, es decir, escribir en consola:

```ssh username@cluster.ing.uc.cl```

o antes también se usaba: (todavía me sigue funcionando)

```ssh username@mazinger.ing.puc.cl```

Siendo ```username``` el nombre de usuario de su correo UC. Luego de escribir lo anterior, les preguntará una contraseña (se las enviaré a sus mails).

Una vez dentro, se pueden usar los comandos típicos que usamos en consola: ```ls```, ```cd```, ```rm```, ```mkdir```, ```htop``` (para ver los procesos corriendo en el servidor), entre otros.

Si quieren cambiar su contraseña del servidor, pueden usar el comando ```yppasswd```.

Subir y recibir archivos:

- Opción 1: ```scp -r local_dir username@cluster.ing.uc.cl:server_dir```

    La línea anterior se corre en consola y el -r sirve para subir una carpeta (si se quita, se sube el archivo indicado en el path). Por ejemplo: tengo mi carpeta ```T2``` y quiero subirla a mi carpeta del servidor, entonces, ubicado en el path de mi carpeta en la consola, escribo el comando  ```scp -r AY04/ alberto.almuna@cluster.ing.uc.cl:~```, les preguntará por su contraseña. Este comando también se puede utilizar para enviar archivos desde el clúster a nuestro computador y solo basta con intercambiar el destino y origen (Ej: ```scp alberto.almuna@cluster.ing.uc.cl:~/log.out ./AY04```)

- Opción 2: crear un repositorio de Github y clonarlo en su computador y en el servidor, para luego transferir archivos con push y pull.

Correr código:

Para correr nuestros códigos podemos hacer lo mismo que en nuestro computador o pedirle al servidor que lo agregue a su cola de trabajo (cuando queramos correr algo grande).

La forma de compilar y correr nuestro código es la misma que ya hemos hecho.

Y para agregarlo a la cola de trabajo (con el job.sh creado):

- ```sbatch job.sh``` -> agrega el trabajo job.sh a la cola del clúster (este archivo corresponde a un set de instrucciones a realizar)

En nuestro caso, una vez que termine el job, creará un archivo ```log.out``` con el resultado obtenido. Si queremos leerlo rápidamente, podemos usar el comando ```cat log.out```. También podemos enviarnos el resultado usando el comando ```scp``` como arriba.

Para obtener información de la cola podemos usar ```squeue```, ```top``` o ```htop```.

Para más información sobre el clúster de Ing: https://deg.ing.uc.cl/informatica/cluster/

En particular, en la página https://deg.ing.uc.cl/informatica/cluster/trabajos-al-cluster/ en la sección de "Solicitud de CPU" se puede observar otro ejemplo de un archivo como ```job.sh```.
