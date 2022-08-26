# IMT2112
Repositorio para las ayudantías de Algoritmos Paralelos en Computación Científica.

Mail: alberto.almuna@uc.cl

Si quieres dar algún comentario sobre la ayudantía: [Formulario de Feedback](https://forms.gle/7B53rLqTXwvjFFhW8)

## Correr código de C/C++ en Windows

Recomiendo instalar WSL (Windows Subsystem for Linux) y pueden seguir la siguiente [guía](https://docs.microsoft.com/en-us/windows/wsl/install)

En teoría debería funcionar la instalación directa con 
```
wsl --install
```
en la PowerShell con permisos de administrador, sin embargo, si no les funciona, recomiendo seguir la instalación manual que se menciona en el link anterior.

Una vez instalado WSL y la distribución de Linux preferida (sugiero Ubuntu o Debian principalmente), recomiendo instalar la consola Windows Terminal (desde la Microsoft Store) ya que permite manejar distintos tipos de consolas dentro de la misma.

Una vez dentro de WSL, corran al siguiente comando:
```
cd ~
```
![image](https://user-images.githubusercontent.com/53873288/186964595-824dab4e-45f2-47a7-8d50-4fe40eb80e7a.png)

para ir al directorio base. Si no hacen lo anterior, correrán los códigos desde Windows y no desde la distribución de Linux, lo que puede afectar el rendimiento de la ejecución. Entonces en este punto recomiendo crear las carpetas que utilizarán para el curso.

A continuación, pueden instalar git y el compilador que utilizaremos con los siguientes comandos:
```
sudo apt-get update
sudo apt-get install git
sudo apt-get install g++
```

Si utilizan VS Code, deben instalar la extensión 
![image](https://user-images.githubusercontent.com/53873288/186965303-e73d7741-0dc4-48b5-89d3-ec318447505a.png)

de esta manera, pueden correr el comando
```
code .
```
en la consola de WSL y les abrirá VS Code dentro del entorno de la distribución de Linux.

Por último, algunos comando útiles para navegar dentro de la consola:
- ```cd nombre_carpeta```: es para moverse por los directorios
- ```cd ..```: es para devolverse una carpeta
- ```mkdir nombre_carpeta```: es para crear una nueva carpeta
- ```ls```: es para ver los archivos que se encuentran en el directorio actual

## Por último, si quieren aprender más o profundizar sobre lo visto en la ayudantía les recomiendo el siguiente [enlace](https://github.com/DCCentral-de-Apuntes/intro-C). Es un un taller muy completo para aprender C y que nos sirve para entender C++.
