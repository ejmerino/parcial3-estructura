#Universidad De Las Fuerzas Armadas Espe
#Integrantes:
#Josué Merino

#Funcion recursiva factorial
sacar_factorial <- function(n) {
  if(n <= 1) {
    return(1)
  } else { 
    return(n * sacar_factorial(n-1))
  }
}
# Para calcular el tiempo de ejecucion usamos los siguientes comandos en 
#la consola
t <- proc.time() # Inicia el cronómetro
#codigo
proc.time()-t    # Detiene el cronómetro
#Para graficar plot(x=variableX,y=variableY)
tiempo<-proc.time()-t
resulfact<-sacar_factorial(7)
resultfact<-sacar_factorial(8)
plot(x=7,y=resultfact)


      

#entradas y operaciones para graficar

entradas<-c(1,2,3,4,5,6,7)
operaciones<-c(sacar_factorial(1),sacar_factorial(2),sacar_factorial(3),
           sacar_factorial(4),sacar_factorial(5),sacar_factorial(6),
           sacar_factorial(7))

plot(x=entradas,
     y=operaciones,
     main='Notacion Factorial recursivo: O(n)',
     xlab='entradas',
     ylab='operaciones',
     col='cornflowerblue',
     pch=16,
     panel.first=grid())






