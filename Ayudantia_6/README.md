Nuestros códigos los correremos en el clúster de ingeniería. Para conectarse debemos usar SSH, es decir, escribir en consola:

```ssh username@mazinger.ing.puc.cl```

Siendo ```username``` el nombre de usuario de su correo UC. Luego de escribir lo anterior, les preguntará una contraseña (se las enviaré a sus mails).

Una vez dentro, se pueden usar los comandos típicos que usamos en consola: ```ls```, ```cd```, ```mkdir```, ```htop``` (para ver los procesos corriendo en el servidor), entre otros.

Si quieren cambiar su contraseña del servidor, pueden usar el comando ```yppasswd```.

Subir archivos:

- Opción 1: ```scp -r local_dir username@mazinger.ing.puc.cl:server_dir```

    La línea anterior se corre en consola y el -r sirve para subir una carpeta (si se quita, se sube el archivo indicado en el path). Por ejemplo: tengo mi carpeta ```T2``` y quiero subirla a mi carpeta del servidor, entonces, ubicado en el path de mi carpeta en la consola, escribo el comando  ```scp -r T2/ alberto.almuna@mazinger.ing.puc.cl:~```, les preguntará por su contraseña.

- Opción 2: crear un repositorio de github y clonarlo en su computador y en el servidor, subir archivos con commits.

Correr código:

Para correr nuestros códigos podemos hacer lo mismo que en nuestro computador o pedirle al servidor que lo agregue a su cola de trabajo (cuando queramos correr algo grande).

La forma de compilar y correr nuestro código con MPI es la siguiente:

- ```mpic++ code.cpp -std=c++11``` -> compila el código y lo guarda en a.out
- ```mpirun ./a.out``` -> corre el ejecutable a.out
- ```mpirun -np 2 ./a.out``` -> corre el ejecutable a.out con 2 procesos

Y para agregarlo a la cola de trabajo (con el job.sh creado):

- ```sbatch job.sh``` -> agrega el trabajo job.sh a la cola de trabajo

Para obtener información de la cola podemos usar ```squeue```, ```top``` o ```htop```.

Para instalar MPI en WSL, pueden usar los siguientes comandos en consola:

    sudo apt-get update
    sudo apt install openmpi-bin libopenmpi-dev

Para más información sobre el clúster de Ing: https://deg.ing.uc.cl/informatica/cluster/
