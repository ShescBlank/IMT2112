## Instalación MPI en WSL

Para instalar MPI en WSL, pueden usar los siguientes comandos en consola:

    sudo apt-get update
    sudo apt install openmpi-bin libopenmpi-dev

# Clúster

Nuestros códigos los correremos en el clúster de ingeniería. Para conectarse debemos usar SSH, es decir, escribir en consola:

```ssh username@cluster.ing.uc.cl```

o antes también se usaba: (todavía me sigue funcionando)

```ssh username@mazinger.ing.puc.cl```

Siendo ```username``` el nombre de usuario de su correo UC. Luego de escribir lo anterior, les preguntará una contraseña (se las enviaré a sus mails).

Una vez dentro, se pueden usar los comandos típicos que usamos en consola: ```ls```, ```cd```, ```rm```, ```mkdir```, ```htop``` (para ver los procesos corriendo en el servidor), entre otros.

Si quieren cambiar su contraseña del servidor, pueden usar el comando ```yppasswd```.

## Subir y recibir archivos

- Opción 1: ```scp -r local_dir username@cluster.ing.uc.cl:server_dir```

    La línea anterior se corre en consola y el -r sirve para subir una carpeta (si se quita, se sube el archivo indicado en el path). Por ejemplo: tengo mi carpeta ```AY05``` y quiero subirla a mi carpeta del servidor, entonces, ubicado en el path de mi carpeta en la consola, escribo el comando  ```scp -r AY05/ alberto.almuna@cluster.ing.uc.cl:~```, les preguntará por su contraseña. Este comando también se puede utilizar para enviar archivos desde el clúster a nuestro computador y solo basta con intercambiar el destino y origen (Ej: ```scp alberto.almuna@cluster.ing.uc.cl:~/log.out ./AY05```)

- Opción 2: crear un repositorio de Github y clonarlo en su computador y en el servidor, para luego transferir archivos con push y pull.

## Correr código

Para correr nuestros códigos podemos hacer lo mismo que en nuestro computador o pedirle al servidor que lo agregue a su cola de trabajo (cuando queramos correr algo grande).

La forma de compilar y correr nuestro código con MPI es la siguiente:

- Antes de poder compilar con ```mpic++``` en el clúster, es necesario correr el comando ```module load mpi/openmpi-x86_64``` en la consola del servidor (cada vez que nos conectemos es necesario volver a correr el comando anterior). Esto carga el módulo asociado a MPI, lo que significa que ahora podremos compilar y correr nuestros scripts de la misma manera que en nuestro computador personal. En caso de no correr la línea anterior luego de hacer login e intentar compilar, nos aparecerá un error de que no se encuentra el comando ```mpic++```.
- ```mpic++ code.cpp -std=c++11``` -> compila el código y lo guarda en a.out
- ```mpirun ./a.out``` -> corre el ejecutable a.out
- ```mpirun -np 2 ./a.out``` -> corre el ejecutable a.out con 2 procesos

Y para agregarlo a la cola de trabajo (con el job.sh creado):

- ```sbatch job.sh``` -> agrega el trabajo job.sh a la cola de trabajo. Ojo que también es necesario correr el comando ```module load mpi/openmpi-x86_64``` antes de mandar el trabajo a la cola.

En nuestro caso, una vez que termine el job, creará un archivo ```log.out``` con el resultado obtenido. Si queremos leerlo rápidamente, podemos usar el comando ```cat log.out```.

Para obtener información de la cola podemos usar ```squeue```, ```top``` o ```htop```.

Para más datos sobre el clúster de Ing: https://deg.ing.uc.cl/informatica/cluster/

## Correr Python en el clúster

En la tarea es necesario también correr un código de Python para generar la matriz pedida y, si queremos hacer un ejemplo bien grande, es buena idea correr este script también en el clúster. En dicho caso, puede ocurrir que no estén todas las librerías de Python necesarias directamente instaladas en el servidor, por lo que, para instalarlas, recomiendo seguir los pasos descritos en la documentación del clúster de ingeniería (https://dt.ing.uc.cl/recursos/cluster/ en la pestaña de "Software" y en la sección de Python). Acá se menciona que cada usuario debe usar Anaconda para administrar los paquetes extras y se indican las instrucciones para la instalación.

## Video Clúster

Hace un par de años hice un video que revisa todo lo importante relacionado al clúster (quizás ya toca hacerle una actualización, pero se los dejo disponible por si les sirve):

https://youtu.be/LqeU8yo_b-w

### IMPORTANTE: Cuando hice este video no era necesario correr el comando de ```module load mpi/openmpi-x86_64``` antes de querer compilar códigos de MPI, sin embargo, si ahora intentan ejecutar ```mpic++``` sin correr la línea anterior, el servidor les tirará un error porque no será capaz de encontrar el comando.

Otro detalle es que uso el ssh con "mazinger.ing.puc.cl", pero hace poco se cambió a "cluster.ing.uc.cl". A mi todavía me funciona el anterior, pero igual les recomiendo utilizar la dirección más nueva.
