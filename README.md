# PROYECTO 1 DE CI3825 - SISTEMAS DE OPERACION 1

**Alumno:** Arturo Yepez
**Carnet:** 15-11551

**Alumno:** Samuel Fagundez
**Carnet:** 15-10460

En Linux hay diversas herramientas para empaquetar, es decir, “juntar” dos o más archivos en un solo archivo (paquete). Una herramienta muy usada en Unix es tar. Otra operación es la de cifrar un archivo para proteger su contenido. Para este proyecto se debe implementar un empaquetador llamado `mytar`. Éste debe preservar la información sobre el archivo, en la medida de lo posible: permisos, tipo, dueño, grupo, número de bloques. Y por supuesto, tamaño y contenido exacto. Dados como fechas y número de inodos no pueden ser manejados a este nivel.

## OPCIONES QUE SE PUEDEN UTILIZAR 

Este comando deberá reconocer las siguientes opciones:
Mytar `<listaOpciones>`

1. ­`-f <nombreTar>`: especifica el archivo tar a usar.
2. ­`-c`: permite crear el archivo nombreTar. Si ya existe, lo sobreescribe. Debe preservar los tipos de archivos: directorios, regulares, pipes, y enlaces tanto simbólicos y fuertes.
3. ­`-n`: ignora todo archivo que no sea regular o directorio. Aplica a las opciones ­c, ­x y ­t.
4. ­`-t`: Muestra el contenido del archivo tar. Usando un formato similar al del comando 'ls ­l'.
5. ­`-o <nombreDirectorio>`: Directorio donde colocará la salida de una extracción. Por defecto es el directorio actual.
6. `­-z <desp>`: cifra el contenido del archivo. Se usa sólo con la opción ­c. Utiliza una técnica básica en donde los bits de cada byte son rotados hacia la derecha `<desp>` bits. Por ejemplo, considere los siguientes bits: 00100000, rotarlos 2 bits a la derecha produce la secuencia: 00001000.
7. ­`-y <desp>`: descifra el contenido del archivo. Se usa sólo con las opciones ­x y ­t. Utiliza una técnica básica en donde los bits de cada byte son rotados hacia la izquierda `<desp>` bits. Por ejemplo, considere los siguientes bits: 00001000, rotarlos 2 bits a la izquierda produce
la secuencia: 00100000.
8. `-­x [nombreArchivo]`: extrae el archivo nombreArchivo en caso de existir. Si este nombre no es especificado extrae todo. Si el archivo está cifrado, debe extraerlo descifrado. Si el archivo destino existe, será sobre escrito. Y debe ser idéntico al original, es decir, los
comandos diff y cmp no podrán encontrar diferencias.
9. `­-v [archivo]`: escribe en archivo una descripción de lo que va haciendo. En caso de no serespecificado el nombre, esta información aparecerá en el terminal.

## IMPLEMENTACION

Se preocedera a dividir el trabajo en los siguientes archivos que tengan funciones para su uso luego:
* ``

La solucion se planteo de la siguiente manera: 