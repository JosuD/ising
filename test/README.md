
## Testeos aplicados

* pick_site hizo un histograma para 8x8 indices. Esperaba ver una distribución uniforme
* energias sacó las energías de la función flip y las visualiza para la cantidad de iteraciones. Sirve para ver tiempo de termalización
* energiaymagnet sacó las energías y las magnetizaciones para la misma T con un puntero de flip.
* preterma muestra que para redes de 64x64 el sistema pretermaliza para $2 \cdot L^2$
* variasT visualiza lo mismo para distintas T, promediando en N iteraciones
* 500 puntos me muestra una tirada para B=0, J=1 de ising, viendo cosas que con 100 puntos no se ven, como los desvios cerca de $T_c$
